/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CNAVIGATIONSYSTEM.CPP
 * Author          : Jayanth Dodderi Chidanand
 * Description     : This file contains the definitions for the methods of the
 * 					 Class CNavigationSystem
 *
 ****************************************************************************/

//System Include Files
#include<iostream>
#include <stdlib.h>
using namespace std;

//Own Include Files
#include "CNavigationSystem.h"

//Method Implementations

/*********************************************************************************************/

/**
 * The Constructor of the CNavigtionSystem , which allows to set the initial value to the member attributes.
 * The Constructor is a default constructor.
 */
CNavigationSystem::CNavigationSystem()
{
	//Passing the address of the CPOI database object to link the CRoute to CPoiDatabase
	//if it is not linked CPOI database cannot be accessed and its member functions as well.
	m_route.connectToPoiDatabase(&m_PoiDatabase);
}

/*********************************************************************************************/
/**
 * Calls the private functions of the CNavigationSystem Class.
 * return type : void
 */
void CNavigationSystem::run()
{
	//POI's Already added in the database .If needed
	m_PoiDatabase.addPoi(CPOI::GASSTATION,"HP","Best in Petroleum division", 48.7758, 9.1829);

	//Enter your Trip
	enterroute();
	//Print the Route
	printroute();
	//Calculate the distance b/w current position and nearest POI and print it.
	printDistanceCurPosNextPoi();
}
/*********************************************************************************************/
/**
 * Add some POI’s and waypoints to the route.It takes the input from the user add some POI’s route.
 * return type : void
 */
void CNavigationSystem::enterroute()
{
	//Waypoints added
	CWaypoint wp1("Amsterdam",11.3,11.4);
	m_route.addWaypoint(wp1);

	CWaypoint wp2("Darmstadt",22.3,22.4);
	m_route.addWaypoint(wp2);

	CWaypoint wp3("Berlin",33.3,33.4);
	m_route.addWaypoint(wp3);

	//POI's added
	m_route.addPoi("HDA");

	m_route.addPoi("SHEL");

	m_route.addPoi("SHELL");

	m_route.addPoi("FRANKENSTEIN CASTLE");

}

/*********************************************************************************************/
/**
 * Print all POI’s and Waypoints of  route.
 * return type : void
 */
void CNavigationSystem::printroute()
{
	m_route.print();
}
/*********************************************************************************************/

/**
 * Get the current position from the GPS sensor and search for the closest Point of Interest.
 * return type : void
 */
void CNavigationSystem::printDistanceCurPosNextPoi()
{
	CPOI Nearest_Poi;

	double  DistCurPosNextPoi = m_route.getDistanceNextPoi(m_GPSSensor.getCurrentPosition(),Nearest_Poi);
	cout<< "Distance to next POI =" << DistCurPosNextPoi <<endl<<endl;

	//Print the Closet POI to the Current Position
	Nearest_Poi.print();
}
/*********************************************************************************************/
