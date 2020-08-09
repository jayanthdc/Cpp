/************************************************************************************************
 *======= Copyright by Darmstadt University of Applied Sciences =======
 *************************************************************************************************
 * Filename        : main.cpp
 * Author        	   : Jayanth Dodderi Chidanand
 * Description   : This file contains the main function  which has complete system functionality.
 *
 ************************************************************************************************/
//System  Include Files
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

//Own Include Files
#include "CNavigationSystem.h"
#include "CWaypoint.h"
#include "CPOI.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"
#include "CRoute.h"
#include "CGPSSensor.h"
#include "CPersistentStorage.h"
#include "CCSV.h"
#include "CDatabase.h"

//MACROS:
#define   TEST_NAVIGATION_SYSTEM							    1
#define   TEST_PERSISTENCE											0
#define   TEST_READDATA												0
#define   TEST_PERSISTENCE_ERROR_HANDLING		    0
#define   TEST_CPOIDB_STRING_AS_KEY							0
#define   TEST_CPOIDB_INT_AS_KEY								0
#define   TEST_CWAYPOINTDB_STRING_AS_KEY				0
#define   TEST_CWAYPOINTDB_INT_AS_KEY					0
/***************************************************************************************************************/
/**
 * main function which instantiates all the objects.
 * return type : int
 */
