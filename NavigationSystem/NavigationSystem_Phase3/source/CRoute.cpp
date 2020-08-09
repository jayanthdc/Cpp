/********************************************************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CROUTE.CPP
 * Author          : Jayanth Dodderi Chidanand
 * Description     : This file contains the definitions for the member functions of the class CRoute
 */
/*******************************************************************************************************************/


//System Include Files
#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

//Own Include Files
#include "CRoute.h"

#define FALSE 											0
#define TRUE												1
#define CROUTE_DEBUG							0
#define CROUTE_UNIT_TESTING				0

bool g_TestCaseRetValue;
/*********************************************************************************************/
//Method Implementations
/*********************************************************************************************/

CRoute::CRoute( )
{
#if 	CROUTE_DEBUG
	cout<< "Default Constructor for the CRoute Database ,no elements are initialized \n" <<endl;
#endif
	m_pWpDatabase = NULL; // pointer to CWpDatabase class,via which members of the class are accessed;

	m_pPoiDatabase = NULL; // pointer to CWpDatabase class,via which members of the class are accessed;
	m_num_WayPoint = 0;
	m_num_poi = 0;
}
/*********************************************************************************************/

CRoute::CRoute(CRoute const& origin)
{
	m_pWpDatabase  = origin. m_pWpDatabase;//the pointer to link to the Waypoint database is copied.

	m_pPoiDatabase = origin. m_pPoiDatabase;//the pointer to link to the CPOI database is copied.

	my_route  	   = origin.my_route;//the List is copied to an new variable.

	m_num_WayPoint = origin.m_num_WayPoint;
	m_num_poi      = origin.m_num_WayPoint;

}
/*********************************************************************************************/

Route_t CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB)
{
	//the address of the CPOIDatabase object is copied to the attribute of CRoute m_pPoiDatabase to link to Database
	Route_t retValue = ROUTE_ERROR;
	if(pPoiDB != NULL)
	{
		m_pPoiDatabase = pPoiDB;
		retValue = ROUTE_SUCCESS;
	}

#if	CROUTE_DEBUG
	cout<< " ******** " <<m_pPoiDatabase<<endl;
#endif

	return retValue;
}
/*********************************************************************************************/
Route_t CRoute::connectToWpDatabase(CWpDatabase* pWpDB)
{
	//the address of the CWpDatabase object is copied to the attribute of CRoute m_pWpDatabase to link to Database
	Route_t retValue =  ROUTE_ERROR;

	if( pWpDB != NULL )
	{
		m_pWpDatabase = pWpDB;
		retValue = ROUTE_SUCCESS;
	}

#if	CROUTE_DEBUG
	cout<< " ******** " <<m_pWpDatabase<<endl;
#endif
	return retValue;
}
/*********************************************************************************************/
Route_t CRoute::addWaypoint(string name)
{
	Route_t retValue = ROUTE_ERROR;
	CWaypoint * WayPointPtr = NULL;

	if(m_pWpDatabase !=NULL) //Database link check
	{
		WayPointPtr = m_pWpDatabase->getPointerToWaypoint(name)  ;

		if (WayPointPtr != NULL)
		{
			//Waypoint added to the end of the list.
			my_route.push_back(WayPointPtr);
			m_num_WayPoint++;
#if	CROUTE_DEBUG
			cout<<" Requested Waypoint has been added to the Route"<<endl;
#endif

			retValue = ROUTE_SUCCESS;
		}
		else
		{
			cout<<" Error : Waypoint not found in the database.Something not in the pool"<<endl;
			retValue = ROUTE_ERROR_WAYPOINT_NULL;
		}

	}
	else
	{
		cout<<" Error : Waypoint Database not linked Please link it and retry again."<<endl;
		retValue = ROUTE_ERROR_DATABASE_NULL;
	}
	return retValue;
}
/*********************************************************************************************/

Route_t CRoute::addPoi(string namePoi,string afterWp)
{
	Route_t retValue = ROUTE_ERROR;
	list<CWaypoint*> ::iterator fitr;
	list<CWaypoint*> ::reverse_iterator ritr;
	CPOI * PoiPtr = NULL;
	bool Poi_Add_flag = FALSE;

	if(m_pPoiDatabase !=NULL) //Database link check
	{
		PoiPtr = m_pPoiDatabase->getPointerToPoi(namePoi) ;

		if(PoiPtr!=NULL) //If POI present in the CPOIdatabase or not.
		{
			if(my_route.empty())
			{
				cout << "Route is empty" << endl;
				retValue = ROUTE_ERROR_EMPTY;
			}
			else
			{
				for( ritr = my_route.rbegin(); ritr!=my_route.rend(); ++ritr )
				{
					if((*ritr)->getName() == afterWp)
					{
						fitr = ritr.base();
						my_route.insert(fitr,PoiPtr);
						m_num_poi++;
						Poi_Add_flag = TRUE;
#if	CROUTE_DEBUG
						cout<<"POI added to route as the AfterWp was present in the route "<<endl;
#endif

						retValue = ROUTE_SUCCESS;
						break;
					}
				}
				if(!Poi_Add_flag)
				{
					cout<<"POI could not be added to route as the AfterWp was not present in the route "<<endl;
					retValue = ROUTE_ERROR_WAYPOINT_NULL;
				}
			}
		}

		else
		{
			cout<<" Error : POI not found in the database.Something not in the pool"<<endl;
			retValue =  ROUTE_ERROR_POI_NULL;
		}

	}
	else
	{
		cout<<" Error : POIsDatabase not linked Please link it and retry again."<<endl;
		retValue = ROUTE_ERROR_DATABASE_NULL;
	}
	return retValue;
}
/*********************************************************************************************/

