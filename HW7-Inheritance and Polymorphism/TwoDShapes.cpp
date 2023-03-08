/*
Author: Kaan Adalýlar (kaanadalilar-28384)
Last Modified: 13.01.2022
*/

#include "TwoDShapes.h"
using namespace std;

float TwoDShape::volume(){ //volume of a 2D shape is 0 => returns the volume as 0
	return 0;
} 

//Constructor of the rectangle class & takes three parameters (width, length, name)
rectangle::rectangle(float width, float length, string name)
	: width(width), length(length){
		myName = name;
}

float rectangle::perimeter(){
	return 2*(width + length); //perimeter formula of a rectangle = 2*(width + length)
}  

float rectangle::area(){ 
	return width * length; //area formula of a rectangle = width * length
} 