/*
 * CJsonPersistence.cpp
 *
 *  Created on: Dec 18, 2018
 *      Author: JAYANTH DC
 */


#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string.h>
#include <algorithm>
#include "CJsonPersistence.h"
#include "CWpDatabase.h"
#include "CPoiDatabase.h"
#include "CJsonScanner.h"
#include "CJsonToken.h"
#include "CJsonInvalidCharacterException.h"
using namespace std;

#include "CJsonPersistence.h"

#define TRUE																	1
#define FALSE																0
#define CJSON_DEBUG													0
#define WP_MAX_ATTRIBUTES_COUNT						3
#define POI_MAX_ATTRIBUTES_COUNT						5

typedef enum
{
	WAITING_FOR_FIRST_TOKEN,
	WAITING_FOR_DB_NAME,
	WAITING_FOR_DB_BEGIN,
	WAITING_FOR_ATTRIBUTE_NAME,
	WAITING_FOR_ATTRIBUTE_VALUE,
	WAITING_FOR_NAME_SEPARATOR,
	WAITING_FOR_VALUE_SEPARATOR,
}JsonParser_States ;


typedef struct
{
	bool DatabaseObject  ;
	bool DatabaseAttributeName ;
	bool DatabaseAttributeLatitude   ;
	bool DatabaseAttributeLongitude ;
	bool DatabaseAttributeType   ;
	bool DatabaseAttributeDescription ;
}JsonParserFlagStruct;

typedef enum{ EMPTY, WAYPOINT_DB,CPOI_DB }database_t;
/*********************************************************************************************************/
CJsonPersistence:: CJsonPersistence()
{
#if 	CJSON_DEBUG

	cout<<"Created a Constructor for the CJsonPersistence Class"<<endl;

#endif
}
/*********************************************************************************************************/
void CJsonPersistence::setMediaName(std::string name)
{
	string fileExtension="_Json.txt";

	m_myjsonFileName = name + fileExtension; //json.txt

#if CJSON_DEBUG
	cout<<m_myjsonFileName<<endl;
#endif
}
/*********************************************************************************************************/
bool CJsonPersistence::writeData(const CWpDatabase& waypointDb,	const CPoiDatabase& poiDb)
{
	/* Local variables declarations */
	bool returnValue = TRUE;
	bool WpdataFlag = FALSE;
	std::map<std::string, CWaypoint> m_jsonWayPoint;
	std::map<std::string, CPOI> m_jsonPOI;

	/*Creating a local copy of the Waypoint database */
	waypointDb.getWpDatabaseByReference(m_jsonWayPoint);

	/*Creating a local copy of the Cpoi database */
	poiDb.getPoiDatabaseByReference(m_jsonPOI);

	/*ofstream class is used  for writing the data to the file */
	ofstream fout;

	fout.open (m_myjsonFileName.c_str(), ios::out );
	if (NULL == fout )
	{
		cout<<"JSONfile could not be opened"<<endl;
		returnValue = FALSE;
		return returnValue ;
	}
	else
	{
		if (m_jsonWayPoint . empty( ) )
		{
			cout << "Waypoint database is empty " << endl;
		}
		else
		{
#if CJSON_DEBUG
			cout<< "WpDatabase Size =  " << m_jsonWayPoint.size()<<endl;
#endif
			/* Write begin object character  ''   {   '' 	&  Newline character  */
			fout<< " { "	<<  "\n"  ;
			writeWpData( m_jsonWayPoint, 	fout);
			WpdataFlag = TRUE;
		}

		if (m_jsonPOI . empty( ) )
		{
			cout << "Poi database is empty " << endl;
			if (WpdataFlag)
			{	/* 	Write end  object character    ''  }  ''    */
				fout<<"\n"<<" } "	;
			}
		}
		else
		{
#if CJSON_DEBUG
			cout<< "PoiDatabase Size =  " << m_jsonPOI.size()<<endl;
#endif
			if (!WpdataFlag)
			{	/*		 Write begin object character  ''   {   '' 	&  Newline character  */
				fout<< " { "	<<  "\n"  ;
			}
			if(WpdataFlag)
			{
				fout<<"," <<"\n"<<"\n" ;
			}
			writePoiData( m_jsonPOI,	  fout);
			/* 	Write end  object character    ''  }  ''    */
			fout<<"\n"<<" } "	;
		}
	}
	fout.close();
	return returnValue;
}
/*********************************************************************************************************/
bool CJsonPersistence::writeWpData(	const std::map<std::string, CWaypoint>& WaypointDb,
		std::ofstream& fileptr)
{
	bool retValue = TRUE;
	unsigned int i = 0;
	std::map<std::string,CWaypoint>::const_iterator Wp_itr;
	/*	Indentation */
	fileptr<<"     ";
	/*	Object name &	Newline character*/
	fileptr<<"\""<< "waypoints"<<"\""<<" :" <<"	 ["<<  "\n" ;

	for( Wp_itr = WaypointDb.begin( );  Wp_itr != WaypointDb.end() ;  ++Wp_itr )
	{
		/*	 Write begin object character  ''   {   ''  &&	Newline character*/
		fileptr<<"     "<<" { "<<  "\n" ;
		/*	name of waypoint*/
		fileptr<< "       "<<"\""<< "name" <<"\""<< " : "<<" \" "<< Wp_itr->second.getName()<<" \" " <<"," <<"\n" ;
		/*waypoint latitude*/
		fileptr<< "       "<<"\""<< "latitude" <<"\""<< " : "<< Wp_itr->second.getLatitude()<<","<<"\n" ;
		/*waypoint longitude*/
		fileptr<< "       "<<"\""<< "longitude" <<"\""<< " : "<< Wp_itr->second.getLongitude()<<"\n" ;
		/* Write end  object character    ''  }  ''    */
		fileptr<<  "     "<<	" } ";
		if( i   !=   (WaypointDb.size( )-1)  )
		{
			fileptr<<	",";
		}
		/*	Newline character*/
		fileptr<< "\n" ;
		i++;
	}
	/*	Indentation */
	fileptr<< "    "<< " ] ";

	return retValue;
}
/*********************************************************************************************************/

