/*
Last Modified: 11.12.2021
Author: Kaan Adalilar - (kaanadalilar/28384)
*/
#ifndef _CAR_H
#define _CAR_H
#include <iostream>
#include <string>
using namespace std;

class Car{

public:
    Car(double fuel, double insurance, double distance); //constructor
	//these functions are called by the driver class
	void updateFuel(double); //updates the fuel level of the car
	void updateInsurance(double); //updates the insurance of the car
	void updateDistance(double); //updates the distance travelled

	double getFuel(); //returns the fuel of the car
	double getInsurance(); //returns the insurance of the car
	double getDistance(); //returns the distance travelled
	double getInitialFuel(); //returns the initial value of the fuel level of the car
   
	//the function below is called by the main function
	void display(); //displays the fuel level, insurance and the total distance

private:
	double myFuel; //keeps the fuel level of the car private
	double myInsurance; //keeps the insurance of the car private
	double myDistance; //keeps the distance travelled private
	double initialFuel; //keeps the initial value of the fuel level of the car private
};

#endif