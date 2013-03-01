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
void printSolution(string text, Node solution){
	cout << text << endl;
	cout << "Sequence of tiles to be moved: ";
	for(int i = 0; i < solution.moves.size(); i++){
		cout << solution.moves[i] << " ";
	}
	cout << endl;
	cout << "Number of moves: " << solution.moves.size() << endl;
}

// Compare successor node to all closed nodes
bool matchClosedNodes(Node successor, vector<Node> closed){
	for(int i = 0; i < closed.size(); i++){
		if(successor.matchBoard(closed[i].board)){
			//if(closed[i].tilesOutOfPlaceRelativeToGoal() < successor.tilesOutOfPlaceRelativeToGoal()){
				return true;
			//}
		}
	}
	return false;
}

// Compare successor node to all open nodes
bool matchOpenNodes(Node successor, vector<Node> open){
	for(int i = 0; i < open.size(); i++){
		if(successor.matchBoard(open[i].board)){
			//if(open[i].tilesOutOfPlaceRelativeToGoal() < successor.tilesOutOfPlaceRelativeToGoal()){
				return true;
			//}
		}
	}
	return false;
}

// Expand a node
void expandNode(Node search, vector<Node> open, vector<Node> &successor, vector<Node> closed){
	successor.clear();
	int position = search.locateEmptySpace();
	for(int i = 0; i < search.board[position].numLinks; i++){
		Node node(search.board, search.moves);
		node.moveTilePosition(search.board[position].links[i], position);
		if(matchClosedNodes(node, closed)){
			// hey
		}
		else if(matchOpenNodes(node, open)){
			// ho
		}
		else {
			successor.push_back(node);
		}
	}
}

// Determines the next node to expand for Manhattan distance
Node nextNodeManhattanDistance(vector<Node> &open){
	int index = 0;
	for(int i = 0; i < open.size(); i++){
		if(open[i].manhattanDistance() < 
		   open[index].manhattanDistance()){
		 	index = i;  
		}
	}
	Node returnNode = open[index];
	open.erase(open.begin() + index);
	return returnNode;
}	

// Determines the next node to expand for misplaced tiles
Node nextNodeMisplacedTiles(vector<Node> &open){
	int index = 0;
	for(int i = 0; i < open.size(); i++){
		if(open[i].tilesOutOfPlaceRelativeToGoal() < 
		   open[index].tilesOutOfPlaceRelativeToGoal()){
		 	index = i;  
		}
	}
	Node returnNode = open[index];
	open.erase(open.begin() + index);
	return returnNode;
}	

// Adds list of successor nodes to open nodes
void addSuccessorsToOpenList(vector<Node> successor, vector<Node> &open){
	for(int i = 0; i < successor.size(); i++){
		open.push_back(successor[i]);
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
	vector<Node> openNodes;
	vector<Node> closedNodes;

	// Initialize board
	readFromInputFile(filename, inputValues);
	Node initialNode(inputValues);
	
	Node searchNode = initialNode;
	openNodes.push_back(searchNode);
	
	int count = 0;
	
	// Find a solution using manhattan distance
	while(!openNodes.empty()){
		expandNode(searchNode, openNodes, successorNodes, closedNodes);
		addSuccessorsToOpenList(successorNodes, openNodes);
		closedNodes.push_back(searchNode);
		searchNode = nextNodeManhattanDistance(openNodes);
		//cout << "Decision: " << count << endl;
		//cout << "MD: " << searchNode.manhattanDistance() << endl;
		//searchNode.printBoard();
		//cout << endl;
		count++;
		if(count > 10){
			//break;
		}
		if(searchNode.manhattanDistance() == 0){
			break;
		}
	}
	printSolution("Manhattan Distance: ", searchNode);
	searchNode.printBoard();	
	
	
	// Reinitialize board and vectors
	successorNodes.clear();
	openNodes.clear();
	closedNodes.clear();
	searchNode = initialNode;
	openNodes.push_back(searchNode);
	
	count = 0;
	
	// Find a solution using number of tiles out of place relative to goal
	while(!openNodes.empty()){
		expandNode(searchNode, openNodes, successorNodes, closedNodes);
		addSuccessorsToOpenList(successorNodes, openNodes);
		closedNodes.push_back(searchNode);
		searchNode = nextNodeMisplacedTiles(openNodes);
		//cout << "Decision: " << count << endl;
		//searchNode.printBoard();
		//cout << endl;
		count++;
		if(count > 40){
			//break;
		}
		if(searchNode.tilesOutOfPlaceRelativeToGoal() == 0){
			break;
		}
	}
	printSolution("Number of Misplaced Tiles: ", searchNode);
	searchNode.printBoard();
	
		
	return 0;
} // end main

