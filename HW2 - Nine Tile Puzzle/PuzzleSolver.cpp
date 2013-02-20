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
	for(int i = 0; i < 3; i++){ // Load row 1
		tile a(iV[i], i, 2);
		t.push_back(a);
	}
	
	for(int i = 3; i < 7; i++){ // Load row 2
		if((i == 3) || (i == 6)){
			tile a(iV[i], i, 3);
			t.push_back(a);
		}
		else {
			tile a(iV[i], i, 6);
			t.push_back(a);
		}
	}
	
	for(int i = 7; i < 10; i++){ // Load row 3
		tile a(iV[i], i, 2);
		t.push_back(a);
	}
}

// Add edges/links between tiles
void addEdgesToTiles(vector<tile> &t){
	t[0].links[0] = 3;
	t[0].links[1] = 4;
	
	t[1].links[0] = 4;
	t[1].links[1] = 5;
	
	t[2].links[0] = 5;
	t[2].links[1] = 6;
	
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
	
	t[8].links[0] = 4;
	t[8].links[1] = 5;
	
	t[9].links[0] = 5;
	t[9].links[1] = 6;
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

// Main 
int main(int argc, char *argv[]){

	// Variable Declarations
	string filename = "";
	vector<int> inputValues;
	vector<tile> tiles;

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
		
	return 0;
} // end main

