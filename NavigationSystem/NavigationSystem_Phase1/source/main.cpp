
// Header-Dateien
#include <iostream>		// Header für die Standard-IO-Objekte (z.B. cout, cin)
#include <stdlib.h>
#include <string>
using namespace std;

#if 1
//System Include Files
#include "CNavigationSystem.h"
#include "CWaypoint.h"
#include "CGPSSensor.h"
#include "CPOI.h"
#include "CPoiDatabase.h"
#include "CRoute.h"

#endif


//Macros
#define TESTCASE_PART1				1
#define TESTCASE_PART2				1


int main (void)
{

	cout << "***** APT LAB - ASSIGNMENT 1 *****" << endl <<endl;
	#if 1
#if TESTCASE_PART1
	{

		cout << "*****TASK 1.1 TestCases *****" << endl <<endl;
		//Task :a
		//Latitude and longitude values (Source : Internet )52.3680° N, 4.9036°E
		CWaypoint amsterdam("Amsterdam",52.3680,4.9036);

		//Latitude and longitude values (Source : Internet )49.8728° N, 8.6512°E
		CWaypoint darmstadt("Darmstadt",49.8728,8.6512);

		//Latitude and longitude values (Source : Internet )52.5200° N, 13.4050°E
		CWaypoint berlin("Berlin",52.5166, 13.4050);

		//Latitude and longitude values (Source : Internet )35.6895° N, 139.6917°E
		CWaypoint tokio("Tokio",35.6895,139.6917);

		CWaypoint newWaypoint;


		//Task :b
		berlin.print(DEGREE); //DEGREE: A symbolic constant with Value 1 ,defined in header-fileof CWaypoint.
		berlin.print(MMSS); //MMSS: A symbolic constant with Value 2,defined in header-file of CWaypoint.


		//Task :c
		cout<<"Name as return value : "<< berlin.getName() << endl;
		cout<<"============================================"<<endl;
		cout<<"Latitude as return value : "<< berlin.getLatitude() << endl;
		cout<<"============================================"<<endl;
		cout<<"Longitude as return value : "<< berlin.getLongitude() << endl;
		cout<<"============================================"<<endl;


		//Task :d
		string name;
		double latitude,longitude = 0;
		/*
		 * When parameters are passed by reference , any changes made inside the function
		 * will be reflected in the main file , where it is declared ,as the value is being written
		 * into the same address.Here when the three local variables name , latitude and longitude are
		 * passed by reference , in the function an alias of the variable will be created and it also points
		 * to the same address allocated for these variables when they are declared. So the address
		 * of the parameters inside the function and local variables address both are same.
		 * */

		tokio.getAllDataByReference(name,latitude,longitude);

		cout<<"The data of the Waypoint Tokio obtained by reference is, "<< "name = "<<name
				<< ",  latitude = "<<latitude <<" and longitude = "<<longitude <<endl;

#if SHOWADDRESS

		cout<< "Addresses of local variables in main file are"<< "Address of string Name="
				<< &name << "Address of variable latitude=" << &latitude <<
				"Address of variable longitude=" << &longitude <<endl;
#endif

		//Task :e

		double DistanceBwWaypoints = 0 ;

		DistanceBwWaypoints = amsterdam.calculateDistance(berlin);
		cout<<"============================================================"<<endl;
		cout<<"The Distance between the Amsterdam and Berlin : "<<DistanceBwWaypoints<<endl;

		DistanceBwWaypoints = berlin.calculateDistance(tokio);
		cout<<"============================================================"<<endl;
		cout<<"The Distance between the Berlin and Tokio :"<<DistanceBwWaypoints<<endl;
		cout<<"============================================================"<<endl<<endl<<endl;
	}
#endif



#if TESTCASE_PART2
	{
		cout << "*******TASK 1.3 TestCase *****" << endl <<endl;

		CNavigationSystem MyFirstNavigationSystem;
		MyFirstNavigationSystem.run();
	}
#endif

#endif

	//cout << "*******TASK 1.3 TestCase *****" << endl << endl;

	return 0;
}
