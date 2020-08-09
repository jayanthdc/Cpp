/*
 * CJsonScanner.cpp
 *
 *  Created on: 10.12.2015
 *      Author: mnl
 */

#include <string>
#include "CJsonScanner.h"
#include "CJsonInvalidCharacterException.h"
using namespace std;

namespace APT {

CJsonScanner::CJsonScanner(std::istream& input) : jsonFlexLexer(&input) {
	token = 0;
}

CJsonScanner::~CJsonScanner() {
	if (token != 0) {
		delete token;
	}
}

CJsonToken* CJsonScanner::nextToken() {
	if (token != 0) {
		delete token;
		token = 0;
	}
	int scanResult = yylex();
	if (scanResult == -1) {
		string illegalChar(YYText( )) ;
		//const char*mych =illegalChar(YYText());
		const char* ch =  YYText();
		// To do : yytext to be examined:;


		/* Changes made*/
		CJsonInvalidCharacterException my_JsonInvalidChacter;
		my_JsonInvalidChacter.setInvalidToken(ch);
		my_JsonInvalidChacter.setLineNumber(scannedLine());
		throw  my_JsonInvalidChacter;
		/*Till here :dc*/

		// Found illegal character, currently ignored.
	}
	return token;
}

int CJsonScanner::scannedLine() {
	return yylineno;
}

} /* namespace APT */

int yyFlexLexer::yywrap() {
	return 1;
}

