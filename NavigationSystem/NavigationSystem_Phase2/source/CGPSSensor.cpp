/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CGPSSENSOR.CPP
 * Author          : Jayanth Dodderi Chidanand
 * Description     : This source file contains the definitions for the methods of the
 * 						Class CGPSSensor
 *
 ****************************************************************************/

//System Include Files
#include <iostream>
#include <stdlib.h>
using namespace std;

//Own Include Files
#include "CGPSSensor.h"

//Method Implementations

/******************************************************************************************/
/**
 * The Constructor of Class CGPSSensor, which allows to set initial value to the member attributes.
 * The Constructor is a default constructor.
 */
CGPSSensor::CGPSSensor()
{
#if GPSSENSOR_CLASS_DEBUG
	cout<<"Just Created a object of type CGPSSensor. This is the constructor at address"<<this<<endl;
#endif
}

/******************************************************************************************/

/**
 * Returns the Current position i.e a Waypoint after receiving the input from the user.
 * @param returntype : CWaypoint
 */
CWaypoint CGPSSensor::getCurrentPosition()
{
	CWaypoint GPSSensor_WayPoint;
	string GPSSensor_PositionName ="CurrentLocation" ;
	double GPSSensor_Latitude = 0 ;
	double GPSSensor_Longitude = 0 ;

	cout << "GPS Sensor"<< endl;
	cout << "Enter the Latitude : ";
	if(!(std::cin >> GPSSensor_Latitude))
	{
		cout<<"Value entered is incorrect"<<endl;
		std::cin.clear();
		std::cin.ignore(256,'\n');
	}
	//cin >> GPSSensor_Latitude;
	cout << "Enter the Longitude : ";
	if(!(std::cin >> GPSSensor_Longitude))
	{
		cout<<"Value entered is incorrect"<<endl;
		std::cin.clear();
		std::cin.ignore(256,'\n');
	}
	//cin >> GPSSensor_Longitude;
	cout << endl;

	//the GPS sensor object is set with the user input and is returned .
	if( (GPSSensor_Latitude >= MIN_LATITUDE_VALUE && GPSSensor_Latitude <= MAX_LATITUDE_VALUE )
			&& (GPSSensor_Longitude >= MIN_LONGITUDE_VALUE && GPSSensor_Longitude <= MAX_LONGITUDE_VALUE ) )
	{
		GPSSensor_WayPoint.set(GPSSensor_PositionName,GPSSensor_Latitude,GPSSensor_Longitude);
	}

	else
	{
		cout<<"The values entered for Current position by user is incorrect. "<<endl;
		cout<<"Distance will be calculated with default values of Current Position (0,0)...."<<endl<<endl;
	}
#if GPSSENSOR_CLASS_DEBUG
	cout<<"The current position is "<<GPSSensor_WayPoint.getName()<<" on Latitude "<<GPSSensor_WayPoint.getLatitude()<<
			" and Longitude "<<GPSSensor_WayPoint.getLatitude() <<endl;
#endif

	return GPSSensor_WayPoint; //Object returned
}
/******************************************************************************************/
