#include "CWpDatabase.h"

/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CWPDATABASE.CPP
 * Author          :
 * Description     :
 *
 *
 ****************************************************************************/
//System Include Files
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

//Own Include Files
#include "CWpDatabase.h"

#define CWAY_DATABASE_DEBUG		0
//Method Implementations

/********************************************************************************************/

CWpDatabase::CWpDatabase()
{
#if	CWAY_DATABASE_DEBUG
	cout<< "Default Constructor for the CWaypoint Database ,no elements are initialized \n" <<endl;
#endif
}
/********************************************************************************************/

void CWpDatabase::addWaypoint(const CWaypoint& wp)
{
	/*a waypoint object is being inserted to the Cwaypoint database */
	m_WayPoint.insert ( pair <string ,CWaypoint> ( wp.getName() , wp ) );
}
/********************************************************************************************/

CWaypoint* CWpDatabase::getPointerToWaypoint(std::string name)
{
	//pointer of type CWaypoint to hold the address of requested CWaypoint.
	CWaypoint* ptr_Wp = NULL;

	//Iterator to iterate through the elements of the WaypointDatabase Container
	map<string,CWaypoint>::iterator Waypoint_Itr;

	if(m_WayPoint.empty())
	{
		cout<< "No WayPoints in the Database" <<endl;
	}

	else
	{
		for( Waypoint_Itr = m_WayPoint.begin(); Waypoint_Itr != m_WayPoint.end();  ++Waypoint_Itr)
		{
			if(name == Waypoint_Itr->second.getName())
			{
#if	CWAY_DATABASE_DEBUG
				cout<< "WayPoint is :" << Waypoint_Itr->second.getName() <<endl;
#endif

				ptr_Wp = &(Waypoint_Itr->second);

#if	CWAY_DATABASE_DEBUG
				cout<< " Ptr-Value " << ptr_Wp <<endl;
#endif
			}
		}
	}
	return ptr_Wp;
}
/********************************************************************************************/

void CWpDatabase::print()
{
	map<std::string, CWaypoint>::iterator itr;
	for( itr = m_WayPoint.begin(); itr != m_WayPoint.end(); ++itr)
	{
		itr->second.print(2);//2->MMSS

	}
}
/********************************************************************************************/
void CWpDatabase::getWpDatabaseByReference(	std::map<std::string, CWaypoint>& WpMap) const
{
	/*Copies the Waypoint Database to WpMap*/
	WpMap = m_WayPoint;
}
/********************************************************************************************/
void CWpDatabase::clearWpDatabase()
{
	/*Clears the contents of the Container(Database)*/
	m_WayPoint.clear();
}
/********************************************************************************************/
