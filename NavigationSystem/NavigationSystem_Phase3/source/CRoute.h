
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
#include <vector>
#include "CWaypoint.h"
#include "CPOI.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"

//MACROS
#define CROUTE_DEFAULT_VALUE		0


typedef enum
{
	ROUTE_ERROR =-1,
	ROUTE_SUCCESS=0,
	ROUTE_ERROR_EMPTY = 1,
	ROUTE_ERROR_DATABASE_NULL= 2,
	ROUTE_ERROR_ELEMENT_NULL= 3,
	ROUTE_ERROR_WAYPOINT_NULL=4,
	ROUTE_ERROR_POI_NULL=5,
}Route_t;

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
	CRoute( );

	/**
	 * The CopyConstructor of the CRoute, which allows to copy an object an existing object of type Croute to an new object.
	 */
	CRoute(CRoute const& origin);

	/**
	 * This function connects the CRoute. to the CPoiDatabase.
	 * @param CPoiDatabase*  pPoiDB :  pointer of type CPoiDatabase which will be linking the Database to CRoute(IN)
	 * return type : void
	 */
	//void connectToPoiDatabase(CPoiDatabase*  pPoiDB);
	Route_t connectToPoiDatabase(CPoiDatabase*  pPoiDB);
	/**
	 * This function connects the CRoute. to the CWpDatabase.
	 * @param CWpDatabase*  pWPDB :  pointer of type CWpDatabase which will be linking the Database to CRoute(IN)
	 * return type : void
	 */
	//void connectToWpDatabase(CWpDatabase*  pWpDB);
	Route_t connectToWpDatabase(CWpDatabase*  pWpDB);
	/**
	 * Adds a Waypoint to the CRoute.
	 * @param CWaypoint string name : name of the CWaypoint to be added to CRoute (IN)
	 * return type : void
	 */
	//void addWaypoint(std::string name);
	Route_t addWaypoint(std::string name);
	/**
	 * Adds a POI to the CRoute.
	 * @param string namePoi: name of the POI to be added to CRoute (IN)
	 * return type : void
	 */
	//void addPoi(std::string namePoi,std::string afterWp);
	Route_t addPoi(std::string namePoi,std::string afterWp);

	/**
	 * Prints the CRoute. .
	 * return type : void
	 */
	//void print();
	Route_t print();
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
	//void operator+=(std::string name);

	Route_t operator+=(std::string name);
	/*
	 * Overloaded assignment operator = copying the contents of one route to another
	 * */
	CRoute& operator=(const CRoute& rop);


	const std::vector<const CWaypoint*>  getRoute() ;



};


/********************
 **  CLASS END
 *********************/
#endif /* CROUTE_H */
