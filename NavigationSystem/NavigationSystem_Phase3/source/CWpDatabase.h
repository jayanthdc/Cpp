/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CWPDATABASE.H
 * Author          :
 * Description     :
 *
 *
 ****************************************************************************/

#ifndef CWPDATABASE_H
#define CWPDATABASE_H

#include <string>
#include <map>
#include "CWaypoint.h"
#include "CDatabase.h"

class CWpDatabase	: public CDatabase< std:: string ,CWaypoint>
//< std::map<std::string,CWaypoint>, CWaypoint	, std::map<std::string,CWaypoint>::iterator	>

{
private:
	/*
	 * An associative container ,with key value mapping
	 * here the name of the Waypoint is used as a key (string)
	 * the CWayPoint is a value to be stored in the container.
	 */
	std::map<std::string, CWaypoint> m_WayPoint;

public:
	/**
	 * The Constructor of the CWpDatabase, which allows to set the initial value to the member attributes.
	 * The Constructor is a default constructor.
	 */
	CWpDatabase();
	/**
	 * This adds an CWaypoint to the CWpDatabase.
	 * @param CPOI const& wp: the wp which needs to be added to the CWpDatabase.(IN)
	 * return type : void
	 */
	//void  addWaypoint(CWaypoint const& wp);
	void addWaypoint(std::string key,const CWaypoint& wp);
	/**
	 * Returns an pointer to the POI for the string being passed on to it.
	 * @param string name : name of the wp to be searched inside the Database.(IN)
	 * return type Ptr to an object of type CWaypoint
	 */
	CWaypoint* getPointerToWaypoint(std::string name);

	/**
	 * Returns the Current values of the CWaypointDatabase data members by reference
	 * std::map<std::string, CWaypoint> &WpMap - The parameter is copied  with the current CWpDatabase.(OUT)
	 * @returntype : void
	 */
	void getWpDatabaseByReference(std::map<std::string, CWaypoint> &WpMap) const;
	/*
	 * Prints the contents of the CWaypoint Database
	 */
	void print();
	/*
	 * Clears the contents of the CWaypoint Database
	 */
	void clearWpDatabase();


};
/********************
 **  CLASS END
 *********************/
#endif /* CWPDATABASE_H */
