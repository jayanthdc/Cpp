
// Header-Dateien
#include <iostream>		// Header für die Standard-IO-Objekte (z.B. cout, cin)
#include <stdlib.h>
#include <string>

//System Include Files
#include "CNavigationSystem.h"
#include "CWaypoint.h"
#include "CGPSSensor.h"
#include "CPOI.h"
#include "CPoiDatabase.h"
#include "CRoute.h"
#include "CWpDatabase.h"
#include "CPersistentStorage.h"
#include "CCSV.h"
#include <stdio.h>

using namespace std;

//Macros
#define TESTCASE_PART1							0
#define TESTCASE_PART2							0
#define TEST_CWAYPOINT							0
#define TEST_CPOI								0
#define TEST_CWAYPOINTDATABASE					0
#define TEST_CPOIDATABASE						0
#define TEST_CROUTE								0
#define TEST_PERSISTENCE						0
#define TEST_PERSISTENCE_ERROR_HANDLING			0
#define TEST_NAVIGATION_SYSTEM					1
#define TEST_READDATA							0



int main (void)
{
	setvbuf(stdout, NULL, _IONBF, 0);

	cout << "***** APT LAB - ASSIGNMENT 2 (POLYMORPHISM)*****"<<endl;
	cout<<"==========================================================="<<endl;


#if TEST_CWAYPOINT
	{
		cout << "***** CWAYPOINT_CLASS -TestCases*****"<<endl;
		cout<<"==========================================================="<<endl;
		CWaypoint WayPt("Amsterdam",52.3680,4.9036);
		cout<<"Testcase 1. Overlaoded Operator '<<' "<<endl;
		cout<< WayPt <<endl;
		cout<<"==========================================================="<<endl;
	}
#endif

#if TEST_CPOI
	{
		cout << "***** CPOI_CLASS -TestCases*****"<<endl;
		cout<<"==========================================================="<<endl;
		CPOI Cpoi(CPOI::UNIVERSITY,"HDA","Best University for Applied Sciences In Germany",50.1109, 8.6821);
		cout<<"Testcase 1. Overlaoded Operator '<<' "<<endl;
		cout<< Cpoi <<endl;
		cout<<"==========================================================="<<endl;
	}
#endif


#if TEST_CWAYPOINTDATABASE
	{
		cout << "***** CWAYPOINTDATABASE -TestCases*****"<<endl;
		cout<<"==========================================================="<<endl;

		//Waypoints created
		CWaypoint wp1("BERLINER_ALEE",11.3,11.4);
		CWaypoint wp2("AUSTRIA",22.3,22.4);

		CWpDatabase wpDatabase;//Cwpdatbase created;

		//Waypoints added to database
		wpDatabase.addWaypoint(wp1);
		wpDatabase.addWaypoint(wp2);

		cout<<"Test case 1. Printing the content of the CWpDatabase "<<endl;
		cout<<"==========================================================="<<endl;
		wpDatabase.print();

	}
#endif

#if TEST_CPOIDATABASE
	{
		cout << "***** CPOIDATABASE -TestCases*****"<<endl;
		cout<<"==========================================================="<<endl;

		//POI 'S  created
		CPOI poi1(CPOI::UNIVERSITY,"HDA","Best University for Applied Sciences In Germany",50.1109, 8.6821);
		CPOI poi2(CPOI::RESTAURANT,"KADAMBA","Best Restaurant for SOUTH INDIAN FOOD",50.1109, 8.6821);

		CPoiDatabase POIDatabase;//Cwpdatbase created;

		//POI's  added to database
		POIDatabase.addPoi(poi1);
		POIDatabase.addPoi(poi2);

		cout<<"Test case 1. Printing the content of the CPOIDatabase "<<endl;
		cout<<"==========================================================="<<endl;
		POIDatabase.print();

	}
#endif

#if TEST_CROUTE
	{
		cout << "***** CROUTE_CLASS -TestCases*****"<<endl;
		cout<<"==========================================================="<<endl;

		//Waypoints added to database
		CWaypoint wp1("BERLINER_ALEE",11.3,11.4);
		CWpDatabase wpDatabase;//Cwpdatbase created;//Waypoints added to database
		wpDatabase.addWaypoint(wp1);

		//POI's  added to database
		CPOI poi1(CPOI::UNIVERSITY,"HDA","Best University for Applied Sciences In Germany",50.1109, 8.6821);
		CPoiDatabase POIDatabase;//Cwpdatbase created;
		POIDatabase.addPoi(poi1);

		CRoute myRoute;

		myRoute.connectToPoiDatabase(&POIDatabase);
		myRoute.connectToWpDatabase(&wpDatabase);

		myRoute.addWaypoint("BERLINER_ALEE");
		myRoute.addPoi("HDA","BERLINER_ALEE");


		cout<<"Test case 1. Printing the content of the CROUTE "<<endl;
		cout<<"==========================================================="<<endl;
		myRoute.print();

		cout<<"Test case 2. Printing the content of the CROUTE when the requested POI or WP not present in database"
				<<endl;
		cout<<"==========================================================="<<endl;
		myRoute.addPoi("KADAMBA","DELHI");
		myRoute.print();

		cout<<"Test case 3. Printing the content of the CROUTE when the requested AFTER WP not present in database"
				<<endl;
		cout<<"==========================================================="<<endl;
		myRoute.addPoi("HDA","DELHI");
		myRoute.print();

		cout<<"Test case 4. CopyConstructor"	<<endl;
		cout<<"=================================="<<endl;
		CRoute OurRoute=myRoute;
		OurRoute.print();

		cout<<"Test case 5: Assignment operator" <<endl;
		cout<<"=================================="<<endl;
		CRoute Route1;
		Route1 = myRoute;
		Route1.print();

		cout<<"Test case 6: Overloaded operator += " <<endl;
		cout<<"=================================="<<endl;

		CWaypoint wp2("AUSTRIA",22.3,22.4);
		wpDatabase.addWaypoint(wp2);

		CPOI poi2(CPOI::RESTAURANT,"KADAMBA","Best Restaurant for SOUTH INDIAN FOOD",50.1109, 8.6821);
		POIDatabase.addPoi(poi2);

		Route1+=("AUSTRIA");
		Route1.print();

		cout<<"Test case 7: Overloaded operator + " <<endl;
		cout<<"=================================="<<endl;
		CRoute Route3;
		Route3 = myRoute + Route1;
		Route3.print();
	}
#endif

#if TEST_PERSISTENCE
	{
		cout << "***** CCSV(PERSISTENCE) -TestCases*****"<<endl;
		cout<<"==========================================================="<<endl;

		//Waypoints created
		CWaypoint wp1("BERLINER_ALEE",11.3,11.4);
		CWaypoint wp2("AUSTRIA",22.3,22.4);
		CWpDatabase wpDatabase;//Cwpdatbase created;

		//Waypoints added to database
		wpDatabase.addWaypoint(wp1);
		wpDatabase.addWaypoint(wp2);

		//POI 'S  created
		CPOI poi1(CPOI::UNIVERSITY,"HDA","Best University for Applied Sciences In Germany",50.1109, 8.6821);
		CPOI poi2(CPOI::RESTAURANT,"KADAMBA","Best Restaurant for SOUTH INDIAN FOOD",50.1109, 8.6821);
		CPoiDatabase POIDatabase;//Cwpdatbase created;

		//POI's  added to database
		POIDatabase.addPoi(poi1);
		POIDatabase.addPoi(poi2);
		CPersistentStorage *Baseptr;
		CCSV myCSV;
		Baseptr = &myCSV;

		Baseptr->setMediaName("Database");
		cout<<" Test case 1. File write and Read operations "<<endl;
		cout<<"==========================================================="<<endl;

		if(!Baseptr->writeData(wpDatabase,POIDatabase))
		{
			cout<< " ERROR : DataBASE content was not written to Files" <<endl;
			cout<<"==========================================================="<<endl;
		}
		else
		{
			cout<< "DataBASE content successsfully written to Files" <<endl;
			cout<<"==========================================================="<<endl;
		}


		if(!Baseptr->readData(wpDatabase,POIDatabase,CPersistentStorage::MERGE))
		{
			cout<< "ERROR : File reading not happened correctly.  " <<endl;
			cout<<"==========================================================="<<endl;
		}
		else
		{
			cout<< " File read successfully" <<endl;
			cout<<"==========================================================="<<endl;
		}

	}
#endif
#if TEST_PERSISTENCE_ERROR_HANDLING
	{
		CPersistentStorage *Baseptr;
		CWpDatabase wpDatabase;
		CPoiDatabase POIDatabase;
		CCSV myCSV;
		Baseptr = &myCSV;

		Baseptr->setMediaName("D:\\Masters_HDA\\SEMESTER_1\\APT\\Assignments\\Database");

		if(! Baseptr->readData(wpDatabase,POIDatabase,CPersistentStorage::MERGE) )
		{
			cout<< "ERROR : File read operation   " <<endl;
		}
	}
#endif

#if TEST_READDATA
	{
		cout << "***** CCSV(PERSISTENCE) -TestCases*****"<<endl;
		cout<<"==========================================================="<<endl;
		CWpDatabase wpDatabase;//Cwpdatbase created;
		CPoiDatabase POIDatabase;//Cwpdatbase created;

		CPersistentStorage *Baseptr = NULL;
		CCSV myCSV;
		Baseptr = &myCSV;
		Baseptr->setMediaName("D:\\Masters_HDA\\SEMESTER_1\\APT\\Assignments\\Container");//for testing purpose
		if(! Baseptr->readData(wpDatabase,POIDatabase,CPersistentStorage::MERGE) )
		{
			cout<< "ERROR : File read operation   " <<endl;
		}
		else
		{
			cout<<"Test case 1. Printing the content of the CWpDatabase "<<endl;
			cout<<"==========================================================="<<endl;
			wpDatabase.print();

			cout<<"Test case 1. Printing the content of the CPOIDatabase "<<endl;
			cout<<"==========================================================="<<endl;
			POIDatabase.print();
		}
	}
#endif

#if	TEST_NAVIGATION_SYSTEM
	{
		cout << "*****NAVIGATION_SYSTEM -TestCases*****"<<endl;
		cout<<"==========================================================="<<endl;
		cout << "******TestCases *****" << endl <<endl;

		CNavigationSystem MyFirstNavigationSystem;
		MyFirstNavigationSystem.run();
	}
#endif

}