bool CJsonPersistence::writePoiData(const std::map<std::string, CPOI>& poiDb,
		std::ofstream& fileptr)
{
	bool retValue = TRUE;
	unsigned int i = 0;
	std::map<std::string,CPOI>::const_iterator Cpoi_itr;

	/*	Indentation */
	fileptr<<"     ";
	/*	Object name &	Newline character*/
	fileptr<<"\""<< "pois"<<"\""<<" :" <<"	 ["<<  "\n" ;

	for( Cpoi_itr = poiDb.begin( );  Cpoi_itr != poiDb.end() ;  ++Cpoi_itr )
	{
		/*	 Write begin object character  ''   {   ''  &&	Newline character*/
		fileptr<<"     "<<" { "<<  "\n" ;
		/*	name of CPOI*/
		fileptr<< "       "<<"\""<< "name" <<"\""<< " : "<<" \" "<< Cpoi_itr->second.getName()<<" \" " <<"," <<"\n" ;
		/*CPOI latitude*/
		fileptr<< "       "<<"\""<< "latitude" <<"\""<< " : "<< Cpoi_itr->second.getLatitude()<<","<<"\n" ;
		/*CPOI longitude*/
		fileptr<< "       "<<"\""<< "longitude" <<"\""<< " : "<< Cpoi_itr->second.getLongitude()<<","<<"\n" ;
		/*CPOI type*/
		fileptr<< "       "<<"\""<< "type" <<"\""<< " : "<< " \" "<<Poi_Type[Cpoi_itr->second.getType()]<<" \" "<<","<<"\n" ;
		/*CPOI description*/
		fileptr<< "       "<<"\""<< "description" <<"\""<< " : "<< " \" "<<Cpoi_itr->second.getDescription()<<" \" "<<"\n" ;
		/* Write end  object character    ''  }  ''    */
		fileptr<<  "     "<<	" } ";
		if( i   !=   (poiDb.size( )-1)  )
		{
			fileptr<<	",";
		}
		/*	Newline character*/
		fileptr<< "\n" ;
		i++;
	}
	/*	Indentation */
	fileptr<< "    "<< " ] "	;

	return retValue;
}
/*********************************************************************************************************/
bool CJsonPersistence::readData(CWpDatabase& waypointDb ,  CPoiDatabase& poiDb ,MergeMode mode)
{
	//local variables declaration
	bool returnValue = TRUE;
	string Name,Description;
	double Latitude = 0;double Longitude = 0;
	int Attribute_Count = 0;
	bool DatabaseBegin =0;bool ArrayType=0;
	CPOI:: t_poi Type=CPOI::ZERO;

	APT ::CJsonToken::TokenType	 Ev_TokenType;
	string Poi_type;string Object_Attribute;
	JsonParserFlagStruct myJsonFlagStruct={0};

	database_t DatabaseType=EMPTY;
	JsonParser_States my_JsonState = WAITING_FOR_FIRST_TOKEN;

	cout<<"*******before adding****** "<<endl;
	waypointDb.print( );
	poiDb.print( );
	cout<<"******************************* "<<endl;

	if(REPLACE == mode)
	{
		waypointDb.clearWpDatabase();
		poiDb.clearPoiDatabase();
	}
	/*ifstream class is used  for writing the data to the file */
	ifstream fin;

	fin.open(m_myjsonFileName.c_str( ),ios::in);
	if(!fin)
	{
		cout<<"WayPointFile could not be opened"<<endl;
		return returnValue;
	}
	else
	{
		APT::CJsonScanner my_JsonScanner(fin);
		APT:: CJsonToken *my_JsonTokenPtr	= NULL;

		try
		{
			my_JsonTokenPtr = my_JsonScanner.nextToken( );
		}
		catch ( CJsonInvalidCharacterException  &InvalidChar )
		{
			cout << InvalidChar.what()<<endl;
			InvalidChar.getInvalidToken();
			InvalidChar.getLineNumber();
		}

		while(my_JsonTokenPtr != NULL)
		{
			/*EVent read which is the token type of the object being pointed */
			Ev_TokenType = my_JsonTokenPtr->getType();


			if((Attribute_Count == WP_MAX_ATTRIBUTES_COUNT)	&&	(DatabaseType ==WAYPOINT_DB)	)
			{
				if( (myJsonFlagStruct.DatabaseAttributeName==0 )|| (myJsonFlagStruct.DatabaseAttributeLatitude==0 ) ||
						(myJsonFlagStruct.DatabaseAttributeLongitude==0 ) )
				{
					cout<< "Error : Repeated  or different attributes added to Waypoint Object , found at line number: "<<
							my_JsonScanner.scannedLine() - 1 <<endl;
					Attribute_Count = 0;
				}
			}

			if((Attribute_Count == POI_MAX_ATTRIBUTES_COUNT)	&&	(DatabaseType ==CPOI_DB)	)
			{
				if(	 (myJsonFlagStruct.DatabaseAttributeName==0 ) || (myJsonFlagStruct.DatabaseAttributeLatitude==0 ) ||
						(myJsonFlagStruct.DatabaseAttributeLongitude==0 ) ||  (myJsonFlagStruct.DatabaseAttributeLongitude==0 )||
						(myJsonFlagStruct.DatabaseAttributeLongitude==0 )		 )
				{
					cout<< "Error : Repeated  or different attributes added to CPOI Object , found at line number: "<<
							my_JsonScanner.scannedLine() - 1 <<endl;
					Attribute_Count = 0;
				}
			}

			switch(my_JsonState)
			{
			case WAITING_FOR_FIRST_TOKEN	:

				if(  Ev_TokenType == APT::CJsonToken:: BEGIN_OBJECT	 )
				{
					my_JsonState = WAITING_FOR_DB_NAME;
				}
				break;

			case 	WAITING_FOR_DB_NAME		:

				if(	 Ev_TokenType  == APT::CJsonToken:: STRING )
				{
					APT:: CJsonStringToken* myTokenValue = dynamic_cast<APT::CJsonStringToken*>(my_JsonTokenPtr);
					if( ( myTokenValue->getValue( ) =="waypoints") || (myTokenValue->getValue() =="pois") )
					{
						//Perform Action
						DatabaseBegin = 1;

						if(myTokenValue->getValue() == "waypoints")
							DatabaseType =WAYPOINT_DB;

						if(myTokenValue->getValue() == "pois")
							DatabaseType =CPOI_DB;
					}
					my_JsonState = WAITING_FOR_NAME_SEPARATOR;
				}
				if(	Ev_TokenType == APT::CJsonToken:: END_OBJECT )
				{
					my_JsonState = WAITING_FOR_FIRST_TOKEN;
				}

				break;

			case WAITING_FOR_DB_BEGIN:

				if( Ev_TokenType == APT::CJsonToken:: BEGIN_ARRAY )
				{
					ArrayType = 1;
				}
				if ( Ev_TokenType == APT::CJsonToken::  BEGIN_OBJECT)
				{
					//to do :
					my_JsonState = WAITING_FOR_ATTRIBUTE_NAME;
				}
				if( Ev_TokenType == APT::CJsonToken:: VALUE_SEPARATOR)
				{
					my_JsonState = WAITING_FOR_DB_NAME;
				}
				break;

			case WAITING_FOR_ATTRIBUTE_NAME:

				if( Ev_TokenType == APT::CJsonToken:: STRING )
				{
					APT:: CJsonStringToken* myTokenValue = dynamic_cast<APT::CJsonStringToken*>(my_JsonTokenPtr);
					Object_Attribute =  myTokenValue->getValue( ) ;

					myJsonFlagStruct.DatabaseObject= 1;
					my_JsonState = WAITING_FOR_NAME_SEPARATOR;
				}
				break;

			case WAITING_FOR_NAME_SEPARATOR :

				if(	Ev_TokenType  == APT::CJsonToken:: NAME_SEPARATOR )
				{
					if (DatabaseBegin	)
					{
						my_JsonState = WAITING_FOR_DB_BEGIN;
						DatabaseBegin	 = 0;
					}
					else if(	myJsonFlagStruct.DatabaseObject	)
					{
						my_JsonState = WAITING_FOR_ATTRIBUTE_VALUE;
					}
				}
				break;

			case WAITING_FOR_ATTRIBUTE_VALUE:

				if(Ev_TokenType ==  APT::CJsonToken:: STRING)
				{
					APT:: CJsonStringToken* myTokenValue = dynamic_cast<APT::CJsonStringToken*>(my_JsonTokenPtr);

					if(Object_Attribute =="name")
					{
						Name =myTokenValue->getValue();					//Name
						myJsonFlagStruct.DatabaseAttributeName = 1;
						Attribute_Count++;
					}
					else if(Object_Attribute =="type")		//Type
					{
						Poi_type =myTokenValue->getValue();
						if(strcmp(Poi_type.c_str(), "RESTAUTANT")== 0 )
							Type = CPOI::RESTAURANT ;

						else if (strcmp(Poi_type.c_str(),"TOURISTIC") == 0)
							Type =CPOI::TOURISTIC ;

						else if (strcmp(Poi_type.c_str(),"GASSTATION") == 0)
							Type= CPOI::GASSTATION ;

						else
							Type =CPOI::UNIVERSITY;

						myJsonFlagStruct.DatabaseAttributeType = 1;
						Attribute_Count++;
					}
					else if(Object_Attribute =="description")//Description
					{
						Description =myTokenValue->getValue();
						myJsonFlagStruct.DatabaseAttributeDescription = 1;
						Attribute_Count++;
					}
				}
				else if(Ev_TokenType ==  APT::CJsonToken:: NUMBER)
				{
					APT:: CJsonNumberToken* myTokenValue = dynamic_cast<APT::CJsonNumberToken*>(my_JsonTokenPtr);

					if(Object_Attribute =="latitude")
					{
						Latitude =myTokenValue->getValue();					//Latitude
						myJsonFlagStruct.DatabaseAttributeLatitude =1;
						Attribute_Count++;
					}
					else if(Object_Attribute =="longitude")
					{
						Longitude =myTokenValue->getValue();				//Longitude
						myJsonFlagStruct.DatabaseAttributeLongitude=1;
						Attribute_Count++;
					}
				}
				my_JsonState =WAITING_FOR_VALUE_SEPARATOR ;
				break;


			case WAITING_FOR_VALUE_SEPARATOR:

				if(	Ev_TokenType == APT::CJsonToken:: END_ARRAY  	)
				{
					ArrayType = 0;
					myJsonFlagStruct.DatabaseObject= 0;
					DatabaseType =EMPTY;
					my_JsonState = WAITING_FOR_DB_NAME;
				}

				if(	 (Ev_TokenType == APT::CJsonToken:: VALUE_SEPARATOR  ) || (Ev_TokenType == APT::CJsonToken:: END_OBJECT ) 	)
				{
					if(		(Ev_TokenType == APT::CJsonToken:: END_OBJECT )	&& (DatabaseType ==WAYPOINT_DB) &&
							(Attribute_Count < WP_MAX_ATTRIBUTES_COUNT) 	)
					{
						myJsonFlagStruct.DatabaseObject = 0;
						myJsonFlagStruct.DatabaseAttributeName = 0;
						myJsonFlagStruct.DatabaseAttributeLatitude = 0;
						myJsonFlagStruct.DatabaseAttributeLongitude  = 0;
						Attribute_Count = 0;
						cout<<"Less number of attributes for waypoint object"<<endl;
						cout<<"Error found at line number : " << my_JsonScanner.scannedLine( ) - 1 <<endl;
					}

					else if(		(Ev_TokenType == APT::CJsonToken:: END_OBJECT )	&& (DatabaseType ==CPOI_DB) &&
							(Attribute_Count < POI_MAX_ATTRIBUTES_COUNT) 	)
					{
						myJsonFlagStruct.DatabaseObject = 0;
						myJsonFlagStruct.DatabaseAttributeName = 0;
						myJsonFlagStruct.DatabaseAttributeLatitude = 0;
						myJsonFlagStruct.DatabaseAttributeLongitude  = 0;
						Attribute_Count = 0;
						cout<<"Less number of attributes for CPOI object"<<endl;
						cout<<"Error found at line number : " << my_JsonScanner.scannedLine( ) - 1 <<endl;
					}


					else if(	 (DatabaseType ==WAYPOINT_DB)	&&	(myJsonFlagStruct.DatabaseAttributeName == 1)&&
							(myJsonFlagStruct.DatabaseAttributeLatitude == 1) &&	(myJsonFlagStruct.DatabaseAttributeLongitude == 1) )
					{
						CWaypoint myWp(Name,Latitude,Longitude);
						//m_csvWayPoint.insert( pair <string ,CWaypoint> (myWp.getName( ),myWp ) );

						waypointDb.addWaypoint(myWp.getName(),myWp);

						myJsonFlagStruct.DatabaseObject = 0;
						myJsonFlagStruct.DatabaseAttributeName = 0;
						myJsonFlagStruct.DatabaseAttributeLatitude = 0;
						myJsonFlagStruct.DatabaseAttributeLongitude  = 0;
						myJsonFlagStruct.DatabaseAttributeType = 0;
						myJsonFlagStruct.DatabaseAttributeDescription  =0;
						Attribute_Count = 0;
					}

					else if ((DatabaseType ==CPOI_DB) && (myJsonFlagStruct.DatabaseAttributeName == 1)&&
							(myJsonFlagStruct.DatabaseAttributeLatitude == 1) && 	(myJsonFlagStruct.DatabaseAttributeLongitude ==1)
							&&	(myJsonFlagStruct.DatabaseAttributeType == 1) &&	(myJsonFlagStruct.DatabaseAttributeDescription == 1) )
					{
						CPOI myPoi(Type,Name,Description,Latitude,Longitude);
						//m_csvPOI.insert(pair <string ,CPOI> (myPoi.getName(),myPoi ));

						poiDb.addPoi(myPoi.getName(),myPoi);

						myJsonFlagStruct.DatabaseObject = 0;
						myJsonFlagStruct.DatabaseAttributeName = 0;
						myJsonFlagStruct.DatabaseAttributeLatitude = 0;
						myJsonFlagStruct.DatabaseAttributeLongitude  = 0;
						myJsonFlagStruct.DatabaseAttributeType = 0;
						myJsonFlagStruct.DatabaseAttributeDescription  =0;
						Attribute_Count = 0;
					}

					else
					{
						if( ( ArrayType==0 ) && ( myJsonFlagStruct.DatabaseObject ==0 ) )
						{
							my_JsonState = WAITING_FOR_DB_NAME;
						}
						else if ( (ArrayType==1 )&& ( myJsonFlagStruct.DatabaseObject ==0 ) )
						{
							my_JsonState = WAITING_FOR_DB_BEGIN;
						}
						else
						{
							my_JsonState = WAITING_FOR_ATTRIBUTE_NAME;
						}
					}
				}
				break;

			default :
				break;
			}
			try
			{
				my_JsonTokenPtr = my_JsonScanner.nextToken( );
			}

			catch ( CJsonInvalidCharacterException  &InvalidChar )
			{
				cout << InvalidChar.what()<<endl;
				InvalidChar.getInvalidToken();
				InvalidChar.getLineNumber();
			}
		}
	}

	fin.close();

	cout<< " **********After adding ***********"<<endl;
	waypointDb.print( );
	poiDb.print( );
	return returnValue;
}
/*********************************************************************************************************/
CJsonPersistence::~CJsonPersistence()
{
#if CJSON_DEBUG
	cout<< "Default constructor for the CCSV Class\n" << endl;
#endif
}
/*********************************************************************************************************/
