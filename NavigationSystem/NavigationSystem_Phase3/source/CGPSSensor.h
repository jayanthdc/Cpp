/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CGPSSENSOR.H
 * Author          : Jayanth Dodderi Chidanand
 * Description     : This file contains all the methods declarations and class
 *					 definition of the Class CGPSSensor
 *
 ****************************************************************************/

#ifndef CGPSSENSOR_H
#define CGPSSENSOR_H

#include "CWaypoint.h"

//macro
#define GPSSENSOR_CLASS_DEBUG	0


class CGPSSensor
{

public:

    /**
     * The Constructor of the CGPSSensor , which allows to set the initial value to the member attributes.
     * The Constructor is a default constructor. 
     */
	CGPSSensor();

    /**
     * Returns the Current position i.e a Waypoint after receiving the input from the user. 
     * @param returntype : CWaypoint
     */
	CWaypoint getCurrentPosition();


};
/********************
 **  CLASS END
 *********************/
#endif /* CGPSSENSOR_H */
