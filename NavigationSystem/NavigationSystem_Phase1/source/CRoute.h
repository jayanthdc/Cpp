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


#include "CPoiDatabase.h"
#include "CWaypoint.h"
#include "CPOI.h"

//MACROS
#define CROUTE_DEFAULT_VALUE		0
#define MAX_WP_IN_ROUTE				4
#define MAX_POI_IN_ROUTE			3
#define CROUTE_DEBUG				0

class CPOI;
class CWaypoint;
class CPoiDatabase;

class CRoute {
private:
	/**
	 * Pointer to the Waypoint Objects.
	 * @link aggregationByValue
	 * @supplierCardinality 1.....4
	 * @clientCardinality 1
	 */
	CWaypoint* m_pWaypoint;
	/**
	 * Maximum number of Waypoints allowed in the CRoute..
	 */
	unsigned int m_maxWp;
	/**
	 * Index for storing the SuccessiveWaypoints in the CRoute..
	 */
	unsigned int m_nextWp;
	/**
	 * DoublePointer for storing the addesses of POI's from database of type CPOI.
	 */
	CPOI** m_pPoi;
	/**
	 * Maximum number of POI's  in the CRoute..
	 */
	unsigned int m_maxPoi;
	/**
	 * Index for storing the SuccessivePOI's in the Route.
	 */
	unsigned int m_nextPoi;
	/**
	 * Pointer to connect to the CPoiDatabase.
	 * @link aggregation
	 * @supplierCardinality 1..*
	 * @clientCardinality 1
	 */
	CPoiDatabase* m_pPoiDatabase;

public:

	/**
	 * The Constructor of the CRoute, which allows to set the initial value to the member attributes.
	 * The Constructor is a parameterized  constructor.
	 * @param unsigned int maxWp - Max Waypoints in the Route ,default 4.(IN)
	 * @param unsigned int maxPoi -Max POI's in the Route ,default 3.(IN)
	 */
	CRoute(unsigned int maxWp = MAX_WP_IN_ROUTE, unsigned int maxPoi = MAX_POI_IN_ROUTE);

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
	 * Adds a Waypoint to the CRoute.
	 * @param CWaypoint const &wp : A constant Waypoint object to be added to the CRoute
	 * return type : void
	 */
	void addWaypoint(CWaypoint const& wp);

	/**
	 * Adds a POI to the CRoute.
	 * @param string namePoi: name of the POI to be added to CRoute (IN)
	 * return type : void
	 */
	void addPoi(std::string namePoi);

	/**
	 * Prints the CRoute. .
	 * return type : void
	 */
	void print();

	/**
	 * Calculates the distance between the Waypoint and POI and returns it.
	 * @param CWaypoint const & wp : a Constant Waypoint object passed by reference.(IN)
	 * @param CPOI& poi :The POI passed as refernce (IN)
	 * return type : double
	 */
	double getDistanceNextPoi(CWaypoint const & wp, CPOI& poi);

	/**
	 * Destructor to clear the object and memory allocated dynamically.
	 */
	~CRoute();
};


/********************
 **  CLASS END
 *********************/
#endif /* CROUTE_H */
