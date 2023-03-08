/*
Aim of this program --> managing a bus line & stop system
Data structure --> in this program there is a singly linked list whose nodes are including the bus line names and pointers to the bus stops of that line
also there are doubly linked lists for each bus line whose nodes are keeping the name of bus stops
Last Modified: 17.11.2021
Author: Kaan Adalilar - (kaanadalilar/28384)
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream> //for ifstream & file reading
#include <sstream> //for istringstream & line reading

using namespace std;

struct busStop{
	string busStopName;
	busStop * left;
	busStop * right;
};

struct busLine{
	string busLineName; 
	busLine * next;
	busStop * busStops;
};

busLine * head = nullptr;

void processMainMenu();
void deleteAllLines();

void printMainMenu(){ //displays the menu to the user
	cout << endl;
	cout <<"I***********************************************I"<<endl
		<<"I 0 - EXIT PROGRAM I"<<endl
		<<"I 1 - PRINT LINES I"<<endl
		<<"I 2 - ADD BUS LINE I"<<endl
		<<"I 3 - ADD BUS STOP I"<<endl
		<<"I 4 - DELETE BUS LINE I"<<endl
		<<"I 5 - DELETE BUS STOP I"<<endl
		<<"I 6 - PATH FINDER I"<<endl
		<<"I***********************************************I"<<endl
		<<">>";
	cout << endl;
}

bool consistencyCheck(){ //checks whether the linked lists are consistent or not
	busLine * currBL = head; //a global variable
	while (currBL){
		busStop * currBS = currBL->busStops;
		while (currBS) {
			busStop * rightBS = currBS->right;
			if(rightBS && rightBS->left != currBS) {
				cout << "Inconsistency for " << currBL->busLineName << " " << currBS->busStopName << endl;
				return false;
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return true;
}

//This function displays the bus lines with their corresponding bus stop names respectively
//The form of displaying is --> "133U: Sabanci <-> Nakliyeciler <-> Viaport <-> Pendik <-> Kartal"
void printBusLines(){
	busLine * printLine = head;
	while(printLine != NULL){
		cout << printLine->busLineName << ": "; //prints the bus line name with ":" e.g. "133U:"
		busStop * stopsHead = printLine->busStops;
		while(stopsHead != NULL){
			cout << stopsHead->busStopName; //prints the bus stops of that line respectively
			stopsHead = stopsHead->right;
			if(stopsHead != NULL){
				cout << " <-> "; //prints "<->" between the bus stops
			}
		}
		cout << endl;
		printLine = printLine->next;
	}
}

//This function checks whether the given bus line name exists in the singly linked list or not
//if exists return true - if does not exist return false
bool isLineExist(string bLineName){
	bool itExists = false;
	busLine * line = head;
	while(line != NULL){
		if(line->busLineName == bLineName){
			itExists = true;
		}
		line = line->next;
	}
	return itExists;
}

//This function checks whether the given bus stop name exists in the given line
//if exists return true - if does not exist return false
bool isStopExist(string bStopLine, string bStopName){
	bool itExists = false;	
	busLine * line = head;
	while(line != NULL){
		if(line->busLineName == bStopLine){
			busStop * stopsHead = line->busStops;
			while(stopsHead != NULL){
				if(stopsHead->busStopName == bStopName){
					itExists = true;
				}
				stopsHead = stopsHead->right;
			}
		}
		line = line->next;
	}
	return itExists;
}

//This function adds a new bus line to the singly linked list with the given line name and forms a bus stops doubly linked list with the given bus stop names
void addBusLine(){
	string addLine;
	cout << "Enter the name of the new bus line (0 for exit to main menu)" << endl;
	cin >> addLine;
	bool isFinish = false; //as the function proceeds, it can be updated as true and if it is updated as true, function stops to proceed
	bool canDisplay = true; //if this boolean variable remains true than user will receive outputs
	if(addLine == "0"){
		return; //exit to main menu
	}
	else{
		while(isFinish == false){ //if isFinish becomes true during the iteration, then the addBusLine function will finish
			while(isLineExist(addLine) == true && isFinish == false){
				cout << "Bus line already exists: enter a new one (0 for exit)" << endl;
				cin>>addLine;
				if(addLine == "0"){
					isFinish = true; 
					return; //exit to main menu directly
				}
			}
			string addStop;
			cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
			cin >> addStop;
			if(addStop == "0"){
				cout << "You are not allowed to add an empty bus line" << endl;
				canDisplay = false; //information of the bus line cannot be displayed since it is empty
				isFinish = true;
			}
			else{
				busLine * temp = new busLine;
				if(head == NULL){ //if the list is empty, temp will be the head of the bus lines
					temp->busLineName = addLine;
					temp->next = NULL;
					temp->busStops = NULL;
					
					head = temp;
					head->next = NULL;
				}
				else{
					temp->busLineName = addLine;
					temp->next = head; //since the new head will be temp, temp has to point the old head
					temp->busStops = NULL;
					head = temp;
				}
				busStop *stHead = NULL;
				busStop *stTail = NULL;
				while(addStop != "0"){
					if(isStopExist(addLine, addStop) == true){
						cout << "Bus stop already exists in the line" << endl;
						cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
						cin>>addStop;
						if(addStop == "0"){
							isFinish = true;
						}
					}
					else{
						if(stHead== NULL || stTail == NULL){ //bus stops doubly linked list is empty
							busStop *temp = new busStop;
							temp->busStopName = addStop;
							temp->right = NULL;
							temp->left = NULL;
				
							stTail = temp;
							stHead = stTail;
						}	
						else{
							busStop *temp = new busStop;
							temp->busStopName = addStop;
							temp->right = NULL;
							temp->left = stTail;
							stTail->right = temp;
							stTail = temp;
						}
						temp->busStops = stHead; //the newly added busLine will point the busStops of that line 
						cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
						cin>>addStop;
						if(addStop == "0"){
							isFinish = true;
						}
					}
				}
			}
			//below; newly formed bus line will be displayed with its' bus stops
			if(canDisplay == true && addStop == "0"){
				cout << "The bus line information is shown below" << endl;
				busLine * ptrr = head;
				while(ptrr != NULL){
					if(ptrr->busLineName == addLine){
						cout << ptrr->busLineName << ": ";
						busStop * stopPtr = ptrr->busStops;
						while(stopPtr != NULL){
							cout << stopPtr->busStopName;
							stopPtr = stopPtr->right;
							if(stopPtr != NULL){
								cout << " <-> ";
							}
						}
					}
					ptrr = ptrr->next;
				}
			isFinish = true;
			}
		}
		if(canDisplay == true){
			string choose;
			cout << "\n";
			cout << "Are you sure? Enter (y/Y) for yes (n/N) for no?" << endl;
			cin >> choose;
			if(choose == "y" || choose == "Y"){
				printBusLines();
				return;
			}
			else{ //if the user chooses "n" or "N", it means that user does not want to add the bus line to the main list
				//however in the upper side of the program, that line was added
				//thus, with the code below, that line and its' stops will be deleted
				
				busLine * ptr = head;
				while(ptr != NULL){
					if(ptr->busLineName == addLine){
						if(ptr == head){
							busStop * stopPtr = ptr->busStops;
							while(stopPtr != NULL){
								busStop * tmp = stopPtr;
								if(tmp->right != NULL){
									stopPtr->right->left = NULL;
									stopPtr = stopPtr->right;
								}
								else{
									stopPtr = NULL;
								}
								delete tmp;
							}
							head = head->next;
						}
					}
					ptr = ptr->next;
				}
				delete ptr; 
				return;
			}
		}
	}
}

//This function adds a bus stop to the existing doubly linked list of the given bus line
void addBusStop(){
	string lineOfStop;
	cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)" << endl;
	cin >> lineOfStop;
	if(isLineExist(lineOfStop) == false){ //if line does not exist, nothing can be done
		cout << "Bus line cannot be found. Going back to previous menu." << endl;
		return;
	}
	else{
		cout << "The bus line information is shown below" << endl; //displaying initial bus line information
		busLine * ptr = head;
		while(ptr != NULL){
			if(ptr->busLineName == lineOfStop){
				cout << ptr->busLineName << ": ";
				busStop * stopPtr = ptr->busStops;
				while(stopPtr != NULL){
					cout << stopPtr->busStopName;
					stopPtr = stopPtr->right;
					if(stopPtr != NULL){
						cout << " <-> ";
					}
				}
			}
			ptr = ptr->next;
		}
		string newBusStop;
		cout << "\n";
		cout << "Enter the name of the new bus stop" << endl;
		cin >> newBusStop;
		if(isStopExist(lineOfStop,newBusStop) == true){
			cout << "Bus stop already exists. Going back to previous menu." << endl;
		}
		else{
			string prevStop;
			cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)" << endl;
			cin >> prevStop;
			if(prevStop == "0"){ //add bus stop as the first stop in the doubly linked list
				while(ptr != NULL){
					if(ptr->busLineName == lineOfStop){
						busStop * stopPtr = ptr->busStops;
						busStop *temp = new busStop;
						temp->busStopName = newBusStop;
						temp->right = stopPtr;
						temp->left = NULL;
						
						stopPtr->left = temp;
						ptr->busStops = temp;
					}
					ptr = ptr->next;
				}
				printBusLines();
			}
			else{
				bool stopIteration = false;
				while(isStopExist(lineOfStop,prevStop) == false && stopIteration == false){
					cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)" << endl;
					cin >> prevStop;
					if(prevStop == "0"){
						return;
						stopIteration = true;
					}
				}
				if(stopIteration == false){
					busLine * ptr = head;
					//add bus stop after the previous stop in the doubly linked list
					while(ptr != NULL){
						if(ptr->busLineName == lineOfStop){
							busStop * stopPtr = ptr->busStops;
							while(stopPtr != NULL){
								if(stopPtr->busStopName == prevStop){
									busStop *temp = new busStop;
									temp->busStopName = newBusStop;
									temp->right = stopPtr->right;
									temp->right->left = temp;
									temp->left = stopPtr;
									stopPtr->right = temp;
								}
								stopPtr = stopPtr->right;
							}
						}
						ptr = ptr->next;
					}
					printBusLines();
				}
			}
		}
	}
}

//This function deletes a bus line from the singly linked list of bus lines and deletes the bus stops doubly linked list pointed by that line
void deleteBusLine(){
	string deleteLine;
	cout << "Enter the name of the bus line to delete" << endl;
	cin >> deleteLine; 
	if(isLineExist(deleteLine) == false){ //if the line does not exist, it cannot be deleted
		cout << "Bus line cannot be found. Going back to previous (main) menu." << endl;
		return;
	}
	else{
		busLine * ptr = head;
		while(ptr != NULL){
			if(ptr->busLineName == deleteLine){ //find the line to be deleted
				if(ptr == head){ //if this line is the head of the lines list
					busStop * stopPtr = ptr->busStops;
					while(stopPtr != NULL){ //delete all of the stops in the busStops doubly linked list pointed by the line
						busStop * tmp = stopPtr;
						if(tmp->right != NULL){
							stopPtr->right->left = NULL;
							stopPtr = stopPtr->right;
						}
						else{
							stopPtr = NULL;
						}
						delete tmp;
					}
					head = head->next; //head is updated
				}
				else{
					busLine * traceHead = head;
					while(traceHead->next != ptr){
						traceHead = traceHead->next;
					}
					//after the while loop, traceHead is pointing the node coming before the line that will be deleted
					busStop * stopPtr = ptr->busStops;
					while(stopPtr != NULL){
						busStop * tmp = stopPtr;
						if(tmp->right != NULL){
							stopPtr->right->left = NULL;
							stopPtr = stopPtr->right;
						}
						else{
							stopPtr = NULL;
						}
						delete tmp;
					}
					traceHead->next = ptr->next;
					//the node coming before the deleted node has to point the node after the deleted node;
					//i.e. ( traceHead->next = ptr->next ) means that previousNode->next = deletedNode->next
					//e.g. if the list is 133U-132B-15K and 132B will be deleted, then 133U has to point 15K - otherwise connection crashes
				}
			}
			ptr = ptr->next;
		}
		delete ptr;
	}
	printBusLines();
}

//This function deletes a bus stop from the existing doubly linked list pointed by the given bus line
void deleteBusStop(){
	string lineOfDeleteStop;
	cout << "Enter the name of the bus line to delete" << endl;
	cin >> lineOfDeleteStop; 
	if(isLineExist(lineOfDeleteStop) == false){ //if the line does not exist, there is no pointed bus stops doubly linked list --> nothing to do
		cout << "Bus line cannot be found. Going back to previous (main) menu." << endl;
		return;
	}
	else{
		cout << "The bus line information is shown below" << endl; //displaying the initial bus line information
		busLine * ptrr = head;
		while(ptrr != NULL){
			if(ptrr->busLineName == lineOfDeleteStop){					
				cout << ptrr->busLineName << ": ";						
				busStop * stopPtr = ptrr->busStops;
				while(stopPtr != NULL){
					cout << stopPtr->busStopName;
					stopPtr = stopPtr->right;
					if(stopPtr != NULL){
						cout << " <-> ";
					}
				}
			}
			ptrr = ptrr->next;
		}
		cout << "\n";

		bool stopFounded = false;
		string deleteStop;
		cout << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
		cin >> deleteStop;
		while(stopFounded == false){
			if(isStopExist(lineOfDeleteStop, deleteStop) == true){
				stopFounded = true;
			}
			else if(isStopExist(lineOfDeleteStop, deleteStop) == false && deleteStop != "0"){
				stopFounded = false;
				cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)" << endl;
				cin >> deleteStop;
			}
			else if(deleteStop == "0"){
				stopFounded = true; //to stop iteration
				return;
			}
		}
		busLine * lineIncludesStop = head; //this pointer is used for finding the line that includes the stop
		busStop * traceStopHead; //this pointer will initially point the head of the busStops doubly linked list but then used for iterating the list
		busStop * delStopHead; //this pointer will be equal to traceStopHead firstly, and WILL NOT CHANGE during the iterations (KEEP THE HEAD SAFE)
		//delStopHead WILL NOT CHANGE while the traceStopHead CHANGES
		while(lineIncludesStop != NULL){
			if(lineIncludesStop->busLineName == lineOfDeleteStop){
				traceStopHead = lineIncludesStop->busStops; //traceStopHead will change during the iteration
				delStopHead = traceStopHead; //delStopHead is initialized and now pointing the head of the busStops
				busStop * delStop;
				while(traceStopHead != NULL){
					if(traceStopHead->busStopName == deleteStop){
						delStop = traceStopHead; /*** the node pointed by delStop will be deleted ***/
						
						if(delStop == delStopHead){ //if the node including the bus stop is the head of the doubly linked list
							busStop * tmpHead = delStopHead;
							if(tmpHead->right != NULL){
								tmpHead->right->left = NULL;
								//c
								lineIncludesStop->busStops = tmpHead->right;
								break;
							}
							else{
								delStopHead = NULL;
							}
							delete tmpHead;
						}
						
						else if(delStop->right == NULL){ //if the node of the bus stop is the last node of the doubly linked list
							busStop * tmpHead = delStop;
							busStop * prevTrace = delStopHead;
							while(prevTrace->right != tmpHead){
								prevTrace = prevTrace->right;
							}
							prevTrace->right = NULL;
							//if the list is Viaport-Pendik-Kartal and Kartal will be deleted, then Pendik->right has to point NULL
							delete tmpHead;
							break;
						}
						
						else{ //if the node of the bus stop is in the middle of the doubly linked list
							busStop * tmpHead = delStop;
							busStop * prevTrace = delStopHead;
							while(prevTrace->right != tmpHead){
								prevTrace = prevTrace->right;
							}
							prevTrace->right = tmpHead->right;
							tmpHead->right->left = tmpHead->left;
							//if the list is Viaport-Pendik-Kartal and Pendik will be deleted, then Viaport->right has to point Kartal (Pendik->right)
							//ALSO, Pendik->right->left has to be equal to Pendik->left
							delete tmpHead;
							break;
						}
					}
					traceStopHead = traceStopHead->right;
				}
			}
			lineIncludesStop = lineIncludesStop->next;
		}
	}
	printBusLines();
}

//This function calculates a path to go from a bus stop to another one
void pathfinder(){
	string currStop, aimStop; //current stop and the wanted stop 
	cout << "Where are you now?" << endl;
	cin >> currStop;
	cout << "Where do you want to go?" << endl;
	cin >> aimStop;
	
	busLine * curPtr = head;
	//below; it is being checked that whether current stop exists in ANY line
	bool isCurrStopExists = false;
	while(curPtr != NULL){
		busStop * stopPtr = curPtr->busStops;
		while(stopPtr != NULL){
			if(stopPtr->busStopName == currStop){
				isCurrStopExists = true;
				break;
			}
			stopPtr = stopPtr->right;
		}
		curPtr = curPtr->next;
	}
	//below; it is being checked that whether aim stop exists in ANY line
	bool isAimStopExists = false;
	busLine * aimPtr = head;
	while(aimPtr != NULL){
		busStop * stopPtr = aimPtr->busStops;
		while(stopPtr != NULL){
			if(stopPtr->busStopName == aimStop){
				isAimStopExists = true;
				break;
			}
			stopPtr = stopPtr->right;
		}
		aimPtr = aimPtr->next;
	}
	if((isCurrStopExists == false || isAimStopExists == false) || (currStop == aimStop)){ //if one of them (current or aim) does not exist, return to the menu
		if(isCurrStopExists == false || isAimStopExists == false){
			cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
			return;
		}
		else{
			cout << "You are already at the stop that you want to go. Going back to previous menu." << endl;
			return;
		}
	}
	else{
		//below; it is being checked that the current stop and the aim stop are on the same line
		bool onSameLine = false;
		busLine * bothPtr = head;
		string lineName;
		while(bothPtr != NULL){
			busStop * stopPtr = bothPtr->busStops;
			while(stopPtr != NULL){
				if(stopPtr->busStopName ==currStop){
					if(isStopExist(bothPtr->busLineName,aimStop) == true){
						onSameLine = true;
						lineName = bothPtr->busLineName;
					}
				}
				stopPtr = stopPtr->right;
			}
			bothPtr = bothPtr->next;
		}
		bool isPathFinderFinished = false;
		if(onSameLine == false){ //if they are not on the same line, there is no path
			cout << "Sorry no path from " << currStop << " to " << aimStop << " could be found." << endl;
			return;
		}
		else{ //if they are on the same line then the path will be displayed
			busLine * bothPtr = head;
			while(bothPtr != NULL){
				if(bothPtr->busLineName == lineName){
					busStop * stopPtr = bothPtr->busStops;
					while(stopPtr != NULL){
						if(stopPtr->busStopName == currStop){
							busStop * currsPtr = stopPtr; //this pointer is used for finding the aim stop
							busStop * printPtr = stopPtr;
							while(currsPtr->right != NULL){
								if(currsPtr->right->busStopName == aimStop){  //if aim stop is located after the current stop;
									cout << "You can go there by " << lineName << ": ";
									while(printPtr != currsPtr->right->right){ //printing will start from the current stop and continue with going RIGHT
										cout << printPtr->busStopName;
										if(printPtr->busStopName != aimStop){
											cout << " <-> ";
										}
										printPtr = printPtr->right;
									}
									isPathFinderFinished = true;
									//if aim stop is not located after the current stop but BEFORE the current stop;
									//then, it means that aim stop has to be found before,
									//so the path finder will continue with the LEFT HAND SIDE searching
									break;
								}
								currsPtr = currsPtr->right;
							}
						}
						stopPtr = stopPtr->right;
					}
				}
				bothPtr = bothPtr->next;
			}

			if(isPathFinderFinished == false){
				busLine * bothPtr = head;
				//searching the aim stop BEFORE the current stop by LEFT HAND SIDE searching
				while(bothPtr != NULL){
					if(bothPtr->busLineName == lineName){
						busStop * stopPtr = bothPtr->busStops;
						while(stopPtr != NULL){
							if(stopPtr->busStopName == currStop){
								busStop * currsPtr = stopPtr;
								busStop * printPtr = stopPtr;
								while(currsPtr->left != NULL){
									if(currsPtr->left->busStopName == aimStop){
										cout << "You can go there by " << lineName << ": ";
										while(printPtr != currsPtr->left->left){ //printing will start from the current stop and continue with going LEFT
											cout << printPtr->busStopName;
											if(printPtr->busStopName != aimStop){
												cout << " <-> ";
											}
											printPtr = printPtr->left;
										}
										break;
									}
									currsPtr = currsPtr->left;
								}
							}
							stopPtr = stopPtr->right;
						}
					}
					bothPtr = bothPtr->next;
				}
			}

		}
	}
}

void processMainMenu(){
	char input;
	do{
		if(!consistencyCheck()){
			cout << "There are inconsistencies. Exit." << endl;
			return;
		}
		printMainMenu();
		cout << "Please enter your option " << endl;
		cin >> input;
		switch (input){
		case '0':
			cout << "Thanks for using our program" << endl;
			deleteAllLines(); //deleting all the busLines with their busStops to disable memory leaks
			return;
		case '1':
			printBusLines();
			break;
		case '2':
			addBusLine();
			break;
		case '3':
			addBusStop();
			break;
		case '4':
			deleteBusLine();
			break;
		case '5':
			deleteBusStop();
			break;
		case '6':
			pathfinder();
			break;
		default:
			cout << "Invalid option: please enter again" << endl;
		}
	} while(true);
}

//This function clears all the nodes belonging to the singly linked list and the doubly linked lists
void deleteAllLines(){
	busLine * ptr = head;
	while(ptr != NULL){
		if(ptr == head){
			busStop * stopPtr = ptr->busStops;
			while(stopPtr != NULL){
				busStop * tmp = stopPtr;
				if(tmp->right != NULL){
					stopPtr->right->left = NULL;
					stopPtr = stopPtr->right;
				}
				else{
					stopPtr = NULL;
				}
				delete tmp;
			}
			head = head->next;
		}
		else{
			busLine * traceHead = head;
			while(traceHead->next != ptr){
				traceHead = traceHead->next;
			}
			busStop * stopPtr = ptr->busStops;
			while(stopPtr != NULL){
				busStop * tmp = stopPtr;
				if(tmp->right != NULL){
					stopPtr->right->left = NULL;
					stopPtr = stopPtr->right;
				}
				else{
					stopPtr = NULL;
				}
				delete tmp;
			}
			traceHead->next = ptr->next;
		}
		ptr = ptr->next;
	}
	delete ptr;
}

int main(){
	string busLinesFile = "busLines.txt"; //name of the text file that this program will proceed
	ifstream bLFile;
	bLFile.open(busLinesFile.c_str());
	string fileLine;

	while(getline(bLFile, fileLine)){
		string busLineInput, nameOfBusStop;
		istringstream ss(fileLine);
		ss >> busLineInput; //first element of the line is the name of bus line
		string nameOfBusLine = busLineInput.substr(0, busLineInput.length()-1); //this removes ':' from the first element (e.g. "133U:" --> "133U")
		
		busLine * ptr = head;
		busLine * temp = new busLine;
		temp->busLineName = nameOfBusLine;
		temp->next = NULL;
		temp->busStops = NULL;

		if(head == NULL){ //if the list is empty
			head = temp; 
		}
		else{ //the list is not empty
			while(ptr->next != NULL){ 
				ptr = ptr->next; 
			}
			ptr->next = temp; 
		}
		
		busStop *stopHead = NULL;
		busStop *tail = NULL;
		while(ss >> nameOfBusStop){ //after first element, the remaining elements of the line are the name of bus stops
			busStop *ptr = stopHead;

			if(stopHead== NULL || tail == NULL){ //if the list is empty
				busStop *temp = new busStop;
				temp->busStopName = nameOfBusStop;
				temp->right = NULL;
				temp->left = NULL;
				
				tail = temp;
				stopHead = tail;
			}	
			else{
				busStop *temp = new busStop;
				temp->busStopName = nameOfBusStop;
				temp->right = NULL;
				temp->left = tail;
				
				tail->right = temp;
				tail = temp;
			}
			temp->busStops = stopHead; //bus line will point the busStops
		}
	}
	processMainMenu();
	return 0;
}