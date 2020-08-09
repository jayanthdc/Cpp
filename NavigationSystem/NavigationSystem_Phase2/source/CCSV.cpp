
/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CCSV.cpp
 * Author          : Jayanth Dodderi Chidanand
 * Description     : This file contains the definition for the member functions of
 * 					 the Class CCSV
 *
 ****************************************************************************/

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string.h>
#include <algorithm>
#include "CCSV.h"
#include "CPOI.h"
#include "CWpDatabase.h"
#include "CPoiDatabase.h"
using namespace std;


#define TRUE						1
#define FALSE						0
#define DECIMAL_POINTS_LIMIT		1
#define AVG_WAYPT_DELIMIT_COUNT		2
#define AVG_CPOI_DELIMIT_COUNT		4

#define CCSV_DEBUG 0
/**************************************************************************************/

const char* Errortable[] =
{
		/*RT_SUCCESS*/				"**Successfully completed**",
		/*RT_ERROR_LESS_FIELDS*/	"**Too few fields**",
		/*RT_ERROR_MORE_FIELDS*/	"**More fields**",
		/*RT_ERROR_TEXT_INVALID*/	"**Invalid Data**",
		/*RT_ERROR_NUMBER_INVALID*/ "**Invalid Number**",
		/*RT_ERROR_COMMA_INVALID*/	"**German editor**",
		/*RT_ERROR_TEXT_MISSING*/	"**Empty Field**",
		/*RT_ERROR_NUMBER_MISSING*/ "**Empty Field**",
		/*RT_ERROR_TYPE_INVALID*/	"**Not a valid type of POI**",
		/*RT_ERROR_TYPE_MISSING*/   "**Type Field of CPOI missing**"
		/*RT_ERROR*/				"**Generic Error**"

};

