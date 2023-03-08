/*
Data Structures;
Linked List: in this program there is a singly linked list whose nodes are including the function names and pointers to the list of commands of that function  
& also there are simply linked lists for each function whose nodes are keeping commands of the corresponding function

Queue: there are two queues in this program; one of them keeps the instructor requests and it is a static queue
& the other one keeps the student requests and it is a dynamic queue

Stack: there is a common shared stack that keeps the commands and the function from which the command is coming 

Last Modified: 28.11.2021
Author: Kaan Adalilar - (kaanadalilar/28384)
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream> //for ifstream & file reading
#include <sstream> //for istringstream & line reading
#include "Services.h" //for services linked list of linked lists
#include "Processing.h" //for the queues and stack

using namespace std;

//This function adds an instructor request to the instructors' queue
void addInstructorRequest(const linkedlist & parameterList, InstructorQueue & parameterQueue){
	string wantedService;
	cout << "Add a service (function) that the instructor wants to use: " << endl;
	cin >> wantedService;
	if(!parameterList.isFuncExist(wantedService)){ //if the wanted service does not exist in the services, return to main menu
		cout << "The requested service (function) does not exist." << endl
			<< "GOING BACK TO MAIN MENU" << endl;
		return;
	}
	else{ //if the wanted service exists, then the instructor name and ID will be asked
		string instName;
		cout << "Give instructor's name: ";
		cin >> instName;
		int instID;
		cout << "Give instructor's ID (an int): ";
		cin >> instID;

		instructorInfo newInstructor(instName, instID, wantedService); //form an instructor struct with the given info
		parameterQueue.enqueue(newInstructor); //add the instructor to the queue

		cout << "Prof. " << instName << "'s service request of " << wantedService << endl
			<< "has been put in the instructor's queue." << endl
			<< "Waiting to be served..." << endl;
	}
}

//This function adds a student request to the students' queue
void addStudentRequest(const linkedlist & parameterList, StudentQueue & parameterQueue){
	string wantedService;
	cout << "Add a service (function) that the student wants to use: " << endl;
	cin >> wantedService;
	if(!parameterList.isFuncExist(wantedService)){ //if the wanted service does not exist in the services, return to main menu
		cout << "The requested service (function) does not exist." << endl
			<< "GOING BACK TO MAIN MENU" << endl;
		return;
	}
	else{ //if the wanted service exists, then the student name and ID will be asked
		string stuName;
		cout << "Give student's name: ";
		cin >> stuName;
		int stuID;
		cout << "Give student's ID (an int): ";
		cin >> stuID;

		studentInfo newStudent(stuName, stuID, wantedService); //form a student struct with the given info
		parameterQueue.enqueue(newStudent); //add the student to the queue

		cout << stuName << "'s service request of " << wantedService << " has been put in the student's queue." << endl
			<< "Waiting to be served..." << endl;
	}
}

//This function (service) processes a specific function (functionName)
void processARequest(string functionName, const linkedlist & parameterList, CommonStack & parameterStack){
	commandNode * temp = parameterList.getCommHead(functionName); //head of the command linked list pointed by the wanted service (function)
	
	while (temp != NULL){
		string commandInList = temp->myCommand;
		string firstCommand; //stringstream will first take into account this string
		string remainingCommands; //after first command stringstream will take this string
		string processCommand = ""; //

		string calledFunction;
		istringstream ss(commandInList);
		
		while(ss >> firstCommand){ //firstCommand can be "define" || "call" || "print"
			if(firstCommand == "define"){ //if firstCommand is "define"
				processCommand += firstCommand + " "; //make processCommand "define"
				while(ss >> remainingCommands){
					processCommand += remainingCommands + " "; //make processCommand "define variable_name" (e.g. "define x")
				}
				//to add the processCommand to the common shared stack functionName also has to be added to the processCommand
				string defineCommand = functionName + ": " + processCommand.substr(0,processCommand.length()-1);
				//defineCommand will be added to the stack as (function_1: define x)
				parameterStack.push(defineCommand);
			}
			else if (firstCommand == "call"){ //if firstCommand is "call"
				while(ss >> remainingCommands){
					calledFunction = remainingCommands; //calledFunction is "function_x" (e.g. "function_1)
				}
				cout << "Calling " << calledFunction << " from " << functionName << endl;
				processARequest(calledFunction, parameterList, parameterStack); //the recursion goes here
			}
			else{ //if firstCommand is "print"
				while(ss >> remainingCommands){
					processCommand += remainingCommands; //for make the ss empty //remainingCommands is not needed because it is already known as ("stack")
				}
				cout << "PRINTING THE STACK TRACE:" << endl;
				parameterStack.printStack(parameterStack); //displaying the stack
			}
		}
		temp = temp->next;
	}

	cout << functionName << " is finished. Clearing the stack from it's data..." << endl;
	parameterStack.deleteFunction(parameterStack, functionName); //after the function finished, it will be deleted from the common stack
	system("pause");
}

//This function decides whether an instructor request will be applied or a student request will be proceeded
void processARequest(InstructorQueue & instructorsQueue, StudentQueue & studentsQueue, const linkedlist & parameterList, CommonStack & parameterStack){
	if (!instructorsQueue.isEmpty()){ //if instructors' queue is not empty, since they have a priority over students, instructor request will be proceeded
		instructorInfo dequeueInst;
		instructorsQueue.dequeue(dequeueInst); //program will proceed with the first instructor request in the queue and remove it from the queue
		
		string requestedInstName = dequeueInst.instructorName; //name of the instructor
		int requestedInstID = dequeueInst.instructorID; //ID of the instructor
		string requestedFunc = dequeueInst.wantedFunction; //service requested by the instructor
		
		cout << "Processing instructor's queue..." << endl;
		cout << "Processing Prof. " << requestedInstName << "'s request (with ID " << requestedInstID << ") of service (function): "<< requestedFunc << endl;
		processARequest(requestedFunc, parameterList, parameterStack); //processARequest will proceed the requested service of the instructor
		parameterStack.printStack(parameterStack);
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else if (!studentsQueue.isEmpty()){ //if instructors' queue is empty and students' queue is not empty, student request will be proceeded
		studentInfo dequeueStu;
		studentsQueue.dequeue(dequeueStu); //program will proceed with the first student request in the queue and remove it from the queue
		
		string requestedStuName = dequeueStu.studentName; //name of the student
		int requestedStuID = dequeueStu.studentID; //ID of the student
		string requestedFunc = dequeueStu.wantedFunction; //service requested by the student
		
		cout << "Instructors queue is empty. Proceeding with student's queue..." << endl;
		cout << "Processing " << requestedStuName << "'s request (with ID " << requestedStuID << ") of service (function): "<< requestedFunc << endl;
		processARequest(requestedFunc, parameterList, parameterStack); //processARequest will proceed the requested service of the student
		parameterStack.printStack(parameterStack);
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else{ //if both instructors' queue and students' queue are empty, there is no request waiting to be proceeded
		cout << "Both instructor's and student's queue is empty.\nNo request is processed." <<endl
			<< "GOING BACK TO MAIN MENU" << endl;
	}
}

int main(){
	bool filesFinished = false;
	string wanted;
	cout << "If you want to open a service (function) defining file, " << endl
		<< "then press (Y/y) for 'yes', otherwise press any single key" << endl;
	cin >> wanted;
	if(wanted == "Y" || wanted == "y"){
		filesFinished = false;
	}
	else{ //in the very first step if the user does not open any service defining file, program cannot proceed
		filesFinished = true;
		cout << "You didn't open any service (function) defining file! Exiting..." << endl;
		exit(0);
	}

	linkedlist myFunctionList; //list of services with corresponding commands
	InstructorQueue myInstructorQueue(5); //instructor queue
	StudentQueue myStudentQueue; //student queue
	CommonStack commonSharedStack; //shared stack that will be used in proceeding a request

	while(filesFinished == false){
		string fileName;
		cout << "Enter the input file name: ";
		cin >> fileName;
		ifstream inputFile;
		inputFile.open(fileName.c_str());

		if(inputFile.fail()){ //if the entered file cannot be opened for any reason, program will be terminated
			cout << "Cannot open the file! PROGRAM EXITING..." << endl;
			myFunctionList.~linkedlist(); //destructing the services linked list of linked lists that has been formed so far
			exit(0);
		}
		string fileLine;
		int counter = 0;
		string nameOfFunction;
		while(getline(inputFile, fileLine)){
			if(counter == 0){ //first line of the file contains function name (e.g. "function_1")
				string functionName;
				istringstream ss(fileLine);
				ss >> functionName;
				nameOfFunction = functionName.substr(0, functionName.length()-1); //removes ':' from the function name (e.g. "function_1:" --> "function_1")
				myFunctionList.addFuncToEnd(nameOfFunction);
			}
			else{ //after the first line, remaining lines contain commands
				string commandWord;
				string nameOfCommand = "";
				string finalCommand;
				istringstream ss(fileLine);
				while(ss >> commandWord){
					nameOfCommand += commandWord + " ";
				}
				finalCommand = nameOfCommand.substr(0, nameOfCommand.length()-2); //this removes ';' from the command (e.g. "print stack;" --> "print stack")
				myFunctionList.addCommandToEnd(nameOfFunction, finalCommand);
			}
			counter++;
		}

		string option;
		cout << "Do you want to open another service defining file?" << endl
			<< "Press (Y/y) for 'yes', otherwise press anykey" << endl;
		cin >> option;
		if(option == "y" || option == "Y"){
			filesFinished = false;
		}
		else{
			filesFinished = true;
		}
	}
	//after forming the linked list structure, it will be displayed to the user
	cout << "--------------------------------------------------------------------" << endl
		<< "PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS" << endl
		<< "--------------------------------------------------------------------" << endl;
	myFunctionList.printServices();

	while(true){
		cout << endl;
		cout << "***********************************************************************" << endl
			<< "**************** 0 - EXIT PROGRAM *************************************" << endl
			<< "**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST ****************" << endl
			<< "**************** 2 - ADD A STUDENT SERVICE REQUEST ********************" << endl
			<< "**************** 3 - SERVE (PROCESS) A REQUEST ************************" << endl
			<< "***********************************************************************"<< endl;
		cout << endl;
		int option;
		cout << "Pick an option from above (int number from 0 to 3): ";
		cin >> option;
		switch (option)
		{
		case 0:
			cout << "PROGRAM EXITING ... " << endl;
			system("pause");
			//when program comes to the end, destructors of the objects are called TO DISABLE MEMORY LEAKAGE
			myFunctionList.~linkedlist(); //destructing the services linked list of linked lists
			myInstructorQueue.~InstructorQueue(); //destructing the instructors' queue
			myStudentQueue.~StudentQueue(); //destructing the students' queue
			commonSharedStack.~CommonStack(); //destructing the stack
			exit(0);
		case 1:
			addInstructorRequest(myFunctionList, myInstructorQueue);
			break;
		case 2:
			addStudentRequest(myFunctionList, myStudentQueue);
			break;
		case 3:
			processARequest(myInstructorQueue, myStudentQueue, myFunctionList, commonSharedStack);
			break;
		default:
			cout << "INVALID OPTION!!! Try again" << endl;
		} //switch
	} //while (true)
	return 0;
}