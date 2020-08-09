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

#define CPOIDATABASE_DEBUG			0
//Method Implementations
/********************************************************************************************/
CPoiDatabase::CPoiDatabase( )
{
#if	CPOIDATABASE_DEBUG
	cout<< "Default Constructor for the CPOI Database ,no elements are initialized \n" <<endl;
#endif
	CDatabase();
}
/********************************************************************************************/

void CPoiDatabase::addPoi( std::string key ,CPOI const& poi)
{
	/*a CPOI object is being inserted to the CPOI database */
	addElementToDatabase(key,poi);
}
/********************************************************************************************/

CPOI* CPoiDatabase::getPointerToPoi(string name)
{
	return getPointerToElementInDatabase( name);
}
/********************************************************************************************/
void CPoiDatabase::getPoiDatabaseByReference(
		std::map<std::string, CPOI>& Poi) const
{
	/*Copies the CPOI Database to Poi*/
	getDatabaseByReference(Poi);
}
/********************************************************************************************/
void CPoiDatabase::print()
{
	/*Prints the content of the CPOI Database	*/
	printDatabase();
}
/********************************************************************************************/
void CPoiDatabase::clearPoiDatabase()
{
	/*Clears the contents of the Container(Database)*/
	clearDatabase();
}
/********************************************************************************************/