int main (void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	cout << "Entered main !!!!!!" << endl;
	cout << "***** APT LAB - ASSIGNMENT 3 (ADVANCED) ******"<<endl;
	cout<<"==========================================================="<<endl;

#if	TEST_NAVIGATION_SYSTEM
	{
		cout << "*****NAVIGATION_SYSTEM -TestCases*****"<<endl;
		cout<<"==========================================================="<<endl;
		cout << "******TestCases *****" << endl <<endl;

		CNavigationSystem MyFirstNavigationSystem;
		MyFirstNavigationSystem.run();
		cout<<"==========================================================="<<endl;
	}
#endif


#if TEST_PERSISTENCE
	{
		cout << "***** CJSON(PERSISTENCE) -TestCases*****"<<endl;
		cout<<"==========================================================="<<endl;

		//Waypoints created
		CWaypoint wp1("BERLINER_ALEE",11.3,11.4);
		CWaypoint wp2("AUSTRIA",22.3,22.4);
		CWpDatabase wpDatabase;//Cwpdatbase created;

		//Waypoints added to database
		wpDatabase.addWaypoint(wp1.getName() ,wp1);
		wpDatabase.addWaypoint(wp2.getName() ,wp2);

		//POI 'S  created
		CPOI poi1(CPOI::UNIVERSITY,"HDA","Best University for Applied Sciences In Germany",50.1109, 8.6821);
		CPOI poi2(CPOI::RESTAURANT,"KADAMBA","Best Restaurant for SOUTH INDIAN FOOD",50.1109, 8.6821);
		CPoiDatabase POIDatabase;//Cwpdatbase created;

		//POI's  added to database
		POIDatabase.addPoi(poi1.getName() ,poi1);
		POIDatabase.addPoi(poi2.getName(),poi2);

		CPersistentStorage *Baseptr;
		CJsonPersistence myJson;
		Baseptr = &myJson;

		Baseptr->setMediaName("Database");
		cout<<" Test case 1. File write and Read operations "<<endl;
		cout<<"==========================================================="<<endl;

		if( !Baseptr->writeData(wpDatabase,POIDatabase))
		{
			cout<< " ERROR : DataBASE content was not written to Files" <<endl;
			cout<<"==========================================================="<<endl;
		}
		else
		{
			cout<< "DataBASE content successsfully written to Files" <<endl;
			cout<<"==========================================================="<<endl;
		}
		cout<<"==========================================================="<<endl;
	}
#endif


#if TEST_PERSISTENCE_ERROR_HANDLING
	{
		CWpDatabase wpDatabase;
		CPoiDatabase POIDatabase;

		CPersistentStorage *Baseptr;
		CJsonPersistence myJson;
		Baseptr = &myJson;

		Baseptr->setMediaName("D:\\Masters_HDA\\SEMESTER_1\\APT\\Assignments\\Assignment-3\\Database");

		if(! Baseptr->readData(wpDatabase,POIDatabase,CPersistentStorage::MERGE) )
		{
			cout<< "ERROR : File read operation   " <<endl;
		}
		else
		{
			cout<< "SUCCESS : File read operation   " <<endl;
		}
		cout<<"==========================================================="<<endl;
	}
#endif


#if TEST_READDATA
	{
		cout << "***** CJSON(PERSISTENCE) -TestCases*****"<<endl;
		cout<<"==========================================================="<<endl;
		CWpDatabase WpDatabase;//Cwpdatbase created;
		CPoiDatabase POIDatabase;//Cwpdatbase created;

		CPersistentStorage *Baseptr = NULL;
		CJsonPersistence myJson;
		Baseptr = &myJson;

		Baseptr->setMediaName("D:\\Masters_HDA\\SEMESTER_1\\APT\\Assignments\\Assignment-3\\Database");//for testing purpose
		if(! Baseptr->readData(WpDatabase,POIDatabase,CPersistentStorage::MERGE) )
		{
			cout<< "ERROR : File read operation   " <<endl;
		}
		else
		{
			cout<<"Test case 1. Printing the content of the CWpDatabase "<<endl;
			cout<<"==========================================================="<<endl;
			WpDatabase.print();

			cout<<"Test case 1. Printing the content of the CPOIDatabase "<<endl;
			cout<<"==========================================================="<<endl;
			POIDatabase.print();
			cout<<"==========================================================="<<endl;
		}
	}
#endif
#if TEST_CPOIDB_STRING_AS_KEY
	{
		/*
		 * Test case for POI database(string as key)
		 */
		cout << "*****Test case for POI database(string as key)*****"<<endl;
	    cout<<"==========================================================="<<endl;
		CPoiDatabase mypoiDatabase;
		CPOI poi1(CPOI::RESTAURANT,"Mensa","good",45.3,99.9);					//create POI objects
		CPOI poi2(CPOI::GASSTATION,"HP","best gas station",56.54,79.19);
		mypoiDatabase.addPoi(poi1.getName(),poi1);			//add the POIs to the database
		mypoiDatabase.addPoi(poi2.getName(),poi2);
		mypoiDatabase.addPoi(poi2.getName(),poi2);        //trying to add same POI

		mypoiDatabase.print();													//print the database contents

		cout << "Pointer to POI HP : " << mypoiDatabase.getPointerToPoi("HP") << endl;		//searching POI present in database
		cout << "Pointer to POI Aldi : " << mypoiDatabase.getPointerToPoi("Aldi") << endl;	//searching POI missing in database
		cout<<"==========================================================="<<endl;
	}
#endif



#if 	TEST_CWAYPOINTDB_STRING_AS_KEY
	{
		cout << "*****Test case for Cwaypoint  database(string as key)*****"<<endl;
	cout<<"==========================================================="<<endl;
		CWpDatabase wpDatabase;

		CWaypoint wp1("Berlin",25.25,65.25);
		wpDatabase.addWaypoint(wp1.getName(),wp1);
		CWaypoint wp2("Amsterdam",54.12,67.11);
		wpDatabase.addWaypoint(wp2.getName(),wp2);
		CWaypoint wp3("Amsterdam",54.12,67.11);
		wpDatabase.addWaypoint(wp3.getName(),wp3); //adding the same waypoint to the database

		wpDatabase.print();													//print the contents of the database

		cout << "Pointer to way point Berlin : " << wpDatabase.getPointerToWaypoint("Berlin") << endl;
		cout << "Pointer to way point Bangalore : "<< wpDatabase.getPointerToWaypoint("Bangalore") << endl;
		cout<<"==========================================================="<<endl;
	}
#endif

#if 	TEST_CWAYPOINTDB_INT_AS_KEY
	{
		cout << "*****Test case for Cwaypoint  database(int as key)*****"<<endl;
		cout<<"==========================================================="<<endl;//create way points and add them to the route
		CWpDatabaseKey_int    wpDatabase;

		CWaypoint wp1("Berlin",25.25,65.25);
		wpDatabase.addElementToDatabase(1,wp1);

		CWaypoint wp2("Amsterdam",54.12,67.11);
		wpDatabase.addElementToDatabase(2,wp2);

		CWaypoint wp3("Berlin",25.25,65.25);
		wpDatabase.addElementToDatabase(1,wp3);

		wpDatabase.printDatabase();													//print the contents of the database

		cout << "Pointer to way point Berlin : " << wpDatabase.getPointerToElementInDatabase(1) << endl;
		cout << "Pointer to way point Amsterdam : "<< wpDatabase.getPointerToElementInDatabase(3) << endl;
		cout<<"==========================================================="<<endl;
	}
#endif

	cout << "*****END*****"<<endl;
	cout<<"==========================================================="<<endl;
	return 0;
}
/***************************************************************************************************************/
