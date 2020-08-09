/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOIDATABASE.CPP
 * Author          : Jayanth Dodderi Chidanand
 * Description     : This file contains the definition for the member functions of
 * 					 the Class CPoiDatabase
 *
 ****************************************************************************/
//System Include Files
#include <iostream>		// Header für die Standard-IO-Objekte (z.B. cout, cin)
#include <stdlib.h>
#include <string>
using namespace std;

//Own Include Files
#include "CPoiDatabase.h"

#define CPOIDATABASE_DEBUG			0
//Method Implementations
/********************************************************************************************/
CPoiDatabase::CPoiDatabase()
{
#if	CPOIDATABASE_DEBUG
	cout<< "Default Constructor for the CPOI Database ,no elements are initialized \n" <<endl;
#endif
}
/********************************************************************************************/

void CPoiDatabase::addPoi(CPOI const& poi)
{
	/*a CPOI object is being inserted to the CPOI database */
	m_POI.insert ( pair <string ,CPOI> ( poi.getName() , poi ) );
}
/********************************************************************************************/

CPOI* CPoiDatabase::getPointerToPoi(string name)
{
	CPOI* pPoi = NULL; //pointer of type CPOI to hold the address of requested CPOI

	//Iterator to iterate through the elements of the CPOIDatabase Container.

	map<string,CPOI>::iterator POI_Itr;

	if(m_POI.empty())
	{
		cout<<" No POI's in the Database "<<endl;
	}
	else
	{
		for( POI_Itr = m_POI.begin(); POI_Itr != m_POI.end();  ++POI_Itr )
		{
			if(name == POI_Itr->second.getName())
			{
#if	CPOIDATABASE_DEBUG
				cout<< "Point Of Interest is :"<< POI_Itr->second.getName() <<endl;
#endif
				pPoi =  &(POI_Itr->second);

			}
		}
	}
#if	CPOIDATABASE_DEBUG
	//cout<<"POI found in the database @ the position "<< PositionOfPOI <<endl;
	cout << "Address of the CPOI Object " << poi <<endl;

	cout<<"ptr value "<<pPoi<<endl;
#endif

	return pPoi; //ptr returned
}
/********************************************************************************************/
void CPoiDatabase::getPoiDatabaseByReference(
		std::map<std::string, CPOI>& Poi) const
{
	/*Copies the Waypoint Database to WpMap*/
	Poi = m_POI;
}
/********************************************************************************************/
void CPoiDatabase::print()
{
	std::map<std::string, CPOI>::iterator itr;
	for( itr = m_POI.begin(); itr != m_POI.end(); ++itr)
	{
		itr->second.print(2);//-->DEGMMMSS;
	}
}
/********************************************************************************************/
void CPoiDatabase::clearPoiDatabase()
{
	/*Clears the contents of the Container(Database)*/
	m_POI.clear();
}
/********************************************************************************************/
