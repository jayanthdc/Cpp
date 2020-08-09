/************************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ************************************************************************************
 * Filename       		 : CNAVIGATIONSYSTEM.CPP
 * Author        		 	 : Jayanth Dodderi Chidanand
 * Description    		 : This file contains the definitions for the methods of the
 * 					 				Class CNavigationSystem
 *
 ***********************************************************************************/

//System Include Files
#include<iostream>
#include <stdlib.h>
using namespace std;

//Own Include Files
#include "CNavigationSystem.h"
#include "CPersistentStorage.h"
//Method Implementations

/*********************************************************************************************/

/**
 * The Constructor of the CNavigtionSystem , which allows to set the initial value to the member attributes.
 * The Constructor is a default constructor.
 */
CNavigationSystem::CNavigationSystem()
{
	//Passing the address of the CPOI  and CWpdatabase objects to link the CRoute to CPoiDatabase and CWaypoint
	//Databases.If it is not linked CPOI database cannot be accessed and its member functions as well.
	m_route.connectToPoiDatabase(&m_PoiDatabase);
	m_route.connectToWpDatabase(&m_WpDatabase);
	m_pBaseptr =NULL;

}

/*********************************************************************************************/
/**
 * Calls the private functions of the CNavigationSystem Class.
 * return type : void
 */
void CNavigationSystem::run()
{
	/* ADDs the WP and CPOI to the containers*/
	createDatabases();

	/* Writes the data from internal ram to Persistent storage */
	writeToFile();

	/* Reads the data from the persistent storage and copies to containers*/
	//readFromFile();

	/* The CRoute is created as per the user*/
	enterroute();

	/* prints the complete Croute*/
	printroute();

}
/*********************************************************************************************/
/**
 * Add some POI’s and waypoints to the route.It takes the input from the user add some POI’s route.
 * return type : void
 */
void CNavigationSystem::enterroute()
{
	//Waypoints added to the Croute
	m_route.addWaypoint("GG_PALYA");
	m_route.addWaypoint("RNSIT");
	m_route.addWaypoint("KENGERI");

	//POI's added to route
	m_route.addPoi("HDA","RNSIT");
	m_route.addPoi("KADAMBA","KENGERI");
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
 * Creates the Wp and CPOI Databases
 * return type : void
 */
void CNavigationSystem::createDatabases()
{
	CWaypoint wp1("GG_PALYA",11.3,11.4);
	CWaypoint wp2("KENGERI",22.3,22.4);
	CWaypoint wp3("RNSIT",33.3,33.4);

	//Waypoints added to database

	m_WpDatabase.addWaypoint(wp1.getName(),wp1);
	m_WpDatabase.addWaypoint(wp2.getName(),wp2);
	m_WpDatabase.addWaypoint(wp3.getName(),wp3);

	//POIs created

	CPOI poi1(CPOI::UNIVERSITY,"HDA","Best University for Applied Sciences In Germany",50.1109, 8.6821);
	CPOI poi2(CPOI::RESTAURANT,"KADAMBA","Best Restaurant for SOUTH INDIAN FOOD",50.1109, 8.6821);

	//POI's added to database
	m_PoiDatabase.addPoi(poi1.getName() , poi1);
	m_PoiDatabase.addPoi(poi2.getName()  ,poi2);

}
/*********************************************************************************************/
/**
 * Writes the data from Cwp and Cpoi Databases to the File
 * return type : void
 */
void CNavigationSystem::writeToFile()
{
	CJsonPersistence myJson;
	CCSV myCSV;
	m_pBaseptr= &myJson;
	m_pBaseptr->setMediaName("myDatabase");

	if( ! m_pBaseptr->writeData (  m_WpDatabase, m_PoiDatabase) )
		cout<<" **File write operation failure** " << endl;
	else
		cout<<" **File write operation Success** " << endl;

	cout<<"==========================================================="<<endl;
	m_pBaseptr =NULL;
}
/*********************************************************************************************/
/**
 * Reads the data from  the File and copies to 	Cwp and Cpoi Databases
 * return type : void
 */
void CNavigationSystem::readFromFile()
{
	CJsonPersistence myJson;
	m_pBaseptr= &myJson;
	m_pBaseptr->setMediaName("myDatabase");

	if( ! m_pBaseptr->readData( m_WpDatabase, m_PoiDatabase, CPersistentStorage::MERGE ) )
		cout<<"**File Read operation failure** " << endl;
	else
		cout<<" **File Read operation Success**" << endl;
	cout<<"==========================================================="<<endl;

	m_pBaseptr =NULL;
}
/*********************************************************************************************/
