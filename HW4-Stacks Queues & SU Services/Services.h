/*
Last Modified: 28.11.2021
Author: Kaan Adalilar - (kaanadalilar/28384)
*/
#ifndef _SERVICES_H
#define _SERVICES_H
#include <iostream>
#include <string>
using namespace std;

/*** *** LINKED LIST OF LINKED LISTS *** ***/

struct commandNode{
	string myCommand;
	commandNode * next;

	commandNode(){}

	commandNode (string & newCom, commandNode * link){
		myCommand = newCom;
		next = link;
	}
};

struct functionNode{
	string myFunction;
	functionNode * next;
	commandNode * funcCommand;

	functionNode (){}

	functionNode (string & newFunc, functionNode * link, commandNode * comLink){
		myFunction = newFunc;
		next = link;
		funcCommand = comLink;
	}
};

class linkedlist {
	private:
		functionNode * funcHead;
	public:
		 linkedlist(); //constructor
		 ~linkedlist(); //destructor
		 commandNode * getCommHead(string) const; //returns the head of the commands list with the given function name
		 void addFuncToEnd(string); //adds a function to the end of the linked list of functions
		 void addCommandToEnd(string,string); //adds a command to the end of the linked list of commands pointed by the corresponding function
		 void printServices() const; //prints the functions and their commands in the form of;
		 bool isFuncExist(string) const; //checks whether the given function name exists in the function list
};

#endif