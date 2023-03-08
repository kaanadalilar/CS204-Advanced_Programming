/*
Flow of the program: 
--> Taking the file name that will be processed: In this program, user enters a file name firstly 
(in this file, each line includes course code, course name and the ID of student who is attending to that course, respectively)

--> Forming a linked list: Then, program forms a linked list with the given information. In this linked list, there are nodes for each course and
each node has a vector keeping the ID of students attending to that course. After forming the linked list, the vectors in each node are being sorted in
an ascending order (the smaller student ID comes before in the vector e.g. 00001 00002 00003 00004).

--> Displaying the linked list: After forming the linked list, all the information is displayed to the user with a sorted and ordered fashion

--> Displaying the menu of Add/Drop and getting input from the user: User is asked to input an integer between 1-4 to determine his/her selection

--> If user chooses option 1 --> add a student to a course (if that course exists, directly add; else, first form a such course, then add the student)
--> If user chooses option 2 --> drop a student from a course (if that course exists & the student exists in that course)
--> If user chooses option 3 --> display the current list (displaying the linked list with a sorted and ordered fashion) 
--> If user chooses option 4 --> finish add/drop and exit the program by deleting the linked list

***Other details such as the purposes of functions and loops are explained below in the program.

Purpose of the program in terms of the course curriculum of CS204: This program is mainly an exercise for implementing the linked list data structure.
Last Modified: 29.10.2021
Author: Kaan Adalilar - (kaanadalilar/28384)
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream> //for ifstream & file reading
#include <sstream> //for istringstream & line reading

using namespace std;

struct courseNode{
	string courseCode, courseName;
	vector<int> studentsAttendingIDs;
	courseNode * next;
};

//This function is borrowed from the lecture slides used in CS204 in the term Fall 2021-2022 and modified by Kaan Adalilar (me) to be used appropriately
//This function adds a new node to the linked list by protecting its required order which is the alphabetic order of the name of the course names
courseNode * AddInOrder(courseNode * head, string nameOfCourse, string codeOfCourse, int idOfStu)
// pre: list is sorted
// post: add newkey to list, keep list sorted, return head of new list
{
	courseNode * ptr = head; // loop variable
	// if new node should be first, handle this case and return 
	// in this case, we return address of new node since it is new head 
	if (head == NULL || nameOfCourse < head->courseName) 
	{ 
		courseNode * temp = new courseNode; //node to be inserted 
		temp->courseName = nameOfCourse;
		temp->courseCode = codeOfCourse;
		temp->studentsAttendingIDs.push_back(idOfStu);
		temp->next = head; //connect the rest
		return temp;
	}
	// check node one ahead so we don't pass!
	while (ptr->next != NULL && ptr->next->courseName < nameOfCourse)
	{
		ptr = ptr->next;
	} // postcondition: new node to be inserted just after the node ptr points
	//now insert new node with newkey after where ptr points to
	courseNode * temp = new courseNode; //node to be inserted 
	temp->courseName = nameOfCourse;
	temp->courseCode = codeOfCourse;
	temp->studentsAttendingIDs.push_back(idOfStu);
	temp->next = ptr->next; //connect the rest
	ptr->next = temp;
	return head;
}

//This function is borrowed from the lecture slides used in CS204 in the term Fall 2021-2022
//This function is used for deleting the linked list during the last steps of option 4 (when the program will finish) to make sure that there is no memory leak
void DeleteList(courseNode * head){		
	courseNode * temp;				
	while (head != NULL) {				
		temp = head->next;			
		delete head;
		head = temp;
	}
}

//This function is borrowed from the slides used in CS201 course in the term Spring 2020-2021
//This function is used for removing a studentID from the vector studentsAttendingIDs
//After calling this function, the sorted vector remains as a sorted vector
void remove(vector<int> & a, int pos){
// pre: a is sorted
// post: original a[pos] removed, a is still sorted
   int k, lastIndex = a.size()-1;
   for (k=pos; k < lastIndex; k++)
       a[k] = a[k+1]; 
   // shift all elements on the right of pos one cell left
   a.pop_back();  // remove the last element of the array
}

//This function is used for displaying all the information taking place in the linked list by tracing the list NODE BY NODE;
//such as COURSE_CODE - COURSE_NAME - ALL_STUDENT_NUMBERS_REGISTERED_IN_THIS_COURSE
void PrintAddDropList(courseNode* head){
	courseNode * ptr = head;
	while(ptr != NULL){
		cout << ptr->courseCode << " " << ptr->courseName << ": ";
		for(int i=0; i<ptr->studentsAttendingIDs.size(); i++){
			cout << ptr->studentsAttendingIDs[i] << " ";
		}
		cout << "\n";
		ptr = ptr->next;
	}
	cout << "\n";
}

//This function is borrowed from the slides used in CS201 course in the term Spring 2020-2021
//This function is used for sorting the vector that is taking place in the each courseNode and including the student ID's
void SelectSort(vector<int> & a){
// pre: a contains a.size() elements
// post: elements of a are sorted in non-decreasing order
    int j, k, temp, minIndex, numElts = a.size();
    for(k=0; k < numElts - 1; k++){
        minIndex = k;             // minimal element index
        for(j=k+1; j < numElts; j++)
            if (a[j] < a[minIndex])
               minIndex = j;     // new min, store index
        temp = a[k];         // swap min and k-th elements
        a[k] = a[minIndex];
        a[minIndex] = temp;
    }
}

int main(){
	string infoFile;
	cout << "Please enter file name: ";
	cin >> infoFile; //coursesAndStudents.txt
	
	ifstream iFile;
	iFile.open(infoFile.c_str());
	cout << "Successfully opened file " << infoFile << endl;

	string fLine;
	courseNode * myhead = new courseNode;
	myhead = NULL; 

	while(getline(iFile, fLine)){
		string cCode, cName;
		int stuID;
		istringstream ss(fLine);
		ss >> cCode >> cName >> stuID;
		
		courseNode * tempPtr = myhead;
		
		bool notExist = true; //determine whether the course in the line (fLine) already exists in the linked list or not
		while(tempPtr != NULL){
			if(tempPtr->courseCode != cCode){ //if the course is not in the linked list
				tempPtr = tempPtr->next;
				//notExist remains as it is (true)
			}
			else{
				bool isExist = false; //determine whether the studentID in the line (fLine) already exists in the studentsAttendingIDs vector
				for(int i=0; i<tempPtr->studentsAttendingIDs.size(); i++){
					if(tempPtr->studentsAttendingIDs[i] == stuID){ //studentID exists in the vector
						cout<<"Student with id " << stuID << " already is enrolled to " << cCode << ". No action taken." << endl;
						isExist = true; //studentID exists in the vector
					}
				}
				if(isExist == false){ //if the studentID does not exist in the vector;
					tempPtr->studentsAttendingIDs.push_back(stuID); //add the studentID
				}
				tempPtr = tempPtr->next;
				notExist = false; //in this case it is sure that the course exists
			}
		}
		if(notExist == true){ //if the course does not exist in the linked list;
			myhead=AddInOrder(myhead, cName, cCode, stuID); //a new node will be formed for that course
		}
	}
	//the following part will sort the vectors in the each courseNode of the linked list in an ascending order
	courseNode * tempPtr = myhead;
	while(tempPtr != NULL){
		SelectSort(tempPtr->studentsAttendingIDs);
		tempPtr = tempPtr->next;
	}
	//after the upper part, it is guaranteed that the linked list is created
	cout << "The linked list is created." << endl;
	cout << "The initial list is: " << endl;
	PrintAddDropList(myhead); //first display of the linked list

	//displaying the menu and take action accordingly:
	int option = 0;
	while(option != 4){
		cout << "Please select one of the choices:" << endl;
		cout << "1. Add to List" << endl;
		cout << "2. Drop from List" << endl;
		cout << "3. Display List" << endl;
		cout << "4. Finish Add/Drop and Exit" << endl;
		cin >> option;

		if(option == 1){ //add a student to a course (if that course exists, directly add; else, first form a such course, then add the student)
			string inputLine;
			cout << "\n";
			cout << "Give the student ID and the course names and course codes that he/she wants to add: ";
			cin.ignore();
			getline(cin, inputLine);
			istringstream ss(inputLine);
			string word;
			int counter = 1; //keep a counter to be able to understand the type of the input (course code OR course name OR student ID)
			//counter will be updated at the end of the while loop 
			string addCode, addName;
			int addStuID;
			while(ss>>word){ //the input is taken as a single line, NOW it will be read WORD BY WORD
				if(counter == 1){ //if the counter is 1, >>word is the first entry and this must be a course code
					addCode = word;
				}
				else if(counter == 2){ //if the counter is 2, >>word is coming after the course code AND it means that this is a course name
					addName = word;
				}
				else{ 
					//if counter is not 1 and not 2, >>word is a student number BUT this is a must ONLY IF counter = 3
					//if counter is larger than 3, >>word can be BOTH a student ID OR a course code // the following loop will check this statement
					int letterCount = 0;
					for(int i=0; i<word.length(); i++){ //this for loop checks whether >>word is a course code OR a student ID
						if(word[i] < '0' || '9'< word[i]){ //if >>word includes some characters different than 0-9
							letterCount++; //it means that >>word includes letters or chars like _
						}
					}
					if(letterCount == 0){ //if there is no letter in the >>word, then >>word is a STUDENT ID
						addStuID = stoi(word); //studentID was taken as a string, with stoi it will be a integer
						courseNode * addPtr = myhead;
						bool notExist = true; //determine whether the course that user entered already exists in the linked list or not
						while(addPtr != NULL){
							if(addPtr->courseCode != addCode){
								addPtr = addPtr->next;
							}
							else{
								bool isExist = false; //determine whether the studentID that user entered already exists in the studentsAttendingIDs vector
								for(int i=0; i<addPtr->studentsAttendingIDs.size(); i++){
									if(addPtr->studentsAttendingIDs[i] == addStuID){
										isExist = true; //studentID exists in the vector
										cout<<"Student with id " << addStuID << " already is enrolled to " << addCode << ". No action taken." << endl;
									}
								}
								if(isExist == false){
									addPtr->studentsAttendingIDs.push_back(addStuID); //add the student to the course (ENROLLED)
									cout << "Student with id " << addStuID << " is enrolled to " << addCode << "." << endl;
								}
								addPtr = addPtr->next;
								notExist = false; //in this case it is sure that the course exists
							}
						}
						if(notExist == true){ //if the course does not exist in the linked list;
							cout << addCode << " does not exist in the list of courses. It is added up." << endl;
							cout << "Student with id " << addStuID << " is enrolled to " << addCode << "." << endl;
							myhead=AddInOrder(myhead, addName, addCode, addStuID); //a new node will be added for that course
						}
					}
					else{ //if there is a letter or letters in the >>word, then >>word is a course code
						addCode = word; //>>word is a course code
						counter = 1; //this will make the counter 1 
						//so that when 1 is added to the counter program will continue with the else if(counter==2) statement since the counter will be updated in the following part
					}
				}
				counter++; //after the whole process above, counter will be equal to counter+1 
			}
			//sorting the vectors in each node is a must, because in option 1;
			//the new vectors can be formed or the existing vectors can be updated
			courseNode * sortPtr = myhead;
			while(sortPtr != NULL){
				SelectSort(sortPtr->studentsAttendingIDs);
				sortPtr = sortPtr->next;
			}
		}
		else if(option == 2){ //drop a student from a course (if that course exists & the student exists in that course)
			string inputLine;
			cout << "\n";
			cout << "Give the student ID and the course names and course codes that he/she wants to drop: ";
			cin.ignore();
			getline(cin, inputLine);
			istringstream ss(inputLine);
			string word;
			int counter = 1; //THIS COUNTER HAS THE SAME FUNCTION AS IN THE OPTION 1 (keep a counter to be able to understand the type of the input (course code OR course name OR student ID))
			string dropCoCode, dropCoName;
			int dropStuID;
			while(ss>>word){ //the input is taken as a single line, NOW it will be read WORD BY WORD
				if(counter == 1){ //if the counter is 1, >>word is the first entry and this must be a course code
					dropCoCode = word;
				}
				else if(counter == 2){ //if the counter is 2, >>word is coming after the course code AND it means that this is a course name
					dropCoName = word;
				}
				else{
					//if counter is not 1 and not 2, >>word is a student number BUT this is a must ONLY IF counter = 3
					//if counter is larger than 3, >>word can be BOTH a student ID OR a course code // the following loop will check this statement
					int letterCount = 0;
					for(int i=0; i<word.length(); i++){
						if(word[i] < '0' || '9'< word[i]){
							letterCount++;
						}
					}
					if(letterCount == 0){
						dropStuID = stoi(word);
						courseNode * dropPtr = myhead;
						bool notExist = true; //determine whether the course that user entered already exists in the linked list or not
						while(dropPtr != NULL){
							if(dropPtr->courseCode != dropCoCode){
								dropPtr = dropPtr->next;
							}
							else{
								bool isExist = false; //determine whether the studentID that user entered already exists in the studentsAttendingIDs vector
								for(int i=0; i<dropPtr->studentsAttendingIDs.size(); i++){
									if(dropPtr->studentsAttendingIDs[i] == dropStuID){
										isExist = true; //studentID exists in the vector
										remove(dropPtr->studentsAttendingIDs, i);
										cout << "Student with id " << dropStuID << " has dropped " << dropCoCode << "." << endl;
									}
								}
								if(isExist == false){
									cout<<"Student with id " << dropStuID << " is not enrolled to " << dropCoCode << ", thus he can't drop that course." << endl;
								}
								dropPtr = dropPtr->next;
								notExist = false; //in this case it is sure that the course exists
							}
						}
						if(notExist == true){ //if the course does not exist in the linked list;
							cout << "The " << dropCoCode << " course is not exist in the list, thus student with id " << dropStuID << " can't be dropped." << endl;
						}
					}
					else{
						dropCoCode = word;
						counter = 1; //this will make the counter 1 
						//so that when 1 is added to the counter program will continue with the else if(counter==2) statement since the counter will be updated in the following part
					}
				}
				counter++; //updating the counter
			}
		}
		else if(option == 3){ //display the current list (displaying the linked list with a sorted and ordered fashion) 
			cout << "The current list of course and the students attending them:"<< endl;
			PrintAddDropList(myhead); //display the current list
			cout << "\n";
		}
	}
	if(option == 4){ //finish add/drop and exit the program by deleting the linked list
		cout << "The add/drop period is finished. Printing the final list of courses and students attending them."<< endl;
		cout << "NOTE: Courses with less than 3 students will be closed this semester." << endl;
		
		courseNode * checkPtr = myhead;
		while(checkPtr != NULL){
			if(checkPtr->studentsAttendingIDs.size() < 3){ //if there are less than 3 students, course will be closed
				cout << checkPtr->courseCode << " " << checkPtr->courseName << " ";
				for(int i=0; i<checkPtr->studentsAttendingIDs.size(); i++){
					cout << checkPtr->studentsAttendingIDs[i] << " ";
				}
				cout << "-> This course will be closed" << endl;
				checkPtr = checkPtr->next;
			}
			else{
				cout << checkPtr->courseCode << " " << checkPtr->courseName << ": ";
				for(int i=0; i<checkPtr->studentsAttendingIDs.size(); i++){
					cout << checkPtr->studentsAttendingIDs[i] << " ";
				}
				cout << "\n";
				checkPtr = checkPtr->next;
			}
		}
		DeleteList(myhead); //call the function DeleteList to return all the dynamically allocated memory to the heap before the termination 
	}	
	return 0;
}