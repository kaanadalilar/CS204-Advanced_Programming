/*
Author: Kaan Adalýlar (kaanadalilar-28384)
Last Modified: 13.01.2022
*/

#include "ThreeDSHapes.h"
using namespace std;

float ThreeDShape::perimeter(){ //perimeter of a 3D shape is 0 => returns the perimeter as 0
	return 0;
}

//Constructor of the box class & takes four parameters (width, length, height, name)
box::box(float width, float length, float height, string name)
	: width(width), length(length), height(height){
		myName = name;
}

float box::volume(){
	return width * length * height; //volume formula of a box = width * length * height
}

float box::area(){
	return 2*(width*length+width*height+length*height); //area formula of a box = 2*(width*length+width*height+length*height) 
}