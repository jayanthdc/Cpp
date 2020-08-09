/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences ======
 ****************************************************************************
 * Filename        : CWAYPOINT.CPP
 * Author          : Jayanth Dodderi Chidanand
 * Description     : This File contains the definitions for the member functions
 * 					 of the Class CWaypoint
 *
 ****************************************************************************/

//System Include Files
#include <iostream>
#include <stdlib.h>
using namespace std;


//Own Include Files
#include "CWaypoint.h"

//Method Implementations
/***************************************************************************************************/
/**
 * The Constructor of the CWaypoint , which allows to set the initial value to the member attributes.
 * The Constructor has parameters with default values.
 *  @param string name - the initial name , default Initial- Goraguntepalya (IN)
 *  @param double latitude - the initial latitude value , default Initial 0 (IN)
 *  @param double longitude - the initial longitude value , default Initial 0 (IN)
 */
CWaypoint::CWaypoint(string name, double latitude , double longitude)
{

	set(name,latitude,longitude);

#if	SHOWADDRESS

	cout<< "Created a CWaypoint Object at " << this <<" "<< " with the name "
			<< m_name << " " << " ,values of latitude = " << m_latitude << ", and longitude = "
			<< m_longitude << endl ;

	//String occupies around 20 bytes of memory
	//Latitude and longitude occupies 8bytes of memory as it is of type double ,whose size is 8bytes

	cout<< "Address of the Attributes are - Address of name = "<< &m_name <<" ,Address of Latitude = "
			<< &m_latitude << " and Address of Longitude = " << &m_longitude << endl;
#endif
}
/***************************************************************************************************/

/**
 * Sets the Current Waypoint attributes.
 * @param:  string name	- The new string  (IN)
 * @param:  double latitude	- The new latitude value (IN)
 * @param:  double longitude - The new longitude value (IN)
 * @returntype  void
 */
void CWaypoint::set(string name, double latitude, double longitude)
{
	m_name = name;

	/*Latitudes and longitudes values range is checked. If input entered is out of this range ,
	 the default values are set*/

	if( (latitude >= MIN_LATITUDE_VALUE && latitude <= MAX_LATITUDE_VALUE )
			&& (longitude >= MIN_LONGITUDE_VALUE && longitude <= MAX_LONGITUDE_VALUE ) )
	{
		m_latitude = latitude;
		m_longitude = longitude;
	}

	else
	{
		m_latitude  = DEFAULT_WPCOORIDINATE_VALUE;  //default values set.
		m_longitude = DEFAULT_WPCOORIDINATE_VALUE;
	}
}
/***************************************************************************************************/

/**
 * Gets the current name of the Waypoint
 * @returntype - string
 */
string CWaypoint::getName()
{
	return m_name;
}
/***************************************************************************************************/

/**
 * Gets the Current latitude value of Waypoint
 * @returntype  - (double)
 */
double CWaypoint::getLatitude()
{
	return m_latitude;
}

/***************************************************************************************************/

/**
 * Gets the Current longitude value of Waypoint
 * @returntype  (double)
 */
double CWaypoint::getLongitude()
{
	return m_longitude;
}

/***************************************************************************************************/

/**
 * Returns the Current values of the Waypoint data members by reference
 * @param:  string &name - The parameter is copied with the current name.  (OUT)
 * @param:  double &latitude -The parameter is copied  with the current latitude.  (OUT)
 * @param:  double &longitude - The parameter is copied  with the current longitude .(OUT)
 * @returntype  void
 */
void CWaypoint::getAllDataByReference(string &name, double &latitude, double &longitude)
{
	name = m_name;
	latitude = m_latitude;
	longitude = m_longitude;

#if	SHOWADDRESS

	cout<< "Address of parameters inside function are"<< "Address of Name = "
			<< &name << "Address of latitude= " << &latitude <<
			" Address of longitude = " << &longitude << endl;

#endif
}
/***************************************************************************************************/

/**
 * Calculates the distance between the two Waypoints and returns it
 * @param: const CWaypoint& - a Waypoint with constant data  (IN)
 * @returntype -  (double)
 */
