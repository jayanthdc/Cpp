/*******************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CCSV.H
 * Author          : Jayanth Dodderi Chidanand
 * Description     : It contains the declaration and definition of the Class CCSV
 *
 ******************************************************************************/
#ifndef MYCODE_CCSV_H_
#define MYCODE_CCSV_H_

#include<string>
#include "CPersistentStorage.h"

typedef enum
{
	RT_SUCCESS           =  0, /**< \brief Function was successfully completed>  */
	RT_ERROR_LESS_FIELDS,      /**< \brief few fields*/
	RT_ERROR_MORE_FIELDS,      /**< \brief More fields*/
	RT_ERROR_TEXT_INVALID,    /**< \brief invlalid string*/
	RT_ERROR_NUMBER_INVALID,   /**< \brief invalid number*/
	RT_ERROR_COMMA_INVALID ,  /**< \brief GERMAN editor problem, expected . for decimal notation*/
	RT_ERROR_TEXT_MISSING,    //empty string ;
	RT_ERROR_NUMBER_MISSING,  // no number present
	RT_ERROR_TYPE_INVALID,   //Type of CPOI is invalid
	RT_ERROR_TYPE_MISSING,   //Type of CPOI missing
	RT_ERROR
}Returntype_t;

class CCSV:public CPersistentStorage
{

protected:
	/**
	 * Name of the CSVFile1 in .txt
	 */
	std :: string m_csv_fileName1;
	/**
	 * Name of the CSVFile2 in .txt
	 */
	std :: string m_csv_fileName2;
	/*
	 * Line number in the csv file
	 * */
	int m_csv_fileLineNum;

public:
	/**
	 * The Constructor of the CCSV , which allows to set the initial value to the member attributes.
	 * The Constructor is a default constructor.
	 */
	CCSV();
	/**
	 * This function sets the name of the media used for storing the data.
	 * @param string name: name of the media used (IN)
	 * return type : void
	 */
	void setMediaName(std::string name) ;
	/**
	 * This function writes the data from the internal Databases to the persistet storage.
	 * @param const CWpDatabase& waypointDb : Waypoint database (IN)
	 * @param const CPoiDatabase& poiDb : POI dtabase (IN)
	 * return type : bool
	 */
	bool writeData (const CWpDatabase& waypointDb,const CPoiDatabase& poiDb) ;
	/**
	 * This function reads the data from the persistet storage and copies to internal Databases
	 * @param CWpDatabase& waypointDb : Waypoint database (IN)
	 * @param CPoiDatabase& poiDb : POI dtabase (IN)
	 * @param mode: can take values from enum {MERGE ,REPLACE};
	 * return type : bool
	 */
	bool readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb,
			MergeMode mode) ;



	/**
	 * This function Parses the CSV file of the WaypointDatabase
	 * @param  char* buffer : input buffer to be parsed (IN)
	 * @param name : string buffer to collect the waypoint name
	 * @param latitude : double buffer to collect the waypoints latitude
	 * @param longitude: double buffer to collect the waypoints longitude
	 * return type : Returntype_t{can take any values from the enum}
	 */
	Returntype_t ParseCSVWpFile(const char* buffer,std::string &name,double &latitude,double &longitude);
	/**
	 * This function Parses the CSV file of the WaypointDatabase
	 * @param  char* buffer : input buffer to be parsed (IN)
	 * @param name : string buffer to collect the waypoint name
	 * @param latitude : double buffer to collect the waypoints latitude
	 * @param longitude: double buffer to collect the waypoints longitude
	 * @param description :string buffer to collect description
	 * @param type : to store type value
	 * return type : Returntype_t{can take any values from the enum}
	 */
	Returntype_t ParseCSVPOIFile(const char* buffer,std::string &name,double &latitude,double &longitude,
			std::string &description,CPOI::t_poi &type);
	/**
	 * This function validates the string and detects errors if any character other than alphabets
	 * are encountered.
	 * @param const char* buffere : input string for validation (IN)
	 * return type :  Returntype_t{can take any values from the enum}
	 */
	Returntype_t Validate_text(const char* buffer);
	/**
	 * This function validates the string and detects errors if any character other than numbers
	 * are encountered.
	 * @param const char* buffer : input string for validation (IN)
	 * return type :  Returntype_t{can take any values from the enum}
	 */
	Returntype_t Validate_Number(const char* buffer);
	/**
	 * This function validates the string and detects errors if any character other than numbers
	 * are encountered.
	 * @param const char* buffer : input string for validation (IN)
	 * return type :  Returntype_t{can take any values from the enum}
	 */
	Returntype_t Validate_type(const char* buffer);
	/**
	 * This function reads the data from the file and writes it into this DB no errors are found in content
	 * @param map<std::string, CWaypoint>& waypointDb returntype of the Error (IN)
	 * return type :Returntype_t{can take any values from the enum}
	 */
	Returntype_t readWpData(std::map<std::string, CWaypoint>& waypointDb);

	/**
	 *This function reads the data from the file and writes it into this DB no errors are found in content
	 * @param map<std::string, CPOI>& waypointDb returntype of the Error (IN)
	 * return type : Returntype_t{can take any values from the enum}
	 */
	Returntype_t readPoiData(std::map<std::string, CPOI>& poiDb);

	/**
	 * This function prints the error messages for the various invalid data.
	 * @param Returntype_t error_type : returntype of the Error (IN)
	 * string content : the line content
	 * return type : void
	 */
	void ErrorReport(Returntype_t error_type,std::string content);
	/**
	 * The Destructor to delete the objects of the CCSV class.
	 */
	~CCSV();
};

#endif /* MYCODE_CCSV_H_ */
