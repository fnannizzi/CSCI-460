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
			//cout << "Read in " << nextInt << endl;
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
	//successor.clear();
	int position = p.locateEmptySpace();
	for(int i = 0; i < p.board[position].numLinks; i++){
		Node node(&p, p.board, p.numMovesToNode); 
		node.moveTilePosition(p.board[position].links[i], position);
		successor.push_back(node);
	}
}

// Compare successor node to all closed nodes
bool matchClosedNodes(Node successor, vector<Node> closed){
	for(int i = 0; i < closed.size(); i++){
		if(successor.matchBoard(closed[i].board)){
			return true;
		}
	}
	return false;
}

// Find successor of parent with lowest combined score
int locateBestSuccessorNode(Node p, vector<Node> successor, vector<Node> closed){
	cout << "Board as is: " << endl;
	p.printBoard();
	cout << endl;
	int index = 0;
	for(int i = 0; i < successor.size(); i++){
		cout << "Node " << i << endl; // debugging
		cout << "Score: " << successor[i].numTilesOutOfPlace << endl; // debugging
		if(!matchClosedNodes(successor[i], closed)){
			cout << "MatchClosedNodes didn't fail" << endl;
			if(*(successor[i].predecessor) == p){
				cout << "Predecessors match" << endl;
				//cout << "Node " << i << endl; // debugging
				//cout << "Score: " << successor[i].numTilesOutOfPlace << endl; // debugging
				if(successor[i].combinedScore < successor[index].combinedScore){
					index = i;
					cout << "Index: " << i << endl; //debugging
				}
				//successor[i].printBoard(); // debugging
				//cout << endl; // debugging
			}
		}
		successor[i].printBoard(); // debugging
		cout << endl; // debugging
	}
	if(index == 0){
		if(matchClosedNodes(successor[index], closed)){
			cout << "FAILURE: successor is closed" << endl;
			index = -1;
		}
		else if(!(*(successor[index].predecessor) == p)){
			cout << "FAILURE: successor not from predecessor" << endl;
			index = -1;
		}
	}
	
	return index;
}

// Make next move based on number of tiles out of place relative to goal
bool nextMove(vector<int> &moves, Node &p, vector<Node> &successor, vector<Node> &closed){
	int indexBestChoice = locateBestSuccessorNode(p, successor, closed);
	if(indexBestChoice >= 0){ //successor found
		int position = p.locateEmptySpace();		
		p = successor[indexBestChoice];
		moves.push_back(p.board[position].value);
		closed.push_back(p);
		successor.erase(successor.begin() + indexBestChoice);
		return true;
	}
	else { // no successors found
		cout << "OriginalStateOfBoard: " << p.isOriginalStateOfBoard << endl;
		if(p.isOriginalStateOfBoard){
			cout << "No successors found for original state of board" << endl;
			moves.pop_back();
			nextMove(moves, p, successor, closed);
			return false;
		}
		else {
			cout << "No successors found" << endl;
			p = *(p.predecessor);
			moves.pop_back();
			nextMove(moves, p, successor, closed);
			return false;
		}
	}
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
	int count = 0;
	bool success = true;

	// Initialize board
	readFromInputFile(filename, inputValues);
	Node puzzle(inputValues);
	closedNodes.push_back(puzzle);
	
	// Find a solution with heuristic 2: 
	// number of tiles out of place relative to goal
	while(puzzle.tilesOutOfPlaceRelativeToGoal() > 0){
		expandNode(puzzle, successorNodes);
		success = nextMove(moves, puzzle, successorNodes, closedNodes);
		if(success){
			cout << "Decision: " << endl;
			puzzle.printBoard();
			cout << endl;
			count++;
		}
		else {
			return 0;
		}
		if(count > 10){
			return 0;
		}
	}
	printSolutionOutOfPlace(moves);
		
	return 0;
} // end main