double CWaypoint::calculateDistance(const CWaypoint &wp)
{
	double DistBwWaypoints = 0;

	//sin function takes input value in radians ,thus the input is converted from deg to rad and applied.

	DistBwWaypoints = EARTH_RADIUS * ( acos  ( sin ( m_latitude * DEG2RADIAN_MULTIPLIER ) *
			sin (wp.m_latitude * DEG2RADIAN_MULTIPLIER ) + cos( m_latitude * DEG2RADIAN_MULTIPLIER )
			* cos ( wp.m_latitude * DEG2RADIAN_MULTIPLIER ) *
			cos(( wp.m_longitude * DEG2RADIAN_MULTIPLIER )-( m_longitude * DEG2RADIAN_MULTIPLIER ) ) ));


	return DistBwWaypoints;
}
/***************************************************************************************************/

/**
 * Prints the Waypoint
 * @param int format : The parameter to specify the way data to be printed
  						It can take values either 1(Degree) or 2(MMSS)  - (IN)
 * @ returntype  : void
 */
void CWaypoint::print(int format)
{
	int latitudeInDeg ,longitudeInDeg  = 0;
	int latitudeInMin ,longitudeInMin = 0;
	double latitudeInSec,longitudeInSec = 0.0;

	switch (format)
	{

	case DEGREE:
		//prints the values in decimal format.
		cout<< m_name <<" on latitude = "<< m_latitude <<" and longitude = " << m_longitude <<endl;
		cout<<"============================================================"<<endl;
		break;


	case MMSS:
		//prints the values in degrees , minutes and seconds format.
		transformLatitude2degmmss ( latitudeInDeg ,latitudeInMin , latitudeInSec);
		transformLongitude2degmmss (longitudeInDeg ,longitudeInMin ,longitudeInSec);

		cout << m_name << " on latitude = " << latitudeInDeg <<"deg"<<" "<< latitudeInMin << "min"
				<<" "<< latitudeInSec << "sec" <<" and on Longitude = "<<longitudeInDeg<<
				"deg"<<" "<< longitudeInMin<< "min"<<" "<< longitudeInSec << "sec"<<endl;
		cout<<"============================================================"<<endl;

		break;


	default :
		cout<< "Not a valid input.Please pass either DEGREE or MMSS (1 or 2)"<<endl;
		cout<<"============================================================"<<endl;
		break;

	}

}
/***************************************************************************************************/

/**
 * Converts the Latitude value (double) to minutes and seconds and returns it by reference
 * @param int &deg : The parameter  which will be updated with value in Degrees.(OUT)
 * @param int &mm  : The parameter  which will be updated with value in minutes.(OUT)
 * @param double &ss :The parameter which will be updated with value in seconds.(OUT)
 * @ returntype : void
 */
void CWaypoint::transformLatitude2degmmss(int &deg, int &mm, double &ss)
{
	deg = int(m_latitude); //takes the integral part of the value.

	//fabs func is used to return the absolute value of the minutes,as it cannot be negative.
	//as we have added math.h library its functions are used
	mm  = fabs( m_latitude - deg )* 60;

	//fabs func is used to return the absolute value of the seconds,as it cannot be negative.
	ss  = fabs( (m_latitude - deg) * 60  - mm) * 60 ;
}
/***************************************************************************************************/

/**
 * Converts the Longitude value (double) to minutes and seconds and returns it by reference
 * @param int &deg : The parameter which will be updated with value in Degrees.(OUT)
 * @param int &mm  : The parameter which will be updated with value in minutes.(OUT)
 * @param double &ss :The parameter which will be updated with value in seconds.(OUT)
 * @ returntype : void
 */
void CWaypoint::transformLongitude2degmmss(int &deg, int &mm, double &ss)
{
	deg = int(m_longitude);//takes the integral part of the value.

	//fabs func is used to return the absolute value of the minutes as it cannot be negative..
	//as we have added math.h library its functions are used
	mm  = fabs( m_longitude - deg )* 60;

	//fabs func is used to return the absolute value of the seconds as it cannot be negative..
	ss  = fabs( (m_longitude - deg) * 60  - mm) * 60 ;
}
/***************************************************************************************************/
