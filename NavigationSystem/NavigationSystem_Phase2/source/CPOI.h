/*******************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOI.H
 * Author          : Jayanth Dodderi Chidanand
 * Description     : It contains the declaration and definition of the Class CWayPoint
 *
 ******************************************************************************/

#ifndef CPOI_H
#define CPOI_H


#include "CWaypoint.h"

//macros
#define DEFAULT_POI_CORDINATE			0
#define CPOI_DEBUG						0


const std::string Poi_Type[] = { "RESTAURANT","TOURISTIC","GASSTATION" ,"UNIVERSITY"};

//CPOI is an Inherited Class of CWaypoint.

class CPOI : public CWaypoint
{
//the << operator to support cout << CPOI
friend std::ostream& operator<<(std::ostream& out, const CPOI& c);

public:

	/**
	 * An enum , to define the values for the POI's type.
	 */
	enum t_poi
	{ RESTAURANT,TOURISTIC,	GASSTATION,	UNIVERSITY};

	/**
	 * The Constructor of the CPOI , which allows to set the initial value to the member attributes.
	 * The Constructor has parameters with default values.
	 * @param t_poi type - the initial type , default Initial -"RESTAURANT" (IN)
	 * @param string name - the initial name , default Initial- "Mensa_HDA" (IN)
	 * @param string description - the initial name , default Initial-"The Best Mensa in the World" (IN)
	 * @param double latitude - the initial latitude value , default Initial 0 (IN)
	 * @param double longitude - the initial longitude value , default Initial 0 (IN)
	 */
	CPOI( t_poi type = RESTAURANT, std :: string name="Mensa_HDA",
			std ::string description ="The Best Mensa in the World",
			double latitude = DEFAULT_POI_CORDINATE, double longitude = DEFAULT_POI_CORDINATE);

	/**
	 * Sets the Current CPOI attributes.
	 * @param:  t_poi  m_type - The new POI's type  (IN)
	 * @param:  std ::string m_description - The new description of the POI(IN)
	 * @returntype  void
	 */
	void set( t_poi  m_type,std :: string name, std ::string description,double latitude, double longitude );

	/**
	 * Returns the Current values of the CPOI data members by reference
	 * @param:  string &name - The parameter is copied with the current name of POI.  (OUT)
	 * @param:  double &latitude -The parameter is copied  with  current latitude value.  (OUT)
	 * @param:  double &longitude - The parameter is copied  with  current longitude value .(OUT)
	 * @param:  t_poi  &type - The parameter is copied  with  current type value of POI .(OUT)
	 * @param:  string &description - The parameter is copied  with  current description of POI .(OUT)
	 * @returntype  void.
	 *
	 */
	void getAllDataByReference(std ::string &name, double &latitude, double &longitude, CPOI::t_poi &type,
			std ::string &description);

	/**
	 * Prints the POI.
	 * @returntype  void.
	 */
	void print(int format);

	/*
	 * Destructor to clear the object
	 */
	~CPOI();

private:
	/**
	 * The attribute  to specify the type of POI. It is an enumeration datatype  variable.
	 */
	t_poi  m_type;
	/**
	 * The description of the POI.
	 */
	std ::string m_description;
};


/********************
 **  CLASS END
 *********************/
#endif /* CPOI_H */
