																																																																																																																																																																																																																																																																															/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CWAYPOINT.H
 * Author          : Jayanth Dodderi Chidanand
 * Description     : It contains the declaration and definition of the Class CWayPoint
 *
 ****************************************************************************/

#ifndef CWAYPOINT_H
#define CWAYPOINT_H

#include <iostream>
#include <string>
#include <cmath>

//macros
#define MIN_LATITUDE_VALUE				   -90
#define MAX_LATITUDE_VALUE		 		    90
#define MIN_LONGITUDE_VALUE		           -180
#define MAX_LONGITUDE_VALUE		            180
#define DEFAULT_WPCOORIDINATE_VALUE			0


#define SHOWADDRESS							0

//Class Definition

class CWaypoint {

//the << operator to support cout << CWaypoint
	friend std::ostream& operator<<(std::ostream& out, const CWaypoint& c);

private:
	/**
	 * Name of the Waypoint
	 */
	std :: string m_name;
	/**
	 * The Latitude value of the Waypoint.
	 */
	double m_latitude;
	/**
	 * The Longitude value of the Waypoint.
	 */
	double m_longitude;


public:

	/**
	 * The Constructor of the CWaypoint , which allows to set the initial values to the  attributes.
	 * The Constructor has parameters with default values.
	 *  @param string name - the initial name , default Initial- Waypoint (IN)
	 *  @param double latitude - the initial latitude value , default Initial 0 (IN)
	 *  @param double longitude - the initial longitude value , default Initial 0 (IN)
	 */
	CWaypoint( std :: string name ="WayPoint", double latitude = DEFAULT_WPCOORIDINATE_VALUE,
			double longitude  = DEFAULT_WPCOORIDINATE_VALUE);


	/**
	 * Sets the Current Waypoint attributes.
	 * @param:  string name	- The new string  (IN)
	 * @param:  double latitude	- The new latitude value (IN)
	 * @param:  double longitude - The new longitude value (IN)
	 * @returntype  void
	 */
	void set( std :: string name, double latitude, double longitude);


	/**
	 * Gets the current name of the Waypoint
	 * @returntype - string
	 */
	std ::string getName() const;

	/**
	 * Gets the Current latitude value of Waypoint
	 * @returntype  - (double)
	 */
	double getLatitude() const;


	/**
	 * Gets the Current longitude value of Waypoint
	 * @returntype  (double)
	 */
	double getLongitude() const;


	/**
	 * Returns the Current values of the Waypoint data members by reference
	 * @param:  string &name - The parameter is set with the current name.  (OUT)
	 * @param:  double &latitude -The parameter is set with the current latitude.  (OUT)
	 * @param:  double &longitude - The parameter is set with the current longitude .(OUT)
	 * @returntype  void
	 */
	void getAllDataByReference(  std :: string &name, double &latitude, double &longitude);


	/**
	 * Calculates the distance between the two Waypoints and returns it
	 * @param: const CWaypoint& - a Waypoint with constant data  (IN)
	 * @returntype -  (double)
	 */
	double calculateDistance(const CWaypoint& wp);


	/**
	 * Prints the Waypoint
	 * @param int format : The parameter to specify the way data to be printed
     						It can take values either 1(Degree) or 2(MMSS)  - (IN)
	 * @ returntype  : void
	 */
	void print(int format);
	/*
	 * Destructor function : made virtual to make it polymorphic
	 **/
	 virtual ~CWaypoint();


protected:

	/**
	 * Converts the Latitude value (double) to degrees minutes and seconds and returns it by reference
	 * @param int &deg : The parameter  which will be updated with value in Degrees.(OUT)
	 * @param int &mm  : The parameter  which will be updated with value in minutes.(OUT)
	 * @param double &ss :The parameter which will be updated with value in seconds.(OUT)
	 * @ returntype : void
	 */
	void transformLatitude2degmmss(int &deg, int &mm, double &ss)const;


	/**
	 * Converts the Longitude value (double) to minutes and seconds and returns it by reference
	 * @param int &deg : The parameter which will be updated with value in Degrees.(OUT)
	 * @param int &mm  : The parameter which will be updated with value in minutes.(OUT)
	 * @param double &ss :The parameter which will be updated with value in seconds.(OUT)
	 * @ returntype : void
	 */
	void transformLongitude2degmmss(int &deg, int &mm, double &ss)const;
};
/********************
 **  CLASS END
 *********************/
#endif /* CWAYPOINT_H */
