// Author: Francesca Nannizzi					
// Date: 2.19.13									
// Purpose: HW2 for CSCI 460: Nine Tile Puzzle	
// - - - - - - - - - - - - - - - - - - - - - - -	| 

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

struct tile {
	int value;
	int numLinks;
	int* links;
	
	// Constructor
	tile(int v, int nL){
		value = v;
		numLinks = nL;
		links = new int[numLinks];
	}
};

class Node {
	public:
		// Data
		vector<tile> board;
		vector<int> moves;
	
		// Functions
		Node(vector<int>);
		Node(vector<tile>, vector<int>);
		~Node();
		void addEdgesToTiles();
		void loadInputIntoTiles(vector<int>);
		void printBoard();
		int tilesOutOfPlaceRelativeToGoal();
		int manhattanDistance();
		void moveTilePosition(int, int);
		int locateEmptySpace();
		bool matchBoard(vector<tile>);
		bool operator == (Node);
		bool searchLinksRound1(int, int);
		bool searchLinksRound2(int, int);
		bool searchLinksRound3(int, int);

};

#endif
