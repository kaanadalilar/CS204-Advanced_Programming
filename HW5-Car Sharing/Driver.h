/*
Last Modified: 11.12.2021
Author: Kaan Adalilar - (kaanadalilar/28384)
*/
#ifndef _DRIVER_H
#define _DRIVER_H
#include <iostream>
#include <string>
#include "Car.h"
using namespace std;

class Driver{

public:
    Driver(Car & mutualCar, double budget); //constructor
    void drive(double); //updates the fuel level of the car and the distance travelled by the car //by taking the distance travelled by a driver as a parameter
	void repairCar(string); //updates the insurance of the car and the budget of the driver //by taking the type of the accident as a parameter
	void fullFuel(); //makes the fuel level of the car full
	void display(); //displays the budget of the driver

private:
	Car & driverCar;     
	double driverBudget;
};



#endif