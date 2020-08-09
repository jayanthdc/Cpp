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
using namespace std;

//Own Include Files
#include "CRoute.h"


//Method Implementations
/**
 * The Constructor of the CRoute, which allows to set the initial value to the member attributes.
 * The Constructor is a parameterized  constructor.
 * @param unsigned int maxWp - Max Waypoints in the Route ,default 3.(IN)
 * @param unsigned int maxPoi -Max POI's in the Route ,default 3.(IN)
 */
CRoute::CRoute(unsigned int maxWp , unsigned int maxPoi)
{

	m_maxWp  = maxWp;	//Initialized with default Values - 4
	m_maxPoi = maxPoi;  //Initialized with default Values - 3


	m_pWaypoint = new CWaypoint[m_maxWp]; //Allocating memory to hold max waypoints

	for(unsigned int j =0; j<m_maxWp; j++)
	{
		m_pWaypoint[j].set("NOTHING",0,0); // Set the memory to default  values
	}

	m_pPoi = new CPOI *[m_maxPoi]; //Allocating memory to hold max POIs

	for(unsigned int i =0; i<m_maxPoi; i++)
	{
		m_pPoi[i] = 0;  //set the memory to Zero.
	}

	m_nextPoi = 0;
	m_nextWp = 0;
	m_pPoiDatabase = NULL;

}
/*********************************************************************************************/

/**
 * This function connects the CRoute. to the CPoiDatabase.
 * @param CPoiDatabase*  pPoiDB :  pointer of type CPoiDatabase which will be update the member attribute(IN)
 * return type : void
 */
void CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB)
{
	//the address of the CPOIDatabase object is copied to the attribute of CRoute m_pPoiDatabase to link to Database
	m_pPoiDatabase = pPoiDB;

#if	CROUTE_DEBUG
	cout<< " ******** " <<m_pPoiDatabase<<endl;
#endif

}
/*********************************************************************************************/

/**
 * Destructor to clear the object and memory allocated dynamically.
 */
CRoute::~CRoute()
{

#if	CROUTE_DEBUG
	cout << "Deleted the Croute Object @"  <<  this  << endl;
#endif
	//free or releasing the memory allocated dynamically
	delete[]m_pWaypoint;
	delete[]m_pPoi;

}
/*********************************************************************************************/

/**
 * The CopyConstructor of the CRoute, which allows to copy an object an existing object of type Croute to an new object.
 */
CRoute::CRoute(CRoute const& origin)
{
	m_maxWp =  origin.m_maxWp; //Copy the contents of Origin to the new object .
	m_nextWp = origin.m_nextWp;
	m_maxPoi = origin.m_maxPoi;
	m_nextPoi= origin.m_nextPoi;


	/*If memory allocated , then for the new object new memory to be alocatd and
	then contents has to be copied : Deep Copy*/
	if(origin.m_pWaypoint)
	{
		m_pWaypoint = new CWaypoint[m_maxWp];
		for(unsigned int i =0; i<m_maxWp; i++)
		{
			m_pWaypoint[i]= origin.m_pWaypoint[i];

		}
	}
	else
		m_pWaypoint = 0;

	/*If memory allocated , then for the new object new memory to be alocatd and
		then contents has to be copied :  Deep Copy*/
	if(origin.m_pPoi)
	{
		m_pPoi = new CPOI*[m_maxPoi];
		for(unsigned int i =0; i<m_maxPoi; i++)
		{
			m_pPoi[i]= origin.m_pPoi[i];

		}
	}
	else
		m_pPoi = 0;


	m_pPoiDatabase = origin. m_pPoiDatabase;

}
/*********************************************************************************************/

/**
 * Adds a Waypoint to the CRoute.
 * @param CWaypoint const &wp : A constant Waypoint object to be added to the CRoute
 * return type : void
 */
