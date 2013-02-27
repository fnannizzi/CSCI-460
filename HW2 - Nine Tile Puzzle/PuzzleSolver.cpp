// Author: Francesca Nannizzi					
// Date: 2.19.13									
// Purpose: HW2 for CSCI 460: Nine Tile Puzzle	
// - - - - - - - - - - - - - - - - - - - - - - -	| 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Node.h"

using namespace std;

// Read the input from a file
void readFromInputFile(string f, vector<int> &iV){
	int nextInt = 0;
	ifstream file(f.c_str());
	if(file.is_open()){
		while(file >> nextInt){
			cout << "Read in " << nextInt << endl;
			iV.push_back(nextInt);
		}
		file.close();
	}
}

// Print the solution and number of moves
void printSolutionOutOfPlace(vector<int> moves, int numMoves){
	cout << "Number of Misplaced Tiles: " << endl;
	cout << "Sequence of tiles to be moved: ";
	for(int i = 0; i < moves.size(); i++){
		cout << moves[i] << " ";
	}
	cout << endl;
	cout << "Number of moves: " << numMoves << endl;
}

// Make next move based on number of tiles out of place relative to goal
void nextMove(vector<int> &moves, int &numMoves, Node &p){
	int position = p.locateEmptySpace();
	if(position < 9){
		vector<Node> nodes;
		for(int i = 0; i < p.board[position].numLinks; i++){
			Node node = p; 
			node.moveTilePosition(p.board[position].links[i], position);
			nodes.push_back(node);
			//cout << "Node " << i << endl;
			//printBoard(node);
			//cout << endl;
		}
		int indexBestChoice = 0;
		for(int i = 0; i < nodes.size(); i++){
			if(nodes[i].tilesOutOfPlaceRelativeToGoal() < 
			   nodes[indexBestChoice].tilesOutOfPlaceRelativeToGoal()){
				indexBestChoice = i;
				cout << "indexBestChoice: " << i << endl;
			}
		}
		p.moveTilePosition(p.board[position].links[indexBestChoice], position);
		moves.push_back(p.board[position].value);
		numMoves++;
	}	
}

// Main 
int main(int argc, char *argv[]){

	// Variable Declarations
	string filename = "";
	vector<int> inputValues;
	vector<int> moves;
	int numMoves = 0;

	// Handling command line arguments
	if(argc == 2){ // store filename
		filename = argv[1];
	} // end if
	else { // terminate if invalid or no filename
		cout << "ERROR: Invalid filename." << endl;
		return 0;
	} // end else

	// Initialize board
	readFromInputFile(filename, inputValues);
	Node puzzle(inputValues);
	
	
	
	
	// Find a solution with heuristic 2: 
	// number of tiles out of place relative to goal
	while(puzzle.tilesOutOfPlaceRelativeToGoal() > 0){
		nextMove(moves, numMoves, puzzle);
		cout << "Decision: " << endl;
		puzzle.printBoard();
		cout << endl;
		cout << "Number of moves: " << numMoves << endl;
		if(numMoves > 12){
			break;
		}
	}
	printSolutionOutOfPlace(moves, numMoves);
		
	return 0;
} // end main

