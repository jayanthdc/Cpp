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


//Method Implementations
/**
 * The Constructor of the CPoiDatabase, which allows to set the initial value to the member attributes.
 * The Constructor is a default constructor.
 */
CPoiDatabase::CPoiDatabase()
{
	m_noPoi = 0;

	addPoi(CPOI::UNIVERSITY,"HDA","Best University for Applied Sciences In Germany",50.1109, 8.6821);

	addPoi(CPOI::GASSTATION,"SHELL","You can be Sure of Shell Quality", 48.7758, 9.1829);

	addPoi(CPOI::UNIVERSITY,"TU-HDA","Best Technical University in Hessen",32.5,32.6);

	addPoi(CPOI::RESTAURANT,"TASTE OF INDIA","Best Indian Food in Frankfurt",45.5,45.6);

	addPoi(CPOI::RESTAURANT,"MENSA-HDA","One of the Best Mensa in Germany",90,65.4);

	addPoi(CPOI::TOURISTIC,"FRANKENSTEIN CASTLE","Wonderful Castle in DARMSTADT",12.5,-60.5);

	addPoi(CPOI::TOURISTIC,"Cologne","City with a history",25.5,122.6);
}

/**
 * This adds an POI to the CPoiDatabase.
 * @param CPOI ::t_poi type  : type name of the POI to be added to the Database.(IN)
 * @param string name        : name of the POI to be added to the Database.(IN)
 * @param string description : description of the POI to be added to the Database.(IN)
 * @param double latitude    : latitude value of the POI to be added to the Database.(IN)
 * @param double longitude   : longitude value of the POI to be added to the Database.(IN)
 * return type : void
 */
void CPoiDatabase::addPoi(CPOI::t_poi type, string name, string description, double latitude, double longitude)
{

	if( m_noPoi >= CPOI_DATABASE_SIZE )
	{
		cout<< "!! ERROR POI_DATABASE IS FULL. NO MEMORY TO ADD THE NEW POI's "<< endl;
	}

	else
	{

		m_POI [m_noPoi].set( type,name, description,latitude,longitude);
		m_noPoi ++; //incrementing the index everytime a new object is called to it.

#if	CPOIDATABASE_DEBUG
		cout<<" **** "<<m_noPoi<<"****"<<endl;
		m_POI [m_noPoi-1].print();
#endif

	}

}

/**
 * Returns an pointer to the Point of Interest for the string being passed on to it.
 * @param string name : name of the POI to be searched inside the Database.(IN)
 * return type Ptr to an object of type CPOI
 */
CPOI* CPoiDatabase::getPointerToPoi(string name)
{
	CPOI* poi = NULL; //pointer of type CPOI to hold the addres of requested CPOI


	for( int PositionOfPOI = 0; PositionOfPOI < m_noPoi ; PositionOfPOI++)
	{
		if(name == m_POI[PositionOfPOI].getName())
		{
			poi = &m_POI[PositionOfPOI];
			break;
		}
	}
#if	CPOIDATABASE_DEBUG
	//cout<<"POI found in the database @ the position "<< PositionOfPOI <<endl;
	cout << "Address of the CPOI Object " << poi <<endl;
#endif

	return poi; //ptr returned
}
