/*
Author: Kaan Adalýlar (kaanadalilar-28384)
Last Modified: 13.01.2022
*/

#ifndef _THREEDSHAPES_H
#define _THREEDSHAPES_H
#include "Shape.h"
using namespace std;

class ThreeDShape: public shape{ //father of the box class & inherits the shape class
public:
	virtual float perimeter(); //perimeter of a 3D shape is 0 => returns the perimeter as 0  
};

class box: public ThreeDShape{ //inherits the ThreeDShape class
public:
	//Constructor of the box class & takes four parameters (width, length, height, name)
	box(float width, float length, float height, string name);
	virtual float volume(); //retuns the volume
	virtual float area(); //returns the area 
private:
	float width, length, height; //private member variables
};
#endif