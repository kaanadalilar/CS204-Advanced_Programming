/*
Last Modified: 28.11.2021
Author: Kaan Adalilar - (kaanadalilar/28384)
*/
#include "Processing.h"
using namespace std;

/*** *** INSTRUCTORS'QUEUE *** ***/
//constructor and the functions enqueue, dequeue & isEmpty are borrowed from the lecture materials of CS204 (from week 5) and updated

InstructorQueue::InstructorQueue(int size){ //creates an empty queue with given number of elements (size)
	queueArray = new instructorInfo[size]; //dynamically allocates an array size of (size) 
	queueSize = size;
	front = -1;
	rear = -1;
	numItems = 0;
}

InstructorQueue::~InstructorQueue(){ //destructor
	delete [] queueArray; //deletes the dynamically allocated queueArray
	queueSize = 0;
	front = -1; //sets front again as -1
	rear = -1; //sets rear again as -1
	numItems = 0; //sets numItems again as 0
}

void InstructorQueue::enqueue(instructorInfo enqueueInst){ //inserts the instructor data at the rear of the queue
	rear = (rear + 1) % queueSize; //Calculate the new rear position circularly.
	queueArray[rear] = enqueueInst;	//Insert new item.
	numItems++; //Update item count.
}

void InstructorQueue::dequeue(instructorInfo & dequeueInst){ //removes the instructor data at the front of the queue, and copies it into dequeueInst
	front = (front + 1) % queueSize; //Move front.
	dequeueInst = queueArray[front]; //Retrieve the front item.
	numItems--; //Update item count.
}

bool InstructorQueue::isEmpty() const{ //returns true if the queue is empty, and false otherwise
	if (numItems > 0){
		return false;
	}
	else{
		return true;
	}
}

/*** *** STUDENTS'QUEUE *** ***/
//constructor and the functions enqueue, dequeue & isEmpty are borrowed from the lecture materials of CS204 (from week 5) and updated

StudentQueue::StudentQueue(){ //creates an empty queue
	front = NULL;
	rear = NULL;
}

StudentQueue::~StudentQueue(){ //destructor //deletes all the studentInfo nodes that are dynamically allocated
	studentInfo * ptr = front;
    while (ptr != NULL){
		studentInfo * temp = ptr->next;
		delete ptr;
		ptr = temp;
	}
}

void StudentQueue::enqueue(studentInfo enqueueStu){ //inserts the student data at the rear of the queue      
	if (isEmpty()){ //if the queue is empty
		front = new studentInfo(enqueueStu); //make it the first element
		rear = front;
	}
	else{ //if the queue is not empty
		rear->next = new studentInfo(enqueueStu); //add it after rear
		rear = rear->next;
	} 
}

void StudentQueue::dequeue(studentInfo & dequeueStu){ //removes the student data at the front of the queue, and copies it into dequeueStu
	studentInfo * temp;
	dequeueStu.studentName = front->studentName;
	dequeueStu.studentID = front->studentID;
	dequeueStu.wantedFunction = front->wantedFunction;
	temp = front;
	front = front->next;
	delete temp;      
}

bool StudentQueue::isEmpty() const{ //returns true if the queue is empty, and false otherwise
	if (front == NULL){
		return true;
	}
	else{
		return false;
	}
}

/*** *** COMMON SHARED STACK *** ***/
//constructor and the functions push, pop & isEmpty are borrowed from the lecture materials of CS204 (from week 5) and updated

CommonStack::CommonStack(){ //constructor to generate an empty stack
	top = NULL;
}

CommonStack::~CommonStack(){ //destructor //deletes all the commonStackNode nodes that are dynamically allocated
	commonStackNode * ptr = top;
    while (ptr != NULL){
		commonStackNode * temp = top->next;
		delete ptr;
		ptr = temp;
	}
}

void CommonStack::push(string newString){ //forms a new node whose string value is "newString" and pushes the node onto the stack
	commonStackNode * newNode;

	newNode = new commonStackNode;
	newNode->functionAndCommand = newString; //functionAndCommand of the newNode will be newString

	if (isEmpty()){ //if the stack is empty
		top = newNode;
		newNode->next = NULL;
	}
	else{ //if the stack is not empty
		newNode->next = top; //add it before top
		top = newNode;
	}
}

void CommonStack::pop(string & popString){ //pops the node at the top of the stack off, and copies its string value into the "popString"
	commonStackNode * temp;

	if (isEmpty()){
		cout << "The stack is empty.\n";
	}
	else{ //pop the node at the top of the stack
		popString = top->functionAndCommand;
		temp = top->next;
		delete top;
		top = temp;
	}
}

bool CommonStack::isEmpty(void){ //returns true if the stack is empty, or false otherwise
	bool status;

	if (top == NULL){
		status = true;
	}
	else{
		status = false;
	}
	return status;
}

/*
This function displays the stack IN A REVERSE ORDER and at the end of this function, the state of the stack does not change
*/
void CommonStack::printStack(CommonStack & myStack){
	commonStackNode tempNode; //node that will be popped
	CommonStack reverseStack; //temporary stack
	if(myStack.isEmpty()){
		cout << "The stack is empty" << endl;
	}
	else{
		while(!myStack.isEmpty()){
			myStack.pop(tempNode.functionAndCommand); 
			//first form the reverse order of myStack
			reverseStack.push(tempNode.functionAndCommand); //last element of myStack will be the first element of reverseStack
		}
	}
	while(!reverseStack.isEmpty()){
		reverseStack.pop(tempNode.functionAndCommand);
		//start to pop the nodes in the reverseStack and take the popped nodes onto myStack
		//last element of reverseStack will be the first element of myStack --> so that the state of myStack will not change at the end of the function
		cout << tempNode.functionAndCommand<<endl; //display the string in the popped element 
		myStack.push(tempNode.functionAndCommand); //push it to myStack
	}
	reverseStack.~CommonStack(); //destruct the reverseStack for no memory leakage
}

/*
This function deletes the node whose string component includes the given function name
i.e. if the given function name is "function_1",
then all the nodes including a string that starts with "function_1" will be deleted from the stack
*/
void CommonStack::deleteFunction(CommonStack & myStack, string funcName){
	commonStackNode tempNode; //node that will be popped
	CommonStack reverseStack; //temporary stack which will be the reverse of myStack
	while(!myStack.isEmpty()){
		//take all the nodes in the stack (myStack) to the temporary stack (reverseStack)
		myStack.pop(tempNode.functionAndCommand);
		reverseStack.push(tempNode.functionAndCommand);
	}
	//now the stack (myStack) is empty and the temporary stack includes all the nodes in first myStack
	while(!reverseStack.isEmpty()){
		reverseStack.pop(tempNode.functionAndCommand); //start to pop the nodes in the reverseStack and take the popped nodes onto myStack (WITH A CONDITION)
		
		string funcAndCom = tempNode.functionAndCommand;
		string functionInNode;
		istringstream ss(funcAndCom);
		ss >> functionInNode;
		string nodeFunction = functionInNode.substr(0,functionInNode.length()-1); //the name of the function taking place in the popped node
		
		if(nodeFunction != funcName){ //if the function name is not the function that is wanted to be deleted
			myStack.push(tempNode.functionAndCommand); //add it back to myStack
		}
		//otherwise that function will not be added to myStack
	}
	reverseStack.~CommonStack(); //destruct the reverseStack for no memory leakage
}