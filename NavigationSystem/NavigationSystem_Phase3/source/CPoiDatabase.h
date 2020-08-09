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

#include <string>
#include <map>
#include "CPOI.h"
#include "CDatabase.h"

class CPOI;

class CPoiDatabase : public CDatabase< std::string, CPOI >
//< std::map<std::string,CPOI>, CPOI ,	std::map<std::string,CPOI>::iterator	>
{

private:
	/**
	 * (An array ) Database for storing the POI's
	 * @clientCardinality 1
	 * @supplierCardinality 1....10
	 * @link aggregationByValue
	 */
	//CPOI m_POI[CPOI_DATABASE_SIZE];
	/**
	 * Number of POI's in the Database
	 */
	//int m_noPoi;


	/*
	 * An associative container ,with key value mapping
	 * here the name of the POI is used as a key (string)
	 * the CPOI is a value to be stored in the container.
	 */

	std::map<std::string, CPOI> m_POI;

public:

	/**
	 * The Constructor of the CPoiDatabase, which allows to set the initial value to the member attributes.
	 * The Constructor is a default constructor.
	 */
	CPoiDatabase();

	/**
	 * This adds an POI to the CPoiDatabase.
	 * @param CPOI const& poi : the POI which needs to be added to the CPOIDatabase.(IN)
	 * return type : void
	 */
	//void  addPoi(CPOI const& poi);
	void addPoi( std::string key ,CPOI const& poi);
	/**
	 * Returns an pointer to the POI for the string being passed on to it.
	 * @param string name : name of the POI to be searched inside the Database.(IN)
	 * return type Ptr to an object of type CPOI
	 */
	CPOI* getPointerToPoi(std::string name);

	/**
	 * Returns the Current values of the CPOIDatabase data members by reference
	 * std::map<std::string, CPOI> &Poi - The parameter is copied  with the current POIdatase.(OUT)
	 * @returntype  void
	 */
	void getPoiDatabaseByReference(std::map<std::string, CPOI> &Poi) const;
	/*
	 *Prints the contents of the CpoiDatabase
	 * */
	void print();
	/*
	 *Clears the contents of the CpoiDatabase
	 */
	void clearPoiDatabase();


};


/********************
 **  CLASS END
 *********************/
#endif /* CPOIDATABASE_H */
