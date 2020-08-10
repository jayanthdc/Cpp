# Resist Pizza

# Problem Statement
The task here is to accept number of different pizza combinations and calculate the total calories eaten for that meal.
The input to be entered of the form: There are 270 calories in each pizza slice, plus additional calories for toppings as described in the table below.
* number of different pizza combinations, number ofslices of each pizza, and toppings selected for each of the slices.

A table of Pizza topping and the its calories is provided, using which the Calculation needs to be done.

|   Toppings    |   Calories  |
|  ------------:| -----------:|
|   Anchovies   |     50      |
|   Artichoke   |     60      |
|   Bacon       |     92      |
|   Brocolli    |     24      |
|   Mushrooms   |     11      |
|   Chicken     |     30      |
|   Feta        |     100     |
|   Garlic      |     8       |
|   Cheese      |     80      |
|   Pineapple   |     21      |
|   Ricotta     |     108     |
|   Pepperoni   |     80      |
|   Ham         |     46      |
|   Tomatoes    |     25      |


# Solution

* The Pizza table is stored as STL_Map as for every Key: "Toppings" a Value is associated "Calories" and also the map operations are efficient for data access.
* The user Input is stored in a string, which is further parsed to obtain the individual Pizza related details.
* A Vector of strings is used to store the individual toppings and processed in loop to calculate the calorie count for every Individual Slice of pizza.
* Finally the additional slice calories count of 270 is added to the toppings calorie count and is multiplied by the factor of number of slices of individual Pizza. 