/**************************************************************************************/
CCSV::CCSV()
{
	m_csv_fileLineNum = 0;

#if CSV_DEBUG
	cout<< "Default constructor for the CCSV Class\n" << endl;
#endif
}
/**************************************************************************************/
void CCSV::setMediaName(std::string name)
{
	string wp="-wp.txt";
	string poi="-poi.txt";

	m_csv_fileName1 = name + wp; //wp.txt
	m_csv_fileName2 = name + poi;//poitxt
#if CCSV_DEBUG
	cout<<m_csv_fileName1<<endl<<m_csv_fileName2<<endl;
#endif
}
/**************************************************************************************/
bool CCSV::writeData(const CWpDatabase& waypointDb, const CPoiDatabase& poiDb)
{
	string name,description;
	double latitude,longitude = 0;
	CPOI::t_poi  type;
	std::map<std::string, CWaypoint> m_csvWayPoint;
	std::map<std::string, CPOI> m_csvPOI;
	bool returnVal = FALSE;

	/*Creating a local copy of the Waypoint database */
	waypointDb.getWpDatabaseByReference(m_csvWayPoint);

	/*Creating a local copy of the Cpoi database */
	poiDb.getPoiDatabaseByReference(m_csvPOI);

	/*ofstream class is used  for writing the data to the file */
	ofstream fout;

	fout.open(m_csv_fileName1.c_str(),ios::out);

	if(!fout )
	{
		cout<<"CWaypointFile could not be opened"<<endl;
		return returnVal;
	}
	else
	{
		map<string,CWaypoint>::iterator Waypoint_Itr;

		for(Waypoint_Itr = m_csvWayPoint.begin();Waypoint_Itr != m_csvWayPoint.end();
				++Waypoint_Itr)
		{
			/*Write Name of the Waypoint to the file with separator*/
			fout<< Waypoint_Itr->second.getName()<<";";
			/*Write latitude  of the Waypoint to the file with separator */
			fout<< Waypoint_Itr->second.getLatitude()<<";";
			/*Write longitude  of the Waypoint to the file with separator */
			fout<< Waypoint_Itr->second.getLongitude();
			/*Newline character*/
			fout<<"\n";
		}
		fout.close();
		returnVal = TRUE;
	}

	if(returnVal == TRUE)
	{
		fout.open(m_csv_fileName2.c_str(),ios::out);

		if(!fout )
		{
			cout<<"CPOIDatabase_File could not be opened"<<endl;
			returnVal = FALSE;
			return returnVal ;
		}
		else
		{
			map<std::string, CPOI>:: iterator CPOI_Itr;

			for(CPOI_Itr = m_csvPOI.begin(); CPOI_Itr != m_csvPOI.end(); ++CPOI_Itr)
			{
				CPOI_Itr->second.getAllDataByReference(name,latitude, longitude, type,description);

				fout<<Poi_Type[type]<<";" <<name<< ";"<<description<< ";"<<latitude<<";" <<longitude<<"\n";

			}
			fout.close();
		}
	}
	return returnVal;
}
/**************************************************************************************/
bool CCSV::readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb,
		MergeMode mode)
{
	bool returnFlag = 0;
	Returntype_t returnVal = RT_ERROR;

	std::map<std::string, CWaypoint> m_csvWayPoint;
	std::map<std::string, CPOI> m_csvPOI;

	std::map<std::string, CWaypoint> ::iterator itr_CWp;
	std::map<std::string, CPOI> ::iterator itr_Cpoi;

	returnVal = readWpData(m_csvWayPoint);
	if(RT_SUCCESS != returnVal ) //if waypoint file not read successfuly  return from function
	{
		return returnFlag;
	}

	returnVal = readPoiData(m_csvPOI);
	if(RT_SUCCESS != returnVal )//if poi file not read successfuly  return from function
	{
		return returnFlag;
	}
	/* If Mode is merge mode , then the data to be added at  the end of the container */
	if(MERGE == mode)
	{
		for(itr_CWp = m_csvWayPoint.begin();itr_CWp != m_csvWayPoint.end(); ++itr_CWp)
		{
			waypointDb.addWaypoint((*itr_CWp).second);

		}
		for(itr_Cpoi = m_csvPOI.begin();itr_Cpoi != m_csvPOI.end(); ++itr_Cpoi)
		{
			poiDb.addPoi((*itr_Cpoi).second);

		}
	}

	/* If Mode is REPLACE mode , then the data in container to be cleared and to be copied with file data*/
	if(REPLACE == mode)
	{
		waypointDb.clearWpDatabase();
		poiDb.clearPoiDatabase();
		for(itr_CWp = m_csvWayPoint.begin();itr_CWp != m_csvWayPoint.end(); ++itr_CWp)
		{
			waypointDb.addWaypoint((*itr_CWp).second);

		}
		for(itr_Cpoi = m_csvPOI.begin();itr_Cpoi != m_csvPOI.end(); ++itr_Cpoi)
		{
			poiDb.addPoi((*itr_Cpoi).second);

		}
	}
	if(RT_SUCCESS == returnVal )
		returnFlag =1;


	return returnFlag;
}
/**************************************************************************************/
Returntype_t CCSV::ParseCSVWpFile(const char* buffer,std::string& name, double& latitude,
		double& longitude)
{
	int  buf_index =0;
	int  delimiter_count = 0;
	int  name_index = 0;
	int  lat_index = 0;
	int  long_index = 0;
	char Wpname[25];
	char WpLatitude[25];
	char WpLongitude[25];
	Returntype_t returnValue = RT_ERROR;

	while(buffer[buf_index]!= '\0')
	{
		//delimiters allowed ',' ,  ';'
		if(buffer[buf_index] == ',' || buffer[buf_index] == ';')
		{
			delimiter_count ++;

		}
		else
		{
			if(delimiter_count > AVG_WAYPT_DELIMIT_COUNT)
			{
#if CCSV_DEBUG
				cout<<"Error : More fields than expected. German editor problem"<<endl;
#endif
				returnValue = RT_ERROR_MORE_FIELDS;
				ErrorReport(returnValue,buffer);
				return returnValue;
			}
			else
			{
				if(delimiter_count == 0)
				{
					Wpname[name_index] = buffer[buf_index] ;
					name_index++;
				}
				else if(delimiter_count == 1)
				{
					WpLatitude[lat_index] = buffer[buf_index] ;
					lat_index++;
				}
				else if(delimiter_count == 2)
				{
					WpLongitude[long_index] = buffer[buf_index] ;
					long_index++;
				}
			}
		}
		buf_index++;
	}
	if(delimiter_count < AVG_WAYPT_DELIMIT_COUNT)
	{
		returnValue = RT_ERROR_LESS_FIELDS;
		ErrorReport(returnValue,buffer);
		return returnValue;
	}
	//Null terminating the copied strings
	Wpname[name_index] ='\0';
	WpLatitude[lat_index]='\0';
	WpLongitude[long_index]='\0';

	//Waypoint name :validation
	returnValue = Validate_text(Wpname);
	if(RT_SUCCESS != returnValue  )
	{
		ErrorReport(returnValue,buffer);
		return returnValue;
	}

	//Waypoint's Latitude :validation
	returnValue = Validate_Number(WpLatitude);
	if(RT_SUCCESS != returnValue  )
	{
		ErrorReport(returnValue,buffer);
		return returnValue;
	}
	//Longitude content :verification
	returnValue = Validate_Number(WpLongitude);
	if(RT_SUCCESS != returnValue  )
	{
		ErrorReport(returnValue,buffer);
		return returnValue;
	}
	if(returnValue == RT_SUCCESS)
	{
		name = Wpname;
		latitude = atof(WpLatitude);
		longitude = atof(WpLongitude);
#if CCSV_DEBUG
		cout<<"waypoint name: "<<name <<" latitude val = "<<latitude
				<<" longitude val = "<<longitude<<endl;
#endif
	}

	return returnValue;
}
/**************************************************************************************/
Returntype_t CCSV::ParseCSVPOIFile(const char* buffer,std::string& name, double& latitude,
		double& longitude, std::string& description, CPOI::t_poi& type)
{

	int  buf_index =0;
	int  delimiter_count = 0;
	int  name_index = 0;
	int  lat_index = 0;
	int  long_index = 0;
	int  desc_index = 0;
	int  type_index = 0;
	char PoiType[25];
	char PoiDescription[50];
	char Poiname[25];
	char PoiLatitude[25];
	char PoiLongitude[25];
	Returntype_t returnValue = RT_ERROR;


	while(buffer[buf_index]!= '\0')		//GG-PALYA;11.3;11.4
	{
		if(buffer[buf_index] == ',' || buffer[buf_index] == ';')
		{
			delimiter_count ++;

		}
		else
		{
			if(delimiter_count > AVG_CPOI_DELIMIT_COUNT)
			{
#if CCSV_DEBUG
				cout<<"Error : More fields than expected. German editor problem"<<endl;
#endif
				returnValue = RT_ERROR_MORE_FIELDS;
				ErrorReport(returnValue,buffer);
				return returnValue;
			}
			else
			{
				if(delimiter_count == 0)
				{
					PoiType[type_index] = buffer[buf_index] ;
					type_index++;
				}
				else if(delimiter_count == 1)
				{
					Poiname[name_index] = buffer[buf_index] ;
					name_index++;
				}
				else if(delimiter_count == 2)
				{
					PoiDescription[desc_index] = buffer[buf_index] ;
					desc_index++;
				}
				else if(delimiter_count == 3)
				{
					PoiLatitude[lat_index] = buffer[buf_index] ;
					lat_index++;
				}
				else if(delimiter_count == 4)
				{
					PoiLongitude[long_index] = buffer[buf_index] ;
					long_index++;
				}
			}

		}
		buf_index++;
	}
	if(delimiter_count < AVG_CPOI_DELIMIT_COUNT)
	{
		returnValue = RT_ERROR_LESS_FIELDS;
		ErrorReport(returnValue,buffer);

		return returnValue;

	}
	PoiType[type_index] ='\0';
	Poiname[name_index]='\0';
	PoiDescription[desc_index]='\0';
	PoiLatitude[lat_index]='\0';
	PoiLongitude[long_index]='\0';

	//CPOI type :validation
	returnValue = Validate_type(PoiType);
	if(RT_SUCCESS != returnValue  )
	{
		ErrorReport(returnValue,buffer);
		return returnValue;
	}
	else
	{
		if(strcmp(PoiType, "RESTAUTANT")== 0 )
			type = CPOI::RESTAURANT;

		else if (strcmp(PoiType,"TOURISTIC") == 0)
			type =CPOI::TOURISTIC;

		else if (strcmp(PoiType,"GASSTATION") == 0)
			type = CPOI::GASSTATION;

		else
			type =CPOI::UNIVERSITY;

	}

	//CPOI name :validation
	returnValue = Validate_text(Poiname);

	if(RT_SUCCESS != returnValue  )
	{
		ErrorReport(returnValue,buffer);
		return returnValue;
	}

	//CPOI description :validation
	returnValue = Validate_text(PoiDescription);
	if(RT_SUCCESS != returnValue  )
	{
		ErrorReport(returnValue,buffer);
		return returnValue;
	}

	//CPOI LATITUDE :validation
	returnValue = Validate_Number(PoiLatitude);
	if(RT_SUCCESS != returnValue  )
	{
		ErrorReport(returnValue,buffer);
		return returnValue;
	}

	//CPOI LONGITUDE :validation
	returnValue = Validate_Number(PoiLongitude);
	if(RT_SUCCESS != returnValue  )
	{
		ErrorReport(returnValue,buffer);
		return returnValue;
	}

	name = Poiname;
	description =PoiDescription;
	latitude = atof(PoiLatitude);
	longitude = atof(PoiLongitude);

#if 0
	cout<<"CPOI name: "<<name<< "description:" <<description <<" latitude val = "<<latitude
			<<" longitude val = "<<longitude<< "Type"<<type<<endl;
#endif

	return returnValue;
}
/**************************************************************************************/
Returntype_t CCSV::Validate_text(const char* buffer)
{
	Returntype_t returnVal = RT_SUCCESS;
	int buf_index= 0;
	while(buffer[buf_index]!= '\0')		//GG-PALYA;11.3;11.4
	{
		if( ( isalpha(buffer[buf_index]) ) || (buffer[buf_index] == ' ')|| (buffer[buf_index] == '_')  )
		{
			buf_index++;
		}
		else
		{
			returnVal = RT_ERROR_TEXT_INVALID;
			return returnVal;
		}
	}
	if(!buf_index)
	{
		returnVal = RT_ERROR_TEXT_MISSING;
		return returnVal;
	}
	return returnVal;
}
/**************************************************************************************/
Returntype_t CCSV::Validate_Number(const char* buffer)
{
	Returntype_t returnVal = RT_SUCCESS;
	int buf_index= 0;
	int dotCount =0;
	while(buffer[buf_index]!= '\0')
	{
		if( ( isdigit(buffer[buf_index]) ) || (buffer[buf_index] == '.') )
		{
			if(buffer[buf_index] == '.')
			{
				dotCount++;
				if(dotCount > DECIMAL_POINTS_LIMIT)
				{
					returnVal = RT_ERROR_NUMBER_INVALID;
#if CCSV_DEBUG
					cout<<"MORE DOTS"<<endl;
#endif
					return returnVal;
				}
			}
			buf_index++;
		}
		else
		{
			returnVal = RT_ERROR_NUMBER_INVALID;
			return returnVal;
		}
	}
	if(!buf_index)
	{
		returnVal = RT_ERROR_NUMBER_MISSING;
		return returnVal;
	}
	return returnVal;
}
/**************************************************************************************/
Returntype_t CCSV::Validate_type(const char* buffer)
{
	Returntype_t returnVal = RT_SUCCESS;
	int buf_index= 0;
	while(buffer[buf_index]!= '\0')		//GG-PALYA;11.3;11.4
	{
		if( ( buffer[buf_index]>='A' && buffer[buf_index]<='Z') )
		{
			buf_index++;
		}
		else
		{
			returnVal = RT_ERROR_TYPE_INVALID;
			return returnVal;
		}
	}
	if(!buf_index)
	{
		returnVal = RT_ERROR_TYPE_MISSING;
		return returnVal;
	}
	return returnVal;
}

