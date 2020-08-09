/*
 * CSong.h
 *
 *  Created on: Aug 9, 2020
 *      Author: JAYANTH
 */

#ifndef CSONG_H_
#define CSONG_H_
#include<iostream>
using namespace std;

class CSong
{
friend ostream&  operator << (ostream &out , const CSong Song);
private:
	std::string m_title;
	std::string m_singer;

public:
	CSong();
	CSong(const string &songtitle, const string &singer);
	~CSong();
	string getTitle( )const ;
	string getSinger( );
	bool operator < (const CSong & song);
	bool operator == ( const CSong & song);
};

#endif /* CSONG_H_ */
