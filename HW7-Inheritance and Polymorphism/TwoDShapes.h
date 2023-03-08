/*
Author: Kaan Adalýlar (kaanadalilar-28384)
Last Modified: 13.01.2022
*/

#ifndef _TWODSHAPES_H
#define _TWODSHAPES_H
#include "Shape.h"
using namespace std;

class TwoDShape: public shape{ //father of the rectangle class & inherits the shape class
public:
	virtual float volume(); //volume of a 2D shape is 0 => returns the volume as 0
};

class rectangle: public TwoDShape{ //inherits the TwoDShape class
public:
	//Constructor of the rectangle class & takes three parameters (width, length, name)
	rectangle(float width, float length, string name);
	virtual float perimeter(); //returns the perimeter 
	virtual float area(); //returns the area
private:
	float width, length; //private member variables
};
#endif