CRoute::~CRoute()
{
#if	CROUTE_DEBUG
	cout << "Deleted the Croute Object @"  <<  this  << endl;
#endif

}
/*********************************************************************************************/
Route_t CRoute::print()
{
	Route_t retValue = ROUTE_ERROR;
	list<CWaypoint*>::iterator print_itr;
	CPOI* CpoiPtr = NULL;

	if(my_route.empty())
	{
		cout<<"CRoute is empty"<<endl;
		retValue = ROUTE_ERROR_EMPTY;
	}
	else
	{
		cout<<"--------------------------------------------------------------------------" << endl;
		cout<<"My ROUTE has "<<m_num_WayPoint << "Waypoints and " <<m_num_poi  << "POI's "<<endl;
		cout<<"--------------------------------------------------------------------------" << endl;
		for( print_itr = my_route.begin(); print_itr != my_route.end(); print_itr++ )
		{
			//downcasting :Dynamic_cast is required
			CpoiPtr = dynamic_cast<CPOI*>(*print_itr);
			if(CpoiPtr!= NULL)
			{
				// CPOI overloaded << method invoked
				cout<<(*CpoiPtr)<<endl;
				cout<<"--------------------------------------------------------------------------" << endl;
			}
			else
			{
				// CWaypoint overloaded << method invoked
				cout<<(**print_itr)<<endl;
				cout<<"--------------------------------------------------------------------------" << endl;
			}
		}
		retValue =ROUTE_SUCCESS;
	}
	return  retValue ;
}
/*********************************************************************************************/
Route_t CRoute::operator +=(std::string name)
						{
	Route_t retValue = ROUTE_SUCCESS;
	CPOI * PoiPtr = NULL;
	/*Function to search the passed string if its present in the Waypoint database and adds it to
	  the end  of the route */
	addWaypoint(name);

	/*LOGIC to search the passed string if its present in the CPOI database and adds it to
	  the end  of the route */

	if(m_pPoiDatabase !=NULL) //Database link check
	{
		PoiPtr = m_pPoiDatabase->getPointerToPoi(name) ;

		if(PoiPtr != NULL)
		{
			my_route.push_back(PoiPtr);
			m_num_poi++;
			retValue =ROUTE_SUCCESS;
		}
		else
		{
			cout<<" Error : POI not found in the database.Something not in the pool"<<endl;
			retValue = ROUTE_ERROR_POI_NULL;
		}
	}
	else
	{
		cout<<" Error : POIsDatabase not linked Please link it and retry again."<<endl;
		retValue = ROUTE_ERROR_DATABASE_NULL;
	}
	return retValue ;
						}
/********************************************************************************************************************/

CRoute operator+( CRoute  &Croute1, CRoute  &Croute2)
{

	CRoute Croute3;
	int Wpcount =0;
	int POIcount =0;
	Wpcount = Croute1.m_num_WayPoint + Croute2.m_num_WayPoint ;
	POIcount = Croute1.m_num_poi + Croute2.m_num_poi ;

	if( (Croute1.m_pPoiDatabase == Croute2.m_pPoiDatabase) && (Croute1.m_pWpDatabase == Croute2.m_pWpDatabase) )
	{
		Croute1.my_route.splice(Croute1.my_route.begin(),Croute2.my_route);
		Croute3 = Croute1;
		Croute3.m_num_WayPoint= Wpcount;
		Croute3.m_num_poi= POIcount;
#ifdef CROUTE_UNIT_TESTING
		g_TestCaseRetValue = 1;
#endif
	}
	else
	{
		cout<< "Routes cannot be joined as they are pointing to differnt databases" <<endl;
#ifdef CROUTE_UNIT_TESTING
		g_TestCaseRetValue = 1;
#endif
	}
	return Croute3;
}
/*********************************************************************************************/
CRoute& CRoute::operator =(const CRoute& rop)
{
	if(this!= &rop)
	{
		my_route = rop.my_route;
		m_pPoiDatabase = rop.m_pPoiDatabase;
		m_pWpDatabase = rop.m_pWpDatabase;
		m_num_WayPoint = rop.m_num_WayPoint;
		m_num_poi = rop.m_num_poi;

	}
	return *this;
}
/*********************************************************************************************/
const vector<const CWaypoint*> CRoute::getRoute( )
{
	vector<const CWaypoint*> myConnectors;
	list< CWaypoint*> ::const_iterator my_itr;

	for( my_itr = my_route.begin(); my_itr != my_route.end(); ++my_itr )
	{
		myConnectors.push_back(*my_itr);
	}
	return myConnectors;
}
/*********************************************************************************************/
