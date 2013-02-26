// Author: Francesca Nannizzi					
// Date: 2.19.13									
// Purpose: HW2 for CSCI 460: Nine Tile Puzzle	
// - - - - - - - - - - - - - - - - - - - - - - -	| 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

struct tile {
	int value;
	int position;
	int numLinks;
	int* links;
	
	// Constructor
	tile(int v, int p, int nL){
		value = v;
		position = p;
		numLinks = nL;
		links = new int[numLinks];
	}
};

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

// Load the input into tile vector
void loadInputIntoTiles(vector<int> iV, vector<tile> &t){
	// Tile 1
	tile a(iV[0], 0, 3);
	t.push_back(a);
	
	//Tile 2
	tile b(iV[1], 1, 4);
	t.push_back(b);	
	
	//Tile 3
	tile c(iV[2], 2, 3);
	t.push_back(c);	
	
	//Tile 4
	tile d(iV[3], 3, 3);
	t.push_back(d);	

	//Tile 5
	tile e(iV[4], 4, 6);
	t.push_back(e);
	
	//Tile 6
	tile f(iV[5], 5, 6);
	t.push_back(f);	
			
	//Tile 7
	tile g(iV[6], 6, 3);
	t.push_back(g);	
			
	//Tile 8
	tile h(iV[7], 7, 3);
	t.push_back(h);	
		
	//Tile 9
	tile i(iV[8], 8, 4);
	t.push_back(i);
	
	//Tile 10
	tile j(iV[9], 9, 3);
	t.push_back(j);	
}

// Add edges/links between tiles
void addEdgesToTiles(vector<tile> &t){
	t[0].links[0] = 3;
	t[0].links[1] = 4;
	t[0].links[2] = 1;
	
	t[1].links[0] = 4;
	t[1].links[1] = 5;
	t[1].links[2] = 0;
	t[1].links[3] = 2;
	
	t[2].links[0] = 5;
	t[2].links[1] = 6;
	t[2].links[2] = 1;
	
	t[3].links[0] = 0;
	t[3].links[1] = 4;
	t[3].links[2] = 7;
	
	t[4].links[0] = 0;
	t[4].links[1] = 1;
	t[4].links[2] = 5;
	t[4].links[3] = 8;
	t[4].links[4] = 7;
	t[4].links[5] = 3;
	
	t[5].links[0] = 1;
	t[5].links[1] = 2;
	t[5].links[2] = 6;
	t[5].links[3] = 9;
	t[5].links[4] = 8;
	t[5].links[5] = 4;
	
	t[6].links[0] = 2;
	t[6].links[1] = 5;
	t[6].links[2] = 9;
	
	t[7].links[0] = 3;
	t[7].links[1] = 4;
	t[7].links[2] = 8;
	
	t[8].links[0] = 4;
	t[8].links[1] = 5;
	t[8].links[2] = 7;
	t[8].links[3] = 9;
	
	t[9].links[0] = 5;
	t[9].links[1] = 6;
	t[9].links[2] = 8;
}

// Print the board (for testing)
void printBoard(vector<tile> t){
	cout << "  ";
	for(int i = 0; i < 3; i++){ // Print row 1
		cout << setw(3) << t[i].value;
	}
	cout << endl;

	for(int i = 3; i < 7; i++){ // Print row 2
		cout << setw(3) << t[i].value;
	}
	cout << endl;
	
	cout << "  ";
	for(int i = 7; i < 10; i++){ // Print row 3
		cout << setw(3) << t[i].value;
	}
	cout << endl;	
	
}

// Calculate number of tiles out of place relative to goal state
int tilesOutOfPlaceRelativeToGoal(vector<tile> t){
	int numTiles = 0;
	for(int i = 0; i < 10; i++){
		if(t[i].value != (i + 1)){
			if(i != 9){
				numTiles++;
			}
			else if(t[i].value != 0){
				numTiles++;
			}
		}
	}
	return numTiles;
}

/*// Calculate Manhattan distance to goal from particular tile
int manhattanDistance(vector<tile> t, int tileIndex){
	int distance = 0;
	if(t[tileIndex].value == 
}*/

// Move a tile by one position
void moveTilePosition(vector<int> &moves, int &numMoves, vector<tile> &t, int startPosition, int endPosition){
	if(t[endPosition].value == 0){
		for(int i = 0; i < t[startPosition].numLinks; i++){
			if(t[startPosition].links[i] == endPosition){
				int temp = t[startPosition].value;
				moves.push_back(temp);
				t[startPosition].value = 0;
				t[endPosition].value = temp;
				numMoves++;
				break;
			}
		}
	}
	else {
		cout << "ERROR: Cannot move tile into position that is not empty." << endl;
	}
}

// Main 
int main(int argc, char *argv[]){

	// Variable Declarations
	string filename = "";
	vector<int> inputValues;
	vector<tile> tiles;
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

	readFromInputFile(filename, inputValues);
	loadInputIntoTiles(inputValues, tiles);
	printBoard(tiles);
	addEdgesToTiles(tiles);
	
	for(int i = 0; i < 2; i++){
		cout << "num tiles out of place" << tilesOutOfPlaceRelativeToGoal(tiles) << endl;
		moveTilePosition(moves, numMoves, tiles, (i+1), i);
		printBoard(tiles);
	}
		
	return 0;
} // end main

