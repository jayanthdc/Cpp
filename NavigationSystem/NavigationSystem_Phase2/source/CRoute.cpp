/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CROUTE.CPP
 * Author          : Jayanth Dodderi Chidanand
 * Description     : This file contains the definitions for the member functions of
 * 					 the class CRoute
 *
 ****************************************************************************/


//System Include Files
#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

//Own Include Files
#include "CRoute.h"

#define FALSE 	0
#define TRUE	1
#define CROUTE_DEBUG	0

/*********************************************************************************************/
//Method Implementations
/*********************************************************************************************/

CRoute::CRoute()
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

void CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB)
{
	//the address of the CPOIDatabase object is copied to the attribute of CRoute m_pPoiDatabase to link to Database
	m_pPoiDatabase = pPoiDB;

#if	CROUTE_DEBUG
	cout<< " ******** " <<m_pPoiDatabase<<endl;
#endif

}
/*********************************************************************************************/
void CRoute::connectToWpDatabase(CWpDatabase* pWpDB)
{
	//the address of the CWpDatabase object is copied to the attribute of CRoute m_pWpDatabase to link to Database
	m_pWpDatabase = pWpDB;

#if	CROUTE_DEBUG
	cout<< " ******** " <<m_pWpDatabase<<endl;
#endif

}
/*********************************************************************************************/
void CRoute::addWaypoint(string name)
{
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
		}
		else
		{
			cout<<" Error : Waypoint not found in the database.Something not in the pool"<<endl;
			cout<<" Requested Waypoint could not be added to the Route"<<endl;
		}
	}
	else
	{
		cout<<" Error : Waypoint Database not linked Please link it and retry again."<<endl;
	}
}
/*********************************************************************************************/

void CRoute::addPoi(string namePoi,string afterWp)
{
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
						break;
					}
				}

				if(!Poi_Add_flag)
				{
					cout<<"POI could not be added to route as the AfterWp was not present in the route "<<endl;
				}
			}
		}

		else
		{
			cout<<" Error : POI not found in the database.Something not in the pool"<<endl;
			cout<<" Requested POI could not be added to the Route"<<endl;
		}

	}
	else
	{
		cout<<" Error : POIsDatabase not linked Please link it and retry again."<<endl;
	}
}
/*********************************************************************************************/

CRoute::~CRoute()
{
#if	CROUTE_DEBUG
	cout << "Deleted the Croute Object @"  <<  this  << endl;
#endif

}
/*********************************************************************************************/
void CRoute::print()
{
	list<CWaypoint*>::iterator print_itr;
	CPOI* CpoiPtr = NULL;
	cout<<"--------------------------------------------------------------------------" << endl;
	cout<<"My ROUTE has "<<m_num_WayPoint << "Waypoints and " <<m_num_poi  << "POI's "<<endl;
	cout<<"--------------------------------------------------------------------------" << endl;
	for( print_itr = my_route.begin(); print_itr != my_route.end(); print_itr++ )
	{
		CpoiPtr = dynamic_cast<CPOI*>(*print_itr); //downcasting :Dynmic_cast is required
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
}
/*********************************************************************************************/
void CRoute::operator +=(std::string name)
{
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
		}
	}
}

/*********************************************************************************************/

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
	}
	else
	{
		cout<< "Routes cannot be joined as they are pointing to differnt databases" <<endl;
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
double CRoute::getDistanceNextPoi(CWaypoint const & wp,CPOI& poi)
{
	double DistanceWrtPOIs[m_num_poi] = { 0 }; //array to store the list of dist w.r.t to various POI's
	double ClosestDistance = 0; // variable to hold the closest distance wr.t POI
	//unsigned int location = 0; //location of the POI in the Route , which is near to Current Position
	std::list<CWaypoint*>::iterator itr;
	CPOI* CpoiPtr = NULL;
	int i =0;
	if(m_num_poi)
	{
		for(itr=my_route.begin();itr != my_route.end(); ++itr)
		{
			CpoiPtr = dynamic_cast<CPOI*>(*itr); //downcasting :Dynmic_cast is required
			if(CpoiPtr!= NULL)
			{
				DistanceWrtPOIs[i]	= (*CpoiPtr).calculateDistance(wp);
				i++;
			}

		}

		ClosestDistance = DistanceWrtPOIs[0]; //The first member in the array is assumed having short distance .

		//Sorting  the values to find out the short distance and its position
		for ( int j= 1 ; j< m_num_poi; j++)
		{
			if(DistanceWrtPOIs[j] < ClosestDistance)
			{
				ClosestDistance = DistanceWrtPOIs[j];
				//location = j;
			}

		}

#if	CROUTE_DEBUG
		cout<<" Closest Distance inside Croute is " << ClosestDistance <<endl;
		cout<<" index value is  " << location <<endl;
#endif

		//poi =  *(my_route[location]); //The POI object is copied with the contents of Closest POI in Route.
	}
	return ClosestDistance;
}
