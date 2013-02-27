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
void printSolutionOutOfPlace(vector<int> moves){
	cout << "Number of Misplaced Tiles: " << endl;
	cout << "Sequence of tiles to be moved: ";
	for(int i = 0; i < moves.size(); i++){
		cout << moves[i] << " ";
	}
	cout << endl;
	cout << "Number of moves: " << moves.size() << endl;
}

// Expand a node
void expandNode(Node p, vector<Node> &successor){
	successor.clear();
	int position = p.locateEmptySpace();
	for(int i = 0; i < p.board[position].numLinks; i++){
		Node node(&p, p.board, (p.numMovesToNode + 1)); 
		node.moveTilePosition(p.board[position].links[i], position);
		successor.push_back(node);
		//cout << "Node " << i << endl;
		//printBoard(node);
		//cout << endl;
	}
}

// Make next move based on number of tiles out of place relative to goal
void nextMove(vector<int> &moves, Node &p, vector<Node> &successor, vector<Node> &closed){
	int indexBestChoice = 0;
	for(int i = 0; i < successor.size(); i++){
		if(successor[i].combinedScore < 
			successor[indexBestChoice].combinedScore){
			indexBestChoice = i;
			cout << "indexBestChoice: " << i << endl;
		}
	}
	int position = p.locateEmptySpace();		
	p = successor[indexBestChoice];
	moves.push_back(p.board[position].value);
	closed.push_back(p);
}	

// Main 
int main(int argc, char *argv[]){

	// Handling command line arguments
	string filename = "";
	vector<int> inputValues;
	
	if(argc == 2){ // store filename
		filename = argv[1];
	} // end if
	else { // terminate if invalid or no filename
		cout << "ERROR: Invalid filename." << endl;
		return 0;
	} // end else

	// Data
	vector<Node> successorNodes;
	vector<Node> closedNodes;
	vector<int> moves;

	// Initialize board
	readFromInputFile(filename, inputValues);
	Node puzzle(inputValues);
	closedNodes.push_back(puzzle);
	
	// Find a solution with heuristic 2: 
	// number of tiles out of place relative to goal
	while(puzzle.tilesOutOfPlaceRelativeToGoal() > 0){
		expandNode(puzzle, successorNodes);
		nextMove(moves, puzzle, successorNodes, closedNodes);
		cout << "Decision: " << endl;
		puzzle.printBoard();
		cout << endl;
	}
	printSolutionOutOfPlace(moves);
		
	return 0;
} // end main

