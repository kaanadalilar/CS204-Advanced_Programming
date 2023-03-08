/*
Last Modified: 28.11.2021
Author: Kaan Adalilar - (kaanadalilar/28384)
*/
#include "Services.h"
using namespace std;

/*** *** LINKED LIST OF LINKED LISTS *** ***/

linkedlist::linkedlist(){ //constructor
	funcHead = NULL;
}

linkedlist::~linkedlist(){ //destructor
	functionNode * ptr = funcHead;
    while (ptr != NULL){
		if(ptr == funcHead){
			commandNode * comPtr = ptr->funcCommand;
			while(comPtr != NULL){ //delete each node in the commands list
				commandNode * temp = comPtr->next;
				delete comPtr;
				comPtr = temp;
			}
			funcHead = funcHead->next;
		}
		else{
			functionNode * traceHead = funcHead;
			while(traceHead->next != ptr){
				traceHead = traceHead->next;
			}
			commandNode * comPtr = ptr->funcCommand;
			while(comPtr != NULL){ //delete each node in the commands list
				commandNode * tmp = comPtr->next;
				delete comPtr;
				comPtr = tmp;
			}
			traceHead->next = ptr->next;
		}
		ptr = ptr->next;
	}
	delete ptr;
}

//this function adds a function to the end of the linked list of functions
void linkedlist::addFuncToEnd(string funcName){
	functionNode * headPtr = funcHead;
	functionNode * funcPtr = new functionNode(funcName,NULL,NULL);
    if(funcHead == NULL){ //if the list is empty, new node including the function name will be the head of the list
		funcHead = funcPtr;	
	}
	else{ //if the list is not empty, new node including the function name will be come after the last node of the list
		while(headPtr->next != NULL){ 
			headPtr = headPtr->next; 
		}
		headPtr->next = funcPtr; 
	}
}

//this function adds a command to the end of the linked list of commands pointed by the corresponding function
void linkedlist::addCommandToEnd(string funcName, string comName){
	functionNode * funcPtr = funcHead;
	while(funcPtr != NULL){
		if(funcPtr->myFunction == funcName){ //find the function to add a command
			commandNode * comHead = funcPtr->funcCommand; //head of the commands linked list
			commandNode * comPtr = comHead;
			if(funcPtr->funcCommand == NULL){
				funcPtr->funcCommand = new commandNode(comName, NULL);
			}
			else{
				while(comPtr->next != NULL){
					comPtr = comPtr->next;
				}
				commandNode * newCom = new commandNode(comName,NULL);
				comPtr->next = newCom;
			}
		}
		funcPtr = funcPtr->next;
	}
}

//this function prints the functions and their commands in the form of;
//function_1: print stack, define x, define y, print stack, call function_2, print stack, define z, print stack, call function_3, print stack, define c, define b, print stack.
void linkedlist::printServices() const{
	functionNode * printLine = funcHead;
	while(printLine != NULL){
		cout << printLine->myFunction << ": "; //prints the function name with ":" (e.g. "function_1:")
		commandNode * comsHead = printLine->funcCommand;
		while(comsHead != NULL){
			cout << comsHead->myCommand; //prints the commands of that function respectively
			comsHead = comsHead->next;
			if(comsHead != NULL){
				cout << ", "; //prints "," between two commands
			}
			else{
				cout << ".";
			}
		}
		cout << endl;
		printLine = printLine->next;
	}
}

//this function checks whether the given function name exists in the function list 
//if exists returns true, otherwise returns false
bool linkedlist::isFuncExist(string anyFunc) const{
	bool itExists = false;
	functionNode * func = funcHead;
	while(func != NULL){
		if(func->myFunction == anyFunc){ //it exists
			itExists = true;
		}
		func = func->next;
	}
	return itExists;
}

//this function returns the head of the commands list with the given function name
commandNode * linkedlist::getCommHead(string funcName) const{
	functionNode * funcPtr = funcHead;
	while(funcPtr != NULL){
		if(funcPtr->myFunction == funcName){
			commandNode * comHead = funcPtr->funcCommand;
			return comHead;
		}
		funcPtr = funcPtr->next;
	}
}