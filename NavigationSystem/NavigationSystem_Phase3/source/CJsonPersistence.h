/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename		 : 	CJSONPERSISTENCE.H
 * Author       	 :  Jayanth Dodderi Chidanand
 * Description	 : This file contains all the declaration and definition of the Class CJsonPersistence
 *
 ****************************************************************************/

#ifndef CJSONPERSISTENCE_H
#define CJSONPERSISTENCE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include<string>
#include<typeinfo>
#include <map>
#include "CPersistentStorage.h"

class CJsonPersistence:public CPersistentStorage
{

protected:
	/**
	 * Attribute to hold the filename
	 */
	std:: string m_myjsonFileName;

public:

	/**
	 * The Constructor of the CJsonPersistene , which allows to set the initial values to the attributes.
	 */
	CJsonPersistence( );
	/**
	 * This function sets the name of the media used for storing the data.
	 * @param string name: name of the media used (IN)
	 * return type : void
	 */
	void setMediaName(std::string name) ;
	/**
	 * This function writes the data from the internal Databases to the persistet storage.
	 * @param const CWpDatabase& waypointDb : Waypoint database (IN)
	 * @param const CPoiDatabase& poiDb : POI dtabase (IN)
	 * return type : bool
	 */
	bool writeData ( const CWpDatabase& waypointDb, const CPoiDatabase& poiDb ) ;
	/**
	 * This function writes the Waypoint Database data from the internal Databases to the persistet storage.
	 * @param std::map<std::string ,CWaypoint> : Waypoint database Container (IN)
	 * @param const fileptr&  : Fileptr (OUT)
	 * return type : bool
	 */
	bool writeWpData( const std::map<std::string ,CWaypoint> &waypointDb ,std::ofstream &fileptr );
	/**
	 * This function writes the CPOI Database data from the internal Databases to the persistet storage.
	 * @param map<std::string ,CPOI>  &poiDb :CPOI database Container (IN)
	 * @param const fileptr&  : Fileptr (OUT)
	 * return type : bool
	 */
	bool writePoiData( const std::map<std::string ,CPOI>  &poiDb,  std::ofstream &fileptr );

	/**
	 * This function reads the data from the persistet storage and copies to internal Databases
	 * @param CWpDatabase& waypointDb : Waypoint database (IN)
	 * @param CPoiDatabase& poiDb : POI dtabase (IN)
	 * @param mode: can take values from enum {MERGE ,REPLACE};
	 * return type : bool
	 */
	bool readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode) ;
	/**
	 * The Destructor to delete the objects of the CJsonPersistence  class.
	 */
	~CJsonPersistence();


};


/********************
 **  CLASS END
 *********************/
#endif /* CJSONPERSISTENCE_H */
