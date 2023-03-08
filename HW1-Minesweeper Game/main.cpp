/*
This program is a simplified version of Minesweeper game.
Last Modified: 14.10.2021
Author: Kaan Adalilar - (kaanadalilar/28384)
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "randgen.h"

using namespace std;

int numOfBombs(int row, int col, vector<vector<char>> & minesBoard){ //this function will return the number of bombs in the neighbor cells
	int numOfBombs = 0;
	for(int j = row-1; j <= row+1; j++){
		for(int k = col-1; k<=col+1; k++){
			if ((j >= 0 && j < minesBoard.size()) && (k >= 0 && k < minesBoard[0].size())){
				if(minesBoard[j][k] == 'B'){
					numOfBombs++;
				}
			}
		}
	}
	if(minesBoard[row][col] == 'B'){
		numOfBombs--;
	}
	return numOfBombs;
}

//this function will update the displayBoard for the option 2 so that
//when user enters another input and want to see another cell, the cell that was opened in the option 2 will also be demonstrated
void updateDisplayBoard(vector<vector<char>> & minesBoard, vector<vector<char>> & displayBoard, int myRow, int myCol){
	displayBoard[myRow][myCol] = minesBoard[myRow][myCol];
}

int main(){
	int row, col;
	cout << "Give the dimensions of the matrix: ";
	cin >> row >> col;

	cout << "\n";
	
	int nrCells = (row*col); //number of cells = rows*columns

	int nrMines;
	cout << "How many bombs: ";
	cin >> nrMines;

	cout << "\n";

	while((0>=nrMines) || (nrMines>=nrCells)){ //this while loop checkes whether 0<nrMines<nrCells
		if (nrMines>=nrCells){
			cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
			cin >> nrMines;
			cout << "\n";
		}
		else if (nrMines<1){
			cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
			cin >> nrMines;
			cout << "\n";
		}
	}

	vector<vector<char>> minesBoard(row, vector<char>(col, 'X')); //this matrix will include the place of the mines and the number of mines in the neighbor cells
	vector<vector<char>> displayBoard(row, vector<char>(col, 'X')); //this matrix will be displayed to the user and will be updated by the other matrix 

	for (int j=0; j < displayBoard.size(); j++) //with this for loop user will be able to see the row*column matrix with X's
    {   
		for (int k=0; k < displayBoard[0].size(); k++)
        {   
			cout << setw(4) << displayBoard[j][k];
        }
        cout << endl;
    }	

	RandGen rand; //this part will distribute the mines randomly
	int randomRow, randomCol;
	for (int i=0; i<nrMines; i++){
		randomRow = rand.RandInt(row);
		randomCol = rand.RandInt(col);
		while (minesBoard[randomRow][randomCol] == 'B'){ //this is checking whether there is a bomb already
			randomRow = rand.RandInt(row);
			randomCol = rand.RandInt(col);
		}
		minesBoard[randomRow][randomCol] = 'B';
	}
	
	for (int j=0; j < minesBoard.size(); j++){ //this part will add the number of bombs to the corresponding coordinate in minesBoard  
		for (int k=0; k < minesBoard[0].size(); k++){   
			if(minesBoard[j][k] != 'B'){
				minesBoard[j][k] = '0'+numOfBombs(j,k,minesBoard); 
			}
        }
    }

	cout << endl;

	
	//THIS PART WILL NOT BE OPEN WHEN USER WANTS TO PLAY THE GAME
	//This part can be used for viewing the minesBoard which includes the bombs and number of bombs in the neighbor cells
	//so that the program developer can understand that the upcoming inputs and their corresponding outputs are correct
	
	for (int j=0; j < minesBoard.size(); j++){   
		for (int k=0; k < minesBoard[0].size(); k++){   
			cout << setw(4) << minesBoard[j][k];
		}
		cout << endl;
	}
	

	bool isGameOver = false;

	while(isGameOver == false){
		cout << "\n";
		cout << "\n";
		cout << "Press:" << endl;
		cout << "\n";
		cout << "1. If you want to find out the surrounding of a cell" << endl;
		cout << "\n";
		cout << "2. If you want to open the cell" << endl;
		cout << "\n";
		cout << "3. If you want to exit." << endl;
		cout << "\n";

		string choice;
		cin >> choice;
		cout << "\n";

		while(choice != "1" && choice != "2" && choice != "3"){
			cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl << endl;
			cin >> choice;
			cout << "\n";
		}
		
		if(choice == "1"){ //OPTION 1 (opening a cell that will show the number of mines in the neighbor cells)
			int rowCoor, colCoor;
			cout << "Give the coordinates: ";
			cin >> rowCoor >> colCoor;
			cout << "\n";
			
			while ((rowCoor>=row) || (colCoor>=col)){
				cout << "It is out of range. Please give a valid coordinates: ";
				cin >> rowCoor >> colCoor;
				cout << "\n";
			}
			cout << "Displaying the surrounding of (" << rowCoor << "," << colCoor << "):" << endl << endl;
			
			for (int j=0; j < displayBoard.size(); j++){   
				for (int k=0; k < displayBoard[0].size(); k++){
					if (j==rowCoor && k == colCoor){
						cout << setw(4) << numOfBombs(j,k,minesBoard);
					}
					else{
						cout << setw(4) << displayBoard[j][k];
					}
				}
				cout << "\n";
			}
			cout << "\n";		
			cout << "Around (" << rowCoor << "," << colCoor << ") you have " << numOfBombs(rowCoor,colCoor,minesBoard) << " bomb(s)" << endl;
			cout << "\n";
			isGameOver = false;
		}
		
		else if(choice == "2"){ //OPTION 2 (opening a cell that will remain open until the end of the game IF it is not a MINE)
			int rowCoor, colCoor;
			cout << "Give the coordinates: "; 
			cin >> rowCoor >> colCoor;
			cout << "\n";
			while ((rowCoor>=row) || (colCoor>=col)){
				cout << "It is out of range. Please give a valid coordinates: ";
				cin >> rowCoor >> colCoor;
				cout << "\n";
			}

			updateDisplayBoard(minesBoard, displayBoard, rowCoor, colCoor); //updating the displayBoard with the opened cell
			cout << "Opening cell (" << rowCoor << "," << colCoor << "):" << endl << endl;

			for (int j=0; j < displayBoard.size(); j++){   
				for (int k=0; k < displayBoard[0].size(); k++){
					if (j==rowCoor && k == colCoor){
						cout << setw(4) << displayBoard[j][k];
					}
					else{
						cout << setw(4) << displayBoard[j][k];
					}
				}
				cout << "\n";
			}


			if(minesBoard[rowCoor][colCoor] == 'B'){ //IF the cell includes bomb, GAME IS OVER
				cout << "\n";
				cout << "Unfortunately, you stepped on a mine" << endl << endl;
				cout << "Arrangement of mines: " << endl << endl;
				for (int j=0; j < minesBoard.size(); j++){   
					for (int k=0; k < minesBoard[0].size(); k++){   
						cout << setw(4) << minesBoard[j][k];
					}
					cout << endl;
				}
				cout << "\n";
				cout << ">>>>> Game Over! <<<<<" << endl;
				isGameOver = true;
			}
			
			int numberOfBombsInMinesBoard = 0; //by using these variables we can understand whether all the non-bombed cells are opened 
			int numberOfClosedCellsInDisplayBoard = 0;
			for(int m=0; m<displayBoard.size(); m++){
				for(int n=0; n<displayBoard[0].size(); n++){
					if(displayBoard[m][n] == 'X'){
						numberOfClosedCellsInDisplayBoard++;
					}
				}
			}
			for(int e=0; e<displayBoard.size(); e++){
				for(int f=0; f<displayBoard[0].size(); f++){
					if(minesBoard[e][f] == 'B'){
						numberOfBombsInMinesBoard++;
					}
				}
			}
			if(numberOfClosedCellsInDisplayBoard == numberOfBombsInMinesBoard){ //IF all of these non-bombed cells are opened, USER WINS
				isGameOver = true;
				cout << "\n";
				cout << "Congratulations! All the non-mined cells opened successfully" << endl << endl;
				cout << "You won!" << endl;
				cout << "\n";
				cout << ">>>>> Game Over! <<<<<" << endl;
			}
		}
		else if(choice == "3"){ //AUTOMATICALLY EXIT THE PROGRAM
			cout << "Program exiting ..." << endl;
			isGameOver = true;
		}
	}
	return 0;
}