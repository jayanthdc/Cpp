/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CROUTE.H
 * Author          : Jayanth Dodderi Chidanand
 * Description     : It contains the declaration of the Class CRoute
 *
 *
 ****************************************************************************/

#ifndef CROUTE_H
#define CROUTE_H

#include <string>
#include <list>
#include "CWaypoint.h"
#include "CPOI.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"

//MACROS
#define CROUTE_DEFAULT_VALUE		0

class CPOI;
class CWaypoint;
class CPoiDatabase;

class CRoute {
	// binary operator
	// as C function, therefore friend needed
	//+ with 2 CRoute objects
	friend CRoute operator+( CRoute &Croute1, CRoute &Croute2);
private:
	/**
	 * Pointer to the Waypoint Objects.
	 * @link aggregationByValue
	 * @supplierCardinality 1.....4
	 * @clientCardinality 1
	 */
	//CWaypoint* m_pWaypoint;
	/**
	 * Maximum number of Waypoints allowed in the CRoute..
	 */
	//unsigned int m_maxWp;
	/**
	 * Index for storing the SuccessiveWaypoints in the CRoute..
	 */
	//unsigned int m_nextWp;
	/**
	 * DoublePointer for storing the addesses of POI's from database of type CPOI.
	 */
	//CPOI** m_pPoi;
	/**
	 * Maximum number of POI's  in the CRoute..
	 */
	//unsigned int m_maxPoi;
	/**
	 * Index for storing the SuccessivePOI's in the Route.
	 */
	//unsigned int m_nextPoi;
	/**
	 * Pointer to connect to the CPoiDatabase.
	 * @link aggregation
	 * @supplierCardinality 1..*
	 * @clientCardinality 1
	 */
	/*
	 * An associative container
	 * Here the pointers of Waypoints and POIs are stored
	 *
	 */
	std::list<CWaypoint*>  my_route;

	/*
	 * Pointer to connect to POIDatabase
	 **/
	CPoiDatabase* m_pPoiDatabase;
	/*
	 * Pointer to connect to CWpDatabase
	 **/
	CWpDatabase* m_pWpDatabase;
	/*
	 * Number of Waypoints present in the route
	 * */
	int m_num_WayPoint;
	/*
	 * Number of POI's present in the route
	 * */
	int m_num_poi;

public:

	/**
	 * The Constructor of the CRoute, which allows to set the initial value to the member attributes.
	 * The Constructor is a default constructor.
	 */
	CRoute();

	/**
	 * The CopyConstructor of the CRoute, which allows to copy an object an existing object of type Croute to an new object.
	 */
	CRoute(CRoute const& origin);

	/**
	 * This function connects the CRoute. to the CPoiDatabase.
	 * @param CPoiDatabase*  pPoiDB :  pointer of type CPoiDatabase which will be linking the Database to CRoute(IN)
	 * return type : void
	 */
	void connectToPoiDatabase(CPoiDatabase*  pPoiDB);

	/**
	 * This function connects the CRoute. to the CWpDatabase.
	 * @param CWpDatabase*  pWPDB :  pointer of type CWpDatabase which will be linking the Database to CRoute(IN)
	 * return type : void
	 */
	void connectToWpDatabase(CWpDatabase*  pWpDB);
	/**
	 * Adds a Waypoint to the CRoute.
	 * @param CWaypoint string name : name of the CWaypoint to be added to CRoute (IN)
	 * return type : void
	 */
	void addWaypoint(std::string name);

	/**
	 * Adds a POI to the CRoute.
	 * @param string namePoi: name of the POI to be added to CRoute (IN)
	 * return type : void
	 */
	void addPoi(std::string namePoi,std::string afterWp);

	/**
	 * Prints the CRoute. .
	 * return type : void
	 */
	void print();

	/**
	 * Calculates the distance between the Waypoint and POI and returns it.
	 * @param CWaypoint const & wp : a Constant Waypoint object passed by reference.(IN)
	 * @param CPOI& poi :The POI passed as refernce (OUT)
	 * return type : double
	 */
	double getDistanceNextPoi(CWaypoint const & wp, CPOI& poi);

	/**
	 * Destructor to clear the object and memory allocated dynamically.
	 */
	~CRoute();
	/*
	 * Overloaded operator for adding a POI or Waypoint to the route
	 * */
	void operator+=(std::string name);
	/*
	 * Overloaded assignment operator = copying the contents of one route to another
	 * */
	CRoute& operator=(const CRoute& rop);
};


/********************
 **  CLASS END
 *********************/
#endif /* CROUTE_H */
