/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOIDATABASE.H
 * Author          : Jayanth Dodderi Chidanand
 * Description     : This file contains the definition for the Tempate Class CDatabase
 *
 ****************************************************************************/

#ifndef CDATABASE_H_
#define CDATABASE_H_

#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include "CWaypoint.h"
#include "CPoi.h"
#include <vector>
/*
 * typename T : container datatype
 */

template <typename K,typename T>

class CDatabase
{
private :

	std::map<K,T > m_database;
public:
	/**
	 * The Constructor of the CDatabase, which allows to set the initial value to the member attributes.
	 * The Constructor is a default constructor.
	 */
	CDatabase( );
	/**
	 * This adds an object to the CDatabase .
	 * @param T const& wp: the wp which needs to be added to the CWpDatabase.(IN)
	 * @param K key:the key of the object which needs to be added
	 * return type : void
	 */
	void addElementToDatabase(K key,T const &element);

	/**
	 * Returns an pointer to the POI for the string being passed on to it.
	 * @param Kname : name of the object/element to be searched inside the Database.(IN)
	 * return type Ptr to an object of type
	 */
	T* getPointerToElementInDatabase(K name);

	/**
	 * Returns the Current values of the CDatabase data members by reference
	 * T- The parameter is copied  with the current CDatabase.(OUT)
	 * @returntype : void
	 */
	void getDatabaseByReference (std::map<K, T> &Database_Element)const;
	/*
	 * Prints the contents of the CDatabase
	 */
	void printDatabase();
	/*
	 * Clears the contents of the CDatabase
	 */
	void clearDatabase();

};
/****************************************************************************/

template <typename K,typename T>
CDatabase<K,T>::CDatabase( )
{
#if	CDATABASE_DEBUG
	cout<< "Default Constructor for the CPOI Database ,no elements are initialized \n" <<endl;
#endif
}
/****************************************************************************/
template <typename K,typename T>
void  CDatabase<K,T>:: addElementToDatabase(K key , T const& element )
{
	typename std::map<K,T>::iterator myItr = m_database.find(key);

	if (myItr == m_database.end())
	{
		//	element.insert(std::make_pair(key,object));
		/*a CPOI  or an CWaypoint object is being inserted to the Cdatabase */
		m_database.insert (std::pair <K ,T> ( key , element ) );
	}
	else
	{
		std::cout << element.getName() <<" Element already present in the Container/Database" << std::endl;
	}
}
/****************************************************************************/

template <typename K,typename T>
void CDatabase<K,T>::getDatabaseByReference ( std::map<K, T> &Database_Element) const
{
	/*Copies the Waypoint/POI  Database to Element */
	Database_Element = m_database;
}
/****************************************************************************/
template <typename K,typename T>
T* CDatabase<K,T>:: getPointerToElementInDatabase(K name)
{
	T* Retptr = NULL;
	if (m_database.empty( ) )
	{
		std::cout<<" No elements in the Database "<<std::endl;
	}
	else
	{
		typename std::map<K,T>::iterator Database_Itr = m_database.find(name);
		if (Database_Itr == m_database.end())
		{
			return NULL;			//return NULL if not found
		}
		else
		{
			return &(Database_Itr->second);
		}
	}
return 	Retptr;
}
/****************************************************************************/

template <typename K,typename T>

void  CDatabase<K,T>:: printDatabase()
{
	//Iterator to iterate through the elements of the CDatabase Container.
	typename std::map<K,T>::iterator myDbItr;

	if(m_database.empty())
	{
		std::cout<< "No WayPoints in the Database" <<std::endl;
	}
	else
	{
		for( myDbItr = m_database.begin(); myDbItr != m_database.end(); ++myDbItr)
		{
			myDbItr->second.print(2);//-->DEGMMMSS;
		}
	}

}

/****************************************************************************/
template <typename K,typename T>
void  CDatabase<K , T>:: clearDatabase()
{
	/*Clears the contents of the Container(Database)*/
	m_database.clear();
}
/****************************************************************************/

typedef CDatabase<int,CWaypoint> CWpDatabaseKey_int;
typedef CDatabase<int,CPOI> CPoiDatabaseKey_int;


#endif /* CDATABASE_H_ */
