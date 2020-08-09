/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPersistentStorage.C
 * Author          : Jayanth Dodderi Chidanand
 * Description     : It contains the definition for the Class CPersistentStorage
 *
 ****************************************************************************/

#include"CPersistentStorage.h"
#include<iostream>
#include<string>
using namespace std;


//Own Include Files
#include "CPersistentStorage.h"

#define CPOIDATABASE_DEBUG			0
//Method Implementations
/********************************************************************************************/

CPersistentStorage::~CPersistentStorage()
{
#if  CPERSISTENT_DEBUG
	cout<<"Pure Virtual destructor is called"<<std::endl;
#endif
}
/********************************************************************************************/
