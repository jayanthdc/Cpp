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
	CDatabase( );
}
/********************************************************************************************/

void CWpDatabase::addWaypoint(std::string key,const CWaypoint& wp)
{
	/*a waypoint object is being inserted to the Cwaypoint database */
	addElementToDatabase(key,wp);
}
/********************************************************************************************/

CWaypoint* CWpDatabase::getPointerToWaypoint(std::string name)
{
	return getPointerToElementInDatabase(name);
}

/********************************************************************************************/
void CWpDatabase::getWpDatabaseByReference(	std::map<std::string, CWaypoint>& WpMap) const
{
	/*Copies the Waypoint Database to WpMap*/
	getDatabaseByReference(WpMap);

}
/********************************************************************************************/

void CWpDatabase::print()
{
/*Prints the content of the CWaypoint Database	*/
	printDatabase();
}
/********************************************************************************************/
void CWpDatabase::clearWpDatabase()
{
	/*Clears the contents of the Container(Database)*/
	clearDatabase();
}
/********************************************************************************************/