/**************************************************************************************/
Returntype_t CCSV::readWpData(std::map<std::string, CWaypoint>& waypoint)
{
	string name;
	double latitude;
	double longitude;
	string str1;
	Returntype_t returnVal = RT_SUCCESS;

	/*ifstream class is used  for writing the data to the file */
	ifstream fin;

	fin.open(m_csv_fileName1.c_str(),ios::in);

	if(!fin)
	{
		cout<<"WayPointFile could not be opened"<<endl;
		return returnVal;
	}
	else
	{


		while(getline(fin,str1))
		{
			//cout<<str1<<endl;
			m_csv_fileLineNum ++;

			const char *str = str1.c_str();
			returnVal = ParseCSVWpFile(str,name,latitude,longitude);

			if(returnVal == RT_SUCCESS)
			{
#if CCSV_DEBUG
				cout<<name1<<endl;
				cout<<latitude1<<endl;
				cout<<longitude1<<endl;
#endif
				//addWaypoint
				CWaypoint wp(name,latitude,longitude);
				waypoint.insert(pair <string ,CWaypoint> (wp.getName(),wp ));
			}
		}
		m_csv_fileLineNum = 0;
	}
	return returnVal;
}
/**************************************************************************************/
Returntype_t CCSV::readPoiData(std::map<std::string, CPOI>& Cpoi)
{
	Returntype_t returnVal = RT_SUCCESS;
	string name;
	string description;
	double latitude;
	double longitude;
	CPOI::t_poi type;

	string str1;

	/*ifstream class is used  for writing the data to the file */
	ifstream fin;

	fin.open(m_csv_fileName2.c_str(),ios::in);
	if(!fin)
	{
		cout<<"WayPointFile could not be opened"<<endl;
		return returnVal;
	}
	else
	{
		while(getline(fin,str1))
		{
			//cout<<str1<<endl;
			m_csv_fileLineNum ++;

			const char *str = str1.c_str();
			returnVal = ParseCSVPOIFile(str,name,latitude,longitude,description,type);

			if(returnVal == RT_SUCCESS)
			{
				//addPOI
				CPOI Poi(type,name,description,latitude,longitude);
				Cpoi.insert(pair <string ,CPOI> (Poi.getName(),Poi ));
			}
		}
		m_csv_fileLineNum = 0;
	}
	return returnVal;
}
/**************************************************************************************/

