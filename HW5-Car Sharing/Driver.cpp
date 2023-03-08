/*
Last Modified: 11.12.2021
Author: Kaan Adalilar - (kaanadalilar/28384)
*/
#include "Driver.h"
using namespace std;

Driver::Driver(Car & mutualCar, double budget)
	:driverCar(mutualCar), driverBudget(budget)
{}

void Driver::drive(double myKilometres){
	driverCar.updateDistance(myKilometres); //adds myKilometres to the total distance
	double fuelConsumed = myKilometres * 0.25; //calculates the fuel consumption (0.25$ per one kilometer)
	driverCar.updateFuel(-fuelConsumed); //subtracts the consumed fuel from the current fuel level of the var
}

void Driver::repairCar(string typeOfAccident){
	if(typeOfAccident == "SMALL"){ //if the type of accident is SMALL
		driverBudget -= 50; //decrease driver budget (50$ for SMALL accidents)
		double insuranceIncrease = driverCar.getInsurance() * 0.05; //increase the insurance fee (add 5% of the current fee for SMALL accidents)
		driverCar.updateInsurance(insuranceIncrease); //update the insurance fee in the Car object
		cout << "50$ is reduced from the driver's budget because of the SMALL accident" << endl
			<< "Yearly insurance fee is increased to " << driverCar.getInsurance() << " because of the SMALL accident" << endl;
	}
	else if(typeOfAccident == "MEDIUM"){ //if the type of accident is MEDIUM
		driverBudget -= 150; //decrease driver budget (150$ for MEDIUM accidents)
		double insuranceIncrease = driverCar.getInsurance() * 0.1; //increase the insurance fee (add 10% of the current fee for MEDIUM accidents)
		driverCar.updateInsurance(insuranceIncrease); //update the insurance fee in the Car object
		cout << "150$ is reduced from the driver's budget because of the MEDIUM accident" << endl
			<< "Yearly insurance fee is increased to " << driverCar.getInsurance() << " because of the MEDIUM accident" << endl;
	}
	else{ //if the type of accident is LARGE
		driverBudget -= 300; //decrease driver budget (300$ for LARGE accidents)
		double insuranceIncrease = driverCar.getInsurance() * 0.2; //increase the insurance fee (add 20% of the current fee for LARGE accidents)
		driverCar.updateInsurance(insuranceIncrease); //update the insurance fee in the Car object
		cout << "300$ is reduced from the driver's budget because of the LARGE accident" << endl
			<< "Yearly insurance fee is increased to " << driverCar.getInsurance() << " because of the LARGE accident" << endl;
	}
}

void Driver::fullFuel(){ //makes the fuel level of the car full
	double initalFuel = driverCar.getInitialFuel();
	double firstFuelLevel = driverCar.getFuel();
	double firstBudget = driverBudget;
	double newFuel = initalFuel-firstFuelLevel;
	driverCar.updateFuel(newFuel); //after this operation fuel level of the car will be full (300$)
	
	driverBudget -= newFuel; //cost of the fuel is subtracted from the driver budget
	cout << "Fuel is full" << endl << endl;
}

void Driver::display(){
	cout << "Driver Budget: " << driverBudget << endl;
}