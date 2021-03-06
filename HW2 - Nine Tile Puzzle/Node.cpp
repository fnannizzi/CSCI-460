// Author: Francesca Nannizzi					
// Date: 2.19.13									
// Purpose: HW2 for CSCI 460: Nine Tile Puzzle	
// - - - - - - - - - - - - - - - - - - - - - - -	| 

#include "Node.h"

using namespace std;

// Constructor for start node
Node::Node(vector<int> inputValues){
	loadInputIntoTiles(inputValues);
	addEdgesToTiles();
	moves.clear();
}

// Constructor for all other nodes
Node::Node(vector<tile> b, vector<int> m){
	board = b;
	moves = m;
}

// Deconstructor
Node::~Node(){}

bool Node::operator== (Node param){
	if(!matchBoard(param.board)){
		return false;
	}
	if(moves.size() != param.moves.size()){
		return false;
	}
	for(int i = 0; i < moves.size(); i++){
		if(moves[i] != param.moves[i]){
			return false;
		}
	}
	return true;
}

// Compares board against another board to check for a match
bool Node::matchBoard(vector<tile> b){
	if(board.size() != b.size()){ // should never occur
		return false;
	}
	for(int i = 0; i < 10; i++){
		if(board[i].value != b[i].value){
			return false;
		}
	}
	return true;
}

// Determines the index of the empty space
int Node::locateEmptySpace(){
	for(int i = 0; i < 10; i++){
		if(board[i].value == 0){
			return i;
		}
	}
	return -1;
}

// Move a tile by one position
void Node::moveTilePosition(int startPosition, int endPosition){
	if(board[endPosition].value == 0){
		for(int i = 0; i < board[startPosition].numLinks; i++){
			if(board[startPosition].links[i] == endPosition){
				int temp = board[startPosition].value;
				board[startPosition].value = 0;
				board[endPosition].value = temp;
				moves.push_back(temp);
				break;
			}
		}	
	}
	else {
		cout << "ERROR: Cannot move tile." << endl;
	}
}

// Check links for a position
bool Node::searchLinksRound1(int position, int num){
	for(int i = 0; i < board[position].numLinks; i++){
		if(board[board[position].links[i]].value == num){
			return true;
		}
	}
	return false;
}

// Check links for a position
bool Node::searchLinksRound2(int position, int num){
	for(int i = 0; i < board[position].numLinks; i++){
		for(int j = 0; j < board[board[position].links[i]].numLinks; j++){
			if(board[board[board[position].links[i]].links[j]].value == num){
				return true;
			}
		}
	}
	return false;
}

// Check links for a position
bool Node::searchLinksRound3(int position, int num){
	for(int i = 0; i < board[position].numLinks; i++){
		for(int j = 0; j < board[board[position].links[i]].numLinks; j++){
			for(int k= 0; k < board[board[board[position].links[i]].links[j]].numLinks; k++){
				if(board[board[board[board[position].links[i]].links[j]].links[k]].value == num){
					return true;
				}
			}
		}
	}
	return false;
}

// Calculate Manhattan distance to goal from particular tile
int Node::manhattanDistance(){
	int sumDistance = 0;
	for(int i = 0; i < 10; i++){
		if(board[i].value != (i + 1)){
			if(i != 9){
				if(searchLinksRound1(i, (i + 1))){
					sumDistance += 1;
				}
				else if(searchLinksRound2(i, (i + 1))){
					sumDistance += 2;
				}
				else if(searchLinksRound3(i, (i + 1))){
					sumDistance += 3;
				}
				else {
					sumDistance += 4;
				}
			}
			else if(board[i].value != 0){			
				if(searchLinksRound1(i, (i + 1))){
					sumDistance += 1;
				}
				else if(searchLinksRound2(i, (i + 1))){
					sumDistance += 2;
				}
				else if(searchLinksRound3(i, (i + 1))){
					sumDistance += 3;
				}
				else {
					sumDistance += 4;
				}
			}
		}
		//cout << sumDistance << " ";
	}
	//cout << endl;
	return sumDistance;
}

// Calculate number of tiles out of place relative to goal state
int Node::tilesOutOfPlaceRelativeToGoal(){
	int numTiles = 0;
	for(int i = 0; i < 10; i++){
		if(board[i].value != (i + 1)){
			if(i != 9){
				numTiles++;
			}
			else if(board[i].value != 0){
				numTiles++;
			}
		}
	}
	return numTiles;
}

// Print the board (for testing)
void Node::printBoard(){
	cout << "  ";
	for(int i = 0; i < 3; i++){ // Print row 1
		cout << setw(3) << board[i].value;
	}
	cout << endl;

	for(int i = 3; i < 7; i++){ // Print row 2
		cout << setw(3) << board[i].value;
	}
	cout << endl;
	
	cout << "  ";
	for(int i = 7; i < 10; i++){ // Print row 3
		cout << setw(3) << board[i].value;
	}
	cout << endl;	
}

// Add edges/links between tiles
void Node::addEdgesToTiles(){
	board[0].links[0] = 3;
	board[0].links[1] = 4;
	board[0].links[2] = 1;
	
	board[1].links[0] = 4;
	board[1].links[1] = 5;
	board[1].links[2] = 0;
	board[1].links[3] = 2;
	
	board[2].links[0] = 5;
	board[2].links[1] = 6;
	board[2].links[2] = 1;
	
	board[3].links[0] = 0;
	board[3].links[1] = 4;
	board[3].links[2] = 7;
	
	board[4].links[0] = 0;
	board[4].links[1] = 1;
	board[4].links[2] = 5;
	board[4].links[3] = 8;
	board[4].links[4] = 7;
	board[4].links[5] = 3;
	
	board[5].links[0] = 1;
	board[5].links[1] = 2;
	board[5].links[2] = 6;
	board[5].links[3] = 9;
	board[5].links[4] = 8;
	board[5].links[5] = 4;
	
	board[6].links[0] = 2;
	board[6].links[1] = 5;
	board[6].links[2] = 9;
	
	board[7].links[0] = 3;
	board[7].links[1] = 4;
	board[7].links[2] = 8;
	
	board[8].links[0] = 4;
	board[8].links[1] = 5;
	board[8].links[2] = 7;
	board[8].links[3] = 9;
	
	board[9].links[0] = 5;
	board[9].links[1] = 6;
	board[9].links[2] = 8;
}

// Load the input into tile vector
void Node::loadInputIntoTiles(vector<int> iV){
	if(board.size() > 0){
		board.clear();
	}

	// Tile 1
	tile a(iV[0], 3);
	board.push_back(a);
	
	//Tile 2
	tile b(iV[1], 4);
	board.push_back(b);	
	
	//Tile 3
	tile c(iV[2], 3);
	board.push_back(c);	
	
	//Tile 4
	tile d(iV[3], 3);
	board.push_back(d);	

	//Tile 5
	tile e(iV[4], 6);
	board.push_back(e);
	
	//Tile 6
	tile f(iV[5], 6);
	board.push_back(f);	
			
	//Tile 7
	tile g(iV[6], 3);
	board.push_back(g);	
			
	//Tile 8
	tile h(iV[7], 3);
	board.push_back(h);	
		
	//Tile 9
	tile i(iV[8], 4);
	board.push_back(i);
	
	//Tile 10
	tile j(iV[9], 3);
	board.push_back(j);	
}
