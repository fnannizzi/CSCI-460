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
void expandNode(Node* p, vector<Node> &successor){
	int position = p->locateEmptySpace();
	//cout << "Address of predecessor from expandNode: " << p << endl;
	//cout << "Current board from expandNode: " << endl;
	//p->printBoard();
	//cout << endl;
	for(int i = 0; i < p->board[position].numLinks; i++){
		vector<tile> tempBoard = p->board;
		Node node(p, tempBoard, p->numMovesToNode); 
		cout << "Position to move tiles from expandNode: " 
		<< p->board[position].links[i] << ", " << position << endl;
		cout << "Current board from expandNode: " << endl;
		node.printBoard();
		node.moveTilePosition(p->board[position].links[i], position);
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
int locateBestSuccessorNode(Node* p, vector<Node> successor, vector<Node> closed){
	cout << "IN LOCATEBEST Current puzzle board from locate...: " << endl;
	p->printBoard();
	cout << "Address of current board from locate...: " << p << endl;
	cout << endl;
	
	int index = 0;
	for(int i = 0; i < successor.size(); i++){
		//cout << "Node " << i << endl; // debugging
		//cout << "Score: " << successor[i].numTilesOutOfPlace << endl; // debugging
		
		if(!matchClosedNodes(successor[i], closed)){ // if the node has not already been expanded
			//cout << "MatchClosedNodes didn't fail" << endl;
			//cout << "Address of predecessor from locate...: " << successor[i].predecessorNode << endl;
			//successor[i].predecessorNode->printBoard();
			//cout << "Address of current board from locate...: " << &p << endl;
			//p->printBoard();
			//cout << endl;
			if(successor[i].predecessorNode->matchBoard(p->board)){ // if the node is at the correct depth
				cout << "Predecessor matches" << endl;
				cout << "Node " << i << endl; // debugging
				cout << "Score: " << successor[i].numTilesOutOfPlace << endl; // debugging
				if(successor[i].combinedScore <= successor[index].combinedScore){
					index = i;
					cout << "Index: " << i << endl; //debugging
				} // end if
				successor[i].printBoard(); // debugging
				cout << endl; // debugging
			} // end if
		} // end if 
		//successor[i].printBoard(); // debugging
		//cout << endl; // debugging
	} // end for
	if(index == 0){
		if(matchClosedNodes(successor[index], closed)){
			cout << "FAILURE: successor is closed" << endl;
			index = -1;
		} // end if
		else if(!successor[index].predecessorNode->matchBoard(p->board)){
			cout << "FAILURE: successor not from predecessor" << endl;
			index = -1;
		} // end if
	} // end if	
	return index;
}

// Make next move based on number of tiles out of place relative to goal
Node nextMove(vector<int> &moves, Node* p, vector<Node> &successor, vector<Node> &closed){
	//cout << "IN NEXTMOVE Current puzzle board from nextMove: " << endl;
	//p->printBoard();
	//cout << "Address of current board from nextMove: " << p << endl;
	
	Node puzzleCopy = *p;
	int indexBestChoice = 0;

	for(int i = 0; i < successor.size(); i++){
		//cout << "Node " << i << endl; // debugging
		//cout << "Score: " << successor[i].numTilesOutOfPlace << endl; // debugging
		//puzzleCopy.printBoard();
		if(!matchClosedNodes(successor[i], closed)){ // if the node has not already been expanded
			//cout << "MatchClosedNodes didn't fail" << endl;
			//puzzleCopy.printBoard();
			//cout << "Address of predecessor from nextMove...: " << successor[i].predecessorNode << endl;
			//successor[i].predecessorNode->printBoard();
			cout << "Address of current board from nextMove...: " << &p << endl;
			puzzleCopy.printBoard();
			cout << endl;
			if(successor[i].predecessorNode->matchBoard(puzzleCopy.board)){ // if the node is at the correct depth
				cout << "Predecessor matches" << endl;
				cout << "Node " << i << endl; // debugging
				cout << "Score: " << successor[i].numTilesOutOfPlace << endl; // debugging
				if(successor[i].numTilesOutOfPlace <= successor[indexBestChoice].numTilesOutOfPlace){
					indexBestChoice = i;
					cout << "Index: " << i << endl; //debugging
				} // end if
				successor[i].printBoard(); // debugging
				cout << endl; // debugging
			} // end if
		} // end if 
		//successor[i].printBoard(); // debugging
		//cout << endl; // debugging
	} // end for
	if(indexBestChoice == 0){
		if(matchClosedNodes(successor[indexBestChoice], closed)){
			cout << "FAILURE: successor is closed" << endl;
			indexBestChoice = -1;
		} // end if
		else if(!successor[indexBestChoice].predecessorNode->matchBoard(puzzleCopy.board)){
			cout << "FAILURE: successor not from predecessor" << endl;
			indexBestChoice = -1;
		} // end if
	} // end if	
	
	if(indexBestChoice >= 0){ //successor found
		int position = puzzleCopy.locateEmptySpace();		
		//cout << "Address of current board from nextMove: " << p << endl;
		Node* tempAddress = p;
		Node tempNode = successor[indexBestChoice];
		tempNode.predecessorNode = tempAddress;
		cout << "Address of updated board predecessor from nextMove: " << tempNode.predecessorNode << endl;
		moves.push_back(tempNode.board[position].value);
		closed.push_back(tempNode);
		successor.erase(successor.begin() + indexBestChoice);
		return tempNode;
	}
	else { // no successors found
		cout << "OriginalStateOfBoard: " << p->isOriginalStateOfBoard << endl;
		if(p->isOriginalStateOfBoard){
			cout << "No successors found for original state of board" << endl;
			moves.pop_back();
			//nextMove(moves, p, successor, closed);
			return *p;
		}
		else {
			cout << "No successors found, begin backtracking" << endl;
			Node tempNode = *p;
			tempNode.revertToPredecessor();
			moves.pop_back();
			nextMove(moves, p, successor, closed);
			return tempNode;
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

	// Initialize board
	readFromInputFile(filename, inputValues);
	Node initialNode(inputValues);
	Node* puzzle = &initialNode;
	closedNodes.push_back(*puzzle);
	
	// Find a solution with heuristic 2: 
	// number of tiles out of place relative to goal
	while(puzzle->tilesOutOfPlaceRelativeToGoal() > 0){
		//cout << "AFTER WHILE Current puzzle board from main: " << endl;
		//puzzle->printBoard();
		//cout << endl;
		expandNode(puzzle, successorNodes);
		//cout << "AFTER EXPANDNODE Current puzzle board from main: " << endl;
		//puzzle->printBoard();
		Node current = nextMove(moves, puzzle, successorNodes, closedNodes);
		//cout << "DECISION: " << endl;
		//current.printBoard();
		//cout << endl;
		count++;
		puzzle = &current;
		cout << "Address of puzzle from main: " << puzzle << endl;
		
		if(count > 10){
			//return 0;
		}
	}
	printSolutionOutOfPlace(moves);
	puzzle->printBoard();
		
	return 0;
} // end main

