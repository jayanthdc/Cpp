/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOIDATABASE.H
 * Author          : Jayanth Dodderi Chidanand
 * Description     : This file contains the definition for the Class CPoiDatabase
 *
 ****************************************************************************/

#ifndef CPOIDATABASE_H
#define CPOIDATABASE_H

#include<string>
#include "CPOI.h"

#define CPOI_DATABASE_SIZE			10
#define CPOIDATABASE_DEBUG			0
class CPOI;

class CPoiDatabase {

private:
	/**
	 * (An array ) Database for storing the POI's
	 * @clientCardinality 1
	 * @supplierCardinality 1....10
	 * @link aggregationByValue
	 */
	CPOI m_POI[CPOI_DATABASE_SIZE];
	/**
	 * Number of POI's in the Database
	 */
	int m_noPoi;

public:

	/**
	 * The Constructor of the CPoiDatabase, which allows to set the initial value to the member attributes.
	 * The Constructor is a default constructor.
	 */
	CPoiDatabase();

	/**
	 * This adds an POI to the CPoiDatabase.
	 * @param CPOI ::t_poi type  : type name of the POI to be added to the Database.(IN)
	 * @param string name        : name of the POI to be added to the Database.(IN)
	 * @param string description : description of the POI to be added to the Database.(IN)
	 * @param double latitude    : latitude value of the POI to be added to the Database.(IN)
	 * @param double longitude   : longitude value of the POI to be added to the Database.(IN)
	 * return type : void
	 */
	void  addPoi(CPOI ::t_poi type, std::string name, std::string description, double latitude, double longitude);

	/**
	 * Returns an pointer to the POI for the string being passed on to it.
	 * @param string name : name of the POI to be searched inside the Database.(IN)
	 * return type Ptr to an object of type CPOI
	 */
	CPOI* getPointerToPoi(std::string name);

};


/********************
 **  CLASS END
 *********************/
#endif /* CPOIDATABASE_H */
