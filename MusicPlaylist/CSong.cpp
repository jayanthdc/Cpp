/**
 * @section License
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017, Jayanth Chidanand
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "CSong.h"
#include<iomanip>
#include<limits>

/*************************************************************************************************
 * Function      : CSong()
 * Description : Default Constructor
 * @param      : none
 * @return      : none
 *************************************************************************************************/
CSong::CSong()
{
	// TODO Auto-generated constructor stub
}
/*************************************************************************************************
 * Function      : CSong(const string &songtitle, const string &singer)
 * Description : Parameterized Constructor
 * @param      : const string &songtitle  ( Title of the Song )
 * @param      : const string &singer  ( Name of the Singer )
 * @return      : none
 *************************************************************************************************/
CSong::CSong(const string &songtitle, const string &singer)
{
	this->m_title =  songtitle;
	this->m_singer = singer;
}

/*************************************************************************************************
 * Function      : ~CSong()
 * Description : Destructor
 * @param      : none
 * @return      : none
 *************************************************************************************************/
CSong::~CSong()
{

}

/*************************************************************************************************
 * Function      : getTitle() const
 * Description : Function to get the title of the song
 * @param      : none
 * @return      : string (Title of the song )
 *************************************************************************************************/
string CSong::getTitle() const
{
	return this->m_title;
}

/*************************************************************************************************
 * Function      : getSinger()
 * Description : Function to get the singer of the song
 * @param      : none
 * @return      : string (Singer of the song )
 *************************************************************************************************/
string CSong::getSinger()
{
	return this->m_singer ;
}

/*************************************************************************************************
 * Function      : operator <(const CSong &song)
 * Description : Overloading operator < for comparison
 * @param      : CSong
 * @return      : bool ( True (lhs < rhs) else false )
 *************************************************************************************************/
bool CSong::operator <(const CSong &song)
{
	if(this->m_title < song.m_title)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*************************************************************************************************
 * Function      : operator ==(const CSong &song)
 * Description : Overloading operator ==  for comparison
 * @param      : CSong
 * @return      : bool ( True (lhs == rhs) else false )
 *************************************************************************************************/
bool CSong::operator ==(const CSong &song)
{
	if( this->m_title ==song.m_title &&  this->m_singer ==song.m_singer )
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*************************************************************************************************
 * Function      : operator << (ostream &out , const CSong Song)
 * Description : Friend function to overload the << operator to print the CSong
 * @param      : ostream &out ,
 * @param      : const CSong Song
 * @return      : ostream& ( reference to the ostream object )
 *************************************************************************************************/
ostream&  operator << (ostream &out , const CSong Song)
{
	out<<Song.m_title<<" :: "<<Song.m_singer;

	return out;
}
/************************************************************************************************/
