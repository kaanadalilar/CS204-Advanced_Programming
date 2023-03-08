/*
Author: Kaan Adalýlar (kaanadalilar-28384)
Last Modified: 12.01.2022
Shape Class
*/

#ifndef _SHAPE_H
#define _SHAPE_H
#include <iostream>
#include <string>
using namespace std;

class shape{ //FATHER (BASE) CLASS FOR ALL OTHER CLASSES
public:
	virtual float perimeter() = 0; //purely virtual function
	virtual float area() = 0; //purely virtual function
	virtual float volume() = 0; //purely virtual function
	string getName(){return myName;} //returns the name of the shape
protected:
	string myName; //name of the shape
};
#endif