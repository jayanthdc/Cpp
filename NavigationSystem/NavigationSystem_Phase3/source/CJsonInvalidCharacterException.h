/*
 * CJsonInvalidCharacterException.h
 *
 *  Created on: Dec 31, 2018
 *      Author: JAYANTH DC
 */

#ifndef CJSONINVALIDCHARACTEREXCEPTION_H_
#define CJSONINVALIDCHARACTEREXCEPTION_H_


#include <stdexcept>			// exception header file contains runtime_error
//using namespace std;

class CJsonInvalidCharacterException: public std:: runtime_error
{
private:
	char InvalidToken;
	int Err_LineNumber;

public:
	// constructor specifies default error message
	CJsonInvalidCharacterException()
	: runtime_error( "Invalid character found ") {
		InvalidToken = 0;
		Err_LineNumber= 0;
	}

	void getInvalidToken()
	{
		std::cout<<"The character is : "<<InvalidToken;
	}
	void getLineNumber()
	{
		std::cout<<"  at the line number : "<<Err_LineNumber<<std::endl;
	}

	void setInvalidToken(const char *Token)
	{
		InvalidToken = *Token;
	}
	void setLineNumber(int LineNumber)
	{
		Err_LineNumber = LineNumber;
	}
};

#endif /* CJSONINVALIDCHARACTEREXCEPTION_H_ */
