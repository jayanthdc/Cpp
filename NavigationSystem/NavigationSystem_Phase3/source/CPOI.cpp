/***************************************************************************
 *======== Copyright by Darmstadt University of Applied Sciences =====
 ****************************************************************************
 * Filename         : CPOI.CPP
 * Author            : Jayanth Dodderi Chidanand
 * Description     : This file contains the definitions for the member functions
 * 					 			of the Class CPOI
 *
 ****************************************************************************/

//System Include Files
#include <iostream>
#include <stdlib.h>
using namespace std;

//Own Include Files
#include "CPOI.h"

//Method Implementations
/******************************************************************************************/
CPOI::CPOI(t_poi type, string name, string description, double latitude, double longitude):
												CWaypoint( name, latitude, longitude)
{
	m_type = type,
	m_description = description;
}

/******************************************************************************************/

void CPOI::set( t_poi  type , string name, string description,double latitude, double longitude)
{
	m_type = type,
	m_description = description;
	CWaypoint::set(name,latitude,longitude);
}
/******************************************************************************************/
void CPOI::getAllDataByReference(string& name, double& latitude, double& longitude, t_poi& type, string& description)const
{
	name  		   = this->getName();
	latitude      = this->getLatitude();
	longitude   = this->getLongitude();
	type            = this->m_type;
	description = this->m_description;
}
/******************************************************************************************/

void CPOI::print(int format)
{
	//To print enum values its respective strings are stored in an array
	cout<<"Point of Interest" <<endl;
	cout<<"================="<<endl;
	cout<<"of type"	<<" "<< Poi_Type[m_type] <<" : "<< m_description << endl;

	/*To print the other members of CPOI , CWaypoint Print fuction is called
	as it has the member function to print the Waypoint data in HH:MM:SS.*/
	CWaypoint::print(format); // Prints the value of Waypoint in DEG :MM:SS

}
/******************************************************************************************/
ostream& operator<<(ostream& out, const CPOI& c)
{
	int latitudeInDeg ,longitudeInDeg  = 0;
	int latitudeInMin ,longitudeInMin = 0;
	double latitudeInSec,longitudeInSec = 0.0;

	c.transformLatitude2degmmss(latitudeInDeg,latitudeInMin,latitudeInSec);
	c.transformLongitude2degmmss(longitudeInDeg,longitudeInMin,longitudeInSec);

	out <<"Point of Interest" <<endl<<"================="<<endl
			<<"of type"	<<" "<< Poi_Type[c.m_type] <<" : "<< c.m_description << endl<<c.getName()<< " on latitude = "
			<< latitudeInDeg <<"deg"<<" "<< latitudeInMin << "min"<<" "<< latitudeInSec << "sec" <<" and on Longitude = "<<longitudeInDeg<<
			"deg"<<" "<< longitudeInMin<< "min"<<" "<< longitudeInSec << "sec"<<endl;

	return out;
}
/******************************************************************************************/
CPOI::~CPOI()
{
#if	CPOI_DEBUG
	cout<< "Destructor for CPOI  Class Object"<<endl;
#endif
}
/******************************************************************************************/
std::string CPOI::getDescription() const
{
	return m_description;
}
/******************************************************************************************/
CPOI::t_poi CPOI::getType() const
{
	return m_type;
}
/******************************************************************************************/
