/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences ======
 ****************************************************************************
 * Filename        : CPOI.CPP
 * Author          : Jayanth Dodderi Chidanand
 * Description     : This file contains the definitions for the member functions
 * 					 of the Class CPOI
 *
 ****************************************************************************/

//System Include Files
#include <iostream>		// Header für die Standard-IO-Objekte (z.B. cout, cin)
#include <stdlib.h>
using namespace std;


//Own Include Files
#include "CPOI.h"



//Method Implementations


/**
 * The Constructor of the CPOI , which allows to set the initial value to the member attributes.
 * The Constructor has parameters with default values.
 * @param t_poi type - the initial type , default Initial -"RESTAURANT" (IN)
 * @param string name - the initial name , default Initial- "Mensa_HDA" (IN)
 * @param string description - the initial name , default Initial-"The Best Mensa in the World" (IN)
 * @param double latitude - the initial latitude value , default Initial 0 (IN)
 * @param double longitude - the initial longitude value , default Initial 0 (IN)
 */
CPOI::CPOI(t_poi type, string name, string description, double latitude, double longitude):
								CWaypoint( name, latitude, longitude)
{
	m_type = type,
			m_description = description;
}

/******************************************************************************************/

/**
 * Sets the Current CPOI attributes.
 * @param:  t_poi  m_type - The new POI's type  (IN)
 * @param:  std ::string name - The new name of the POI(IN)
 * @param:  std ::string m_description - The new description of the POI(IN)
 * @param:  double latitude -The new latitude value of the POI(IN)
 * @param:  double longitude -The new longitude value of the POI(IN)
 * @returntype  void
 */
void CPOI::set( t_poi  type , string name, string description,double latitude, double longitude)
{
	m_type = type,
			m_description = description;
	m_name = name;
	m_latitude = latitude;
	m_longitude = longitude;

}
/******************************************************************************************/
/**
 * Returns the Current values of the CPOI data members by reference
 * @param:  string &name - The parameter is copied with the current name of POI.  (OUT)
 * @param:  double &latitude -The parameter is copied  with  current latitude value.  (OUT)
 * @param:  double &longitude - The parameter is copied  with  current longitude value .(OUT)
 * @param:  t_poi  &type - The parameter is copied  with  current type value of POI .(OUT)
 * @param:  string &description - The parameter is copied  with  current description of POI .(OUT)
 * @returntype  void.
 *
 */
void CPOI::getAllDataByReference(string& name, double& latitude, double& longitude, t_poi& type, string& description)
{
	name  		= this->m_name;
	latitude    = this->m_latitude;
	longitude   = this->m_longitude;
	type        = this->m_type;
	description = this->m_description;

}
/******************************************************************************************/
/**
 * Prints the POI.
 * @returntype  void.
 */
void CPOI::print()
{
	//To print enum values its respective strings are stored in an array
	const string Poi_Type[] = { "Restaurant","Touristic","GasStation" ,"University"};


	cout<<"Point of Interest" <<endl;
	cout<<"================="<<endl;
	cout<<"of type"	<<" "<< Poi_Type[m_type] <<" : "<< m_description << endl;

	/*To print the other members of CPOI , CWaypoint Print fuction is called
	as it has the member function to print the Waypoint data in HH:MM:SS.*/

	CWaypoint::print(MMSS); // Prints the value of Waypoint in DEG :MM:SS

	//if to be printed in Decimal the below line of code can be used.
	//cout<< m_name <<" on latitude = "<< m_latitude <<" and longitude = " << m_longitude <<endl;
}
/******************************************************************************************/

