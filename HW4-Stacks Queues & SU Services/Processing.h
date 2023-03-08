/*
Last Modified: 28.11.2021
Author: Kaan Adalilar - (kaanadalilar/28384)
*/

#ifndef _PROCESSING_H
#define _PROCESSING_H
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/*** *** INSTRUCTORS'QUEUE *** ***/

struct instructorInfo{ //data related to the instructor
	string instructorName;
	int instructorID;
	string wantedFunction; //the function requested by the instructor
	
	instructorInfo(){}
	
	instructorInfo(string name, int id, string function){
		instructorName = name;
		instructorID = id;
		wantedFunction = function;
	}
};

class InstructorQueue{ //borrowed from the lecture materials of CS204 (from week 5) and updated to be used appropriately
private:
	instructorInfo * queueArray;
	int queueSize; //capacity of the queue
	int front;
	int rear;
	int numItems; //number of elements currently in the queue
public:
	InstructorQueue(int); //constructor
	~InstructorQueue(); //destructor
  	void enqueue(instructorInfo); //adds a new instructor
  	void dequeue(instructorInfo &); //removes an instructor
  	bool isEmpty() const; //checks whether the queue is empty or not
};

/*** *** STUDENTS'QUEUE *** ***/

struct studentInfo{ //data related to the student
	string studentName;
	int studentID;
	string wantedFunction; //the function requested by the student
	studentInfo * next;
	
	studentInfo(){} 
	
	studentInfo(string name, int id, string function, studentInfo * ptr = NULL){
		studentName = name;
		studentID = id;
		wantedFunction = function;
		next = ptr;
	}
};

class StudentQueue{ //borrowed from the lecture materials of CS204 (week 5) and updated to be used appropriately
private:
	studentInfo * front;
	studentInfo * rear;
public:
	StudentQueue(); //constructor
	~StudentQueue(); //destructor
  	void enqueue(studentInfo); //adds a new student
  	void dequeue(studentInfo &); //removes a student
  	bool isEmpty() const; //checks whether the queue is empty or not
};

/*** *** COMMON SHARED STACK *** ***/

struct commonStackNode{
	string functionAndCommand; //command and the function from which the command is coming (e.g. function_1: define x)
	commonStackNode * next;

	commonStackNode(){}

	commonStackNode(string funcAndCom, commonStackNode * nodePtr = NULL){
		functionAndCommand = funcAndCom;
		next = nodePtr;
	}
};

class CommonStack{
private:
	commonStackNode * top;
public:
	CommonStack(); //constructor
	~CommonStack(); //destructor
	void push(string); //adds a new functionAndCommand
	void pop(string &); //removes a functionAndCommand
	bool isEmpty(void); //checks whether the stack is empty or not
	void printStack(CommonStack &); //displays the stack
	void deleteFunction(CommonStack &, string);  //removes all the functionAndCommand starting with a given specific function
};

#endif