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

/*********************************************************************************************
 * Filename      : MyPizza.cpp
 * Author        : Jayanth Dodderi Chidanand
 * Date          : 29/7/2020
 *
 *********************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Pizza.h"
using namespace std;


//Function Prototype
int CalculateIndividualSlice_Calories(vector<string> &userElements, int toppingCount,int index );

/************************************************************************************
 *Function   : main
 *Description: This function invokes all other sub functions to drive the functionality
 *@param	 : none
 *@returnType: int ( success : 0)
 *
 ************************************************************************************/
int main()
{
	
	string userinput = "2 1 Pepperoni 2 Pineapple,Ham";//Hard coded user input for testing
	vector<string> userelements;
	unsigned int totalpizzacombination = 0;
	int sliceitr = 1;
	int numberofslice = 0;
	int toppingsindex = 0;
	unsigned int totalcalories = 0;
	unsigned int retval = 0;


	//To be uncommented if user input need to be accepted at runtime
	//cout << "Enter your desired pizza combination"<<endl;
	//getline(cin, userinput);

	//Spliting UserInput on spaces and storing individual elements in a vector
	istringstream inputstream(userinput);
	for(std::string userinput; inputstream >> userinput; )
	{
		userelements.push_back(userinput);
	}

	// Deriving the total pizza combinations from the Userinput
	totalpizzacombination = stoi(userelements.at(0));

	while( totalpizzacombination != 0 )
	{
		numberofslice = stoi(userelements.at(sliceitr));
		toppingsindex = sliceitr+1;
		retval = CalculateIndividualSlice_Calories(userelements,numberofslice,toppingsindex);
		totalcalories += retval;
		totalpizzacombination -= 1;
		sliceitr = sliceitr + 2; //Incrementing the position by 2 to reach to next slice of pizza
	}

	cout << "\nThe total calorie intake is: "<<totalcalories<<" calories"<<endl;
	return 0;
}

/************************************************************************************
 *Function   : CalculateIndividualSlice_Calories
 *Description: This function Calculates the Calories added from Individual Slices of Pizza
 *@param	 : vector<string> &SortedUserInput (Reference Variable)
 *@param	 : int ( numberofslice - Count of individual Slices)
 *@param	 : int ( toppingindex - Position of the Toppings )
 *@returnType: int ( Total Calorie Count of Individual Pizza  )
 *
 ************************************************************************************/
int  CalculateIndividualSlice_Calories(vector<string> &sorteduserinput, int numberofslice,int toppingindex  )
{

	int slicecaloriecount=0;
	vector<string> slicetoppings;
	string token;

	string buffer = sorteduserinput.at(toppingindex);
	istringstream stream(buffer);

	//Parse the user inputs and store slice toppings
	while(std::getline(stream, token, ','))
	{
		slicetoppings.push_back(token);
	}

	//Looping the toppings to calculate the overall calories
	for (int toppingsitr=0; toppingsitr< numberofslice ; toppingsitr++)
	{
		slicecaloriecount += pizzaToppingsMap.at( slicetoppings.at(toppingsitr));
	}

	//Calculating total calories of individual pizza.
	slicecaloriecount=(slicecaloriecount+PIZZA_SLICE_CALORIE)*(numberofslice);

	return slicecaloriecount;

}
