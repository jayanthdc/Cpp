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

//============================================================================
// Name        : BinaryPalindrome.cpp
// Author      : Jayanth
// Copyright   : Your copyright notice
// Description : Program to find the list of binarypalindromes between two ranges[ a,b]
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include "BinaryPalindrome.h"
using namespace std;

/************************************************************************************
 *Function     : main
 *Description: This function invokes all other sub functions to drive the functionality
 *@param	   : none
 *@returnType: int ( success : 0)
 *
 ************************************************************************************/


int main(void)
{
    unsigned int num1=0,num2=0;
    unsigned int count = 0;
    string sin, s1, s2;
    stringstream ss;
    unsigned int shiftval = 0;
    time_t start, end;

    // Input parsing logic
    size_t pos;
    cout <<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout << "Please enter the Lower and Upper range in the format Number1,Number2. Ex: 5,17"<< endl;
    cout << "No negative numbers and (Number1 <= Number2)" <<endl;
    cout << "A comma should be provided after the first input. Else it provides error output" <<endl;
    cout << "WRONG / INVALID ANSWERS --> if input violates above restrictions" << endl;
    cout <<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;

    std::cin >> sin;
    pos = sin.find(",");
    s1 = sin.substr(0, pos);
    s2 = sin.substr(pos+1);

    stringstream(s1) >> num1;
    stringstream(s2) >> num2;

    if ( num1 > num2 )
        cout << "Invalid Input" << endl;

    else
    {
		time(&start);

		for ( unsigned int  num = num1; num<= num2 ; num++)
		{
			unsigned int result = 0;
			unsigned int tempnum = 0;
			unsigned int temprev = 0;

			// Step1: Reverse the entire 32 bit number

#ifdef EIGHT_BIT

			unsigned int mask = 0xFF;
			tempnum = 0;

			tempnum = num >> 24;		//octet3
			result  = eightbit_revtable[tempnum];

			tempnum = (num >> 16) & mask; //octet2
			result  = (eightbit_revtable[tempnum] << 8) | result;

			tempnum = (num >> 8) & mask; //octet1
			result  = (eightbit_revtable[tempnum] << 16) | result;

			tempnum = num  & mask; //octet0
			result  = (eightbit_revtable[tempnum] << 24) | result;

		#else
			unsigned int mask = 0xF;
			tempnum = 0;

			tempnum = num >> 28;
			result  = fourbit_revtable[tempnum];		//quad7

			tempnum = (num >> 24) & mask;
			result  = (fourbit_revtable[tempnum] << 4) | result;  //quad6

			tempnum = (num >> 20) & mask;
			result  = (fourbit_revtable[tempnum] << 8) | result;  //quad5

			tempnum = (num >> 16) & mask;
			result  = (fourbit_revtable[tempnum] << 12) | result; //quad4

			tempnum = (num >> 12) & mask;
			result  = (fourbit_revtable[tempnum] << 16) | result;//quad3

			tempnum = (num >> 8) & mask;
			result  = (fourbit_revtable[tempnum] << 20) | result; //quad2

			tempnum = (num >> 4) & mask;
			result  = (fourbit_revtable[tempnum] << 24) | result; //quad1

			tempnum = num & mask;
			result  = (fourbit_revtable[tempnum] << 28) | result; //quad0
		#endif
			// section ends

			// Step2: Find first set bit position from LSB
			temprev = result & ~(result - 1);

			// Step3: Flush zeroes in LSB for latter comparison
			switch(temprev)
			{
			case 0b00000000000000000000000000000001: shiftval = 0;break;
			case 0b00000000000000000000000000000010: shiftval = 1;break;
			case 0b00000000000000000000000000000100: shiftval = 2;break;
			case 0b00000000000000000000000000001000: shiftval = 3;break;
			case 0b00000000000000000000000000010000: shiftval = 4;break;
			case 0b00000000000000000000000000100000: shiftval = 5;break;
			case 0b00000000000000000000000001000000: shiftval = 6;break;
			case 0b00000000000000000000000010000000: shiftval = 7;break;
			case 0b00000000000000000000000100000000: shiftval = 8;break;
			case 0b00000000000000000000001000000000: shiftval = 9;break;
			case 0b00000000000000000000010000000000: shiftval = 10;break;
			case 0b00000000000000000000100000000000: shiftval = 11;break;
			case 0b00000000000000000001000000000000: shiftval = 12;break;
			case 0b00000000000000000010000000000000: shiftval = 13;break;
			case 0b00000000000000000100000000000000: shiftval = 14;break;
			case 0b00000000000000001000000000000000: shiftval = 15;break;
			case 0b00000000000000010000000000000000: shiftval = 16;break;
			case 0b00000000000000100000000000000000: shiftval = 17;break;
			case 0b00000000000001000000000000000000: shiftval = 18;break;
			case 0b00000000000010000000000000000000: shiftval = 19;break;
			case 0b00000000000100000000000000000000: shiftval = 20;break;
			case 0b00000000001000000000000000000000: shiftval = 21;break;
			case 0b00000000010000000000000000000000: shiftval = 22;break;
			case 0b00000000100000000000000000000000: shiftval = 23;break;
			case 0b00000001000000000000000000000000: shiftval = 24;break;
			case 0b00000010000000000000000000000000: shiftval = 25;break;
			case 0b00000100000000000000000000000000: shiftval = 26;break;
			case 0b00001000000000000000000000000000: shiftval = 27;break;
			case 0b00010000000000000000000000000000: shiftval = 28;break;
			case 0b00100000000000000000000000000000: shiftval = 29;break;
			case 0b01000000000000000000000000000000: shiftval = 30;break;
			case 0b10000000000000000000000000000000: shiftval = 31;break;
			}

			result = result >> shiftval;

			// Step4: Compare reverse number after alignment with original
			count += (result == num)? 1:0;
		}

		time(&end);

		double time_taken = double(end - start);
		cout << "Total Number of Palindromes in given range : "<<"[ "<<num1<<" ,"<<num2<<" ] : "<<count <<endl;
		cout << "Execution Time : " << time_taken << " seconds"<<endl;
    }

    return 0;
}
