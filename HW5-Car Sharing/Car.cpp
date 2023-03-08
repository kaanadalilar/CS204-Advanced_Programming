/*
Last Modified: 11.12.2021
Author: Kaan Adalilar - (kaanadalilar/28384)
*/
#include "Car.h"
using namespace std;

Car::Car(double fuel, double insurance, double distance){ //constructs the car with the given information
	myFuel = fuel;
	myInsurance = insurance;
	myDistance = distance;
	initialFuel = fuel;
}

void Car::updateFuel(double changeFuel){ //updates the fuel level of the car
	myFuel += changeFuel; 
}

void Car::updateInsurance(double changeInsurance){ //updates the insurance of the car
	myInsurance += changeInsurance;
}

void Car::updateDistance(double changeDistance){ //updates the distance travelled
	myDistance += changeDistance;
}

double Car::getFuel(){ //returns the fuel of the car
	return myFuel;
}

double Car::getInsurance(){ //returns the insurance of the car
	return myInsurance; 
}

double Car::getDistance(){ //returns the distance travelled
	return myDistance;
}

double Car::getInitialFuel(){ //returns the initial value of the fuel level of the car
	return initialFuel;
}

void Car::display(){ //displays the fuel level, insurance and the total distance
	cout << "Fuel Level: " << myFuel << endl;
	cout << "Insurance Fee: " << myInsurance << endl;
	cout << "Total distance that the car has travelled: " << myDistance << endl << endl;
}