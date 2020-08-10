/*
 * Pizza.h
 *
 *  Created on: Jul 29, 2020
 *      Author: JAYANTH
 */

#ifndef PIZZA_H_
#define PIZZA_H_

#include <iostream>
#include <string>
#include <map>
using namespace std;

//Macros:
#define PIZZA_SLICE_CALORIE 	270
#define TOTAL_PIZZA_TOPPINGS	22

//Map: Containing Toopings with its calories values
const map<string,int> pizzaToppingsMap =
{
		{"Anchovies",50 },
		{"Artichoke",60 },
		{"Bacon",92 },
		{"Brocolli",24 },
		{"Cheese",80 },
		{"Chicken",30 },
		{"Feta",99 },
		{"Garlic",8 },
		{"Ham",46 },
		{"Mushrooms",11 },
		{"Pepperoni",80 },
		{"Pineapple",21 },
		{"Ricotta",108 },
		{"Tomatoes",14 },
};



#endif /* PIZZA_H_ */