void CRoute :: addWaypoint(CWaypoint const& wp)
{
	if(m_nextWp < m_maxWp)
	{
		m_pWaypoint [m_nextWp] = wp; //Adds the Waypoint to the CRoute
		m_nextWp ++; // Incrementing the Waypoint Index.

	}
	else
	{
		cout<<"!!MAXIMUM WAYPOINTS ARE ADDED TO THE ROUTE.FURTHER IT CANNOT BE EXTENDED"	<<endl;

	}

}
/*********************************************************************************************/

/**
 * Adds a POI to the CRoute.
 * @param string namePoi: name of the POI to be added to CRoute (IN)
 * return type : void
 */
void CRoute::addPoi(string namePoi)
{
	if(m_nextPoi < m_maxPoi)
	{
		if(m_pPoiDatabase !=NULL) //Database link check
		{
			m_pPoi[m_nextPoi] = m_pPoiDatabase->getPointerToPoi(namePoi)  ;


			if(m_pPoi[m_nextPoi] != NULL) //Pointer value verified to check whether it has address of POI or not.
			{
				m_nextPoi++; //Index incremented as to point to next POI
			}
			else
			{
				//The added POI is not in the database.So could not add to route.
				cout<<"!!ERROR : Could not find POI. Something not in the pool"	<<endl;
			}
		}
		else
		{
			cout<<"Database not linked Please link it and retry again."<<endl;
		}
	}
	else
	{
		//The size of the memory /buffer is complete.
		cout<<"!!MAXIMUM POI'S ARE ADDED TO THE ROUTE.FURTHER IT CANNOT BE EXTENDED"	<<endl;

	}
}
/*********************************************************************************************/

/**
 * Prints the CRoute. .
 * return type : void
 */
void CRoute::print()
{
	cout<<"*** Our Route has "<< m_nextWp << "Waypoints and " << m_nextPoi<< " Points of interest***"<<endl<<endl;

	for(unsigned int i =0; i<m_nextWp; i++)
	{
		m_pWaypoint[i].print(MMSS); //Print Waypoints added in the route

	}

	for(unsigned int j =0; j<m_nextPoi; j++)
	{
		m_pPoi[j]->print(); ////Print POI's added in the route

	}

}
/*********************************************************************************************/

/**
 * Calculates the distance between the Waypoint and POI and returns it.
 * @param CWaypoint const & wp : a Constant Waypoint object passed by reference.(IN)
 * @param CPOI& poi :The POI passed as refernce (IN)
 * return type : double
 */
double  CRoute::getDistanceNextPoi(CWaypoint const & wp,CPOI& poi)
{

	//double DistanceWrtPOIs[m_nextPoi] = { 0.0 }; //array to store the list of dist w.r.t to various POI's
	double DistanceWrtPOIs[5] = { 0.0 };
	double ClosestDistance = 0; // variable to hold the closest distance wr.t POI
	unsigned int location = 0; //location of the POI in the Route , which is near to Current Position

	if(m_nextPoi)
	{
		for(unsigned int i = 0; i< m_nextPoi; i++)

		{
			DistanceWrtPOIs[i] = m_pPoi[i]->calculateDistance(wp);

#if	CROUTE_DEBUG
			cout<<" A collection of Distances inside Croute is " << DistanceWrtPOIs[i] ;
			cout<<endl ;
#endif

		}

		ClosestDistance = DistanceWrtPOIs[0]; //The first member in the array is assumed having short distance .

		//Sorting  the values to find out the short distance and its position
		for (unsigned int j= 1 ; j< m_nextPoi; j++)
		{
			if(DistanceWrtPOIs[j] < ClosestDistance)
			{
				ClosestDistance = DistanceWrtPOIs[j];
				location = j;
			}

		}

#if	CROUTE_DEBUG
		cout<<" Closest Distance inside Croute is " << ClosestDistance <<endl;
		cout<<" index value is  " << location <<endl;
#endif

		poi =  *(m_pPoi[location]); //The POI object is copied with the contents of Closest POI in Route.
	}
	return ClosestDistance;
}
/*********************************************************************************************/



