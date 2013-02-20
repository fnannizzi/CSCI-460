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

// Main 
int main(int argc, char *argv[]){

	// Variable Declarations
	string filename = "";
	vector<int> inputValues;

	// Handling command line arguments
	if(argc == 2){ // store filename
		filename = argv[1];
	} // end if
	else { // terminate if invalid or no filename
		cout << "ERROR: Invalid filename." << endl;
		return 0;
	} // end else

	readFromInputFile(filename, inputValues);
		
	return 0;
} // end main