void CCSV::ErrorReport(Returntype_t error_type ,string content)
{
	switch(error_type)
	{
	case RT_ERROR_LESS_FIELDS:

		cout<<Errortable[RT_ERROR_LESS_FIELDS] << " in line "<< m_csv_fileLineNum<<" " << " : Errorcontent [" <<
		" "<< content <<"]"<<endl<<endl;
		break;

	case RT_ERROR_MORE_FIELDS:
		cout<<Errortable[RT_ERROR_MORE_FIELDS] << " in line "<<m_csv_fileLineNum<< "  " << " : Errorcontent [" <<
		" "<< content <<"]"<<endl<<endl;
		break;

	case RT_ERROR_TEXT_INVALID:
		cout<<Errortable[RT_ERROR_TEXT_INVALID] << " in line "<<m_csv_fileLineNum<<"  " << ": Error content [" <<
		" "<< content <<"]"<<endl<<endl;
		break;

	case RT_ERROR_NUMBER_INVALID:
		cout<<Errortable[RT_ERROR_NUMBER_INVALID] << " in line "<<m_csv_fileLineNum <<"  " << ": Error content [" <<
		" "<< content <<"]"<<endl<<endl;
		break;

	case RT_ERROR_COMMA_INVALID:
		cout<<Errortable[RT_ERROR_COMMA_INVALID] << " in line "<< m_csv_fileLineNum <<"  " << ": Error content [" <<
		" "<< content <<"]"<<endl<<endl;
		break;

	case RT_ERROR_TEXT_MISSING:
		cout<<Errortable[RT_ERROR_TEXT_MISSING] << " in line "<< m_csv_fileLineNum <<" " << ": Error content [" <<
		" "<< content <<"]"<<endl<<endl;
		break;

	case RT_ERROR_NUMBER_MISSING:
		cout<<Errortable[RT_ERROR_NUMBER_MISSING] << "in line "<< m_csv_fileLineNum <<" " << ": Error content[" <<
		" "<< content <<"]"<<endl<<endl;
		break;

	case RT_ERROR_TYPE_INVALID:
		cout<<Errortable[RT_ERROR_TYPE_INVALID] << "in line "<< m_csv_fileLineNum <<" " << ": Error content [" <<
		" "<< content <<"]"<<endl<<endl;
		break;

	default :
		break;
	}
}
/**************************************************************************************/
CCSV::~CCSV()
{
	//cout<< "Default constructor for the CCSV Class\n" << endl;

}

/**************************************************************************************/
