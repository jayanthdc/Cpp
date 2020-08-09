/***************************************************************************
 *========= Copyright by Darmstadt University of Applied Sciences =====
 ****************************************************************************
 * Filename        		: CNAVIGATIONSYSTEM.H
 * Author         	    : Jayanth Dodderi Chidanand
 * Description         : It contains the declaration of the Class CNavigationSystem
 *
 ****************************************************************************/

#ifndef CNAVIGATIONSYSTEM_H
#define CNAVIGATIONSYSTEM_H

#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPoiDatabase.h"
#include "CWaypoint.h"
#include "CWpDatabase.h"
#include "CCSV.h"
#include "CJsonPersistence.h"

class CNavigationSystem
{

private:
	/**
	 * A CRoute Object
	 * @link aggregationByValue
	 * @clientCardinality 1
	 * @supplierCardinality 1..**/
	CRoute m_route;
	/**
	 * A CPoiDatabase Object.
	 * @link aggregationByValue
	 * @clientCardinality 1
	 * @supplierCardinality 1..*
	 */
	CPoiDatabase m_PoiDatabase;
	/**
	 * A CWpDatabase Object.
	 * @link aggregationByValue
	 * @clientCardinality 1
	 * @supplierCardinality 1..*
	 */
	CWpDatabase m_WpDatabase;
	/**
	 * A CGPSSensor Object.
	 * @link aggregationByValue
	 * @clientCardinality 1
	 * @supplierCardinality 1
	 */
	CGPSSensor m_GPSSensor;
	/**
	 * A CCSV  /CJSON Object pointer.
	 */
	CPersistentStorage *m_pBaseptr;

public:

	/**
	 * The Constructor of the CNavigtionSystem , which allows to set the initial value to the member attributes.
	 * The Constructor is a default constructor.
	 */
	CNavigationSystem();

	/**
	 * Calls the private functions of the CNavigationSystem Class.
	 * return type : void
	 */
	void run();

private:

	/**
	 * Add some POI’s and waypoints to the route.It takes the input from the user add some POI’s route.
	 * return type : void
	 */
	void enterroute();

	/**
	 * Print all POI’s and Waypoints of  route.
	 * return type : void
	 */
	void printroute();

	/**
	 * Get the current position from the GPS sensor and search for the closest Point of Interest.
	 * return type : void
	 */
	void printDistanceCurPosNextPoi();
	/**
	 * Creates waypoints and POIS and adds them to dtabases
	 * return type : void
	 */
	void createDatabases();
	/**
	 * Writes the current content of the databases to the files
	 * return type : void
	 */
	void writeToFile() ;
	/**
	 *Reads the data from the external files and copies it to the databases
	 * return type : void
	 */
	void readFromFile();

};

/********************
 **  CLASS END
 *********************/
#endif /* CNAVIGATIONSYSTEM_H */
