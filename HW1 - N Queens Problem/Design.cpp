// Author: Francesca Nannizzi					
// Date: 2.11.13									
// Purpose: HW1 for CSCI 460: N-Queens Problem	
// - - - - - - - - - - - - - - - - - - - - - - -	| 

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// Main 
int main(int argc, char *argv[]){

	// Variable Declarations
	int n, numSolutions = 0, numQueens = 0;
	int yPos = 0, xPos = -1;
	int yStart = 0, xStart = 0;
	bool solutionsRemaining = true, initialTrace = true, beginBacktrace = false;
	bool solutionsFound = false;
	int numSolutionsRecorded = 0;
	int count = 0;

	// Handling command line arguments
	if(argc == 0){ // if user forgets to specify n, ask them
		cout << "Enter a number between 0 and 14: " << endl;
		cin >> n;
		cout << "You have entered: " << n << endl;
	}
	else { // otherwise, process the arguments
		n = atoi(argv[1]);
		cout << n << endl;
	}

	if((n >= 0) && (n < 15)){ // check to see if n is valid

		// Initialize 2D board array
		int** board = new int*[n];
		for(int i = 0; i < n; i++){
			board[i] = new int[n];
		}

		// Mark all board spaces as 99 (an available space)
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				board[i][j] = 99;
			}
		}

		// Initialize 2D solution array
		int* queenPositions = new int[n*2];
		for(int i = 0; i < (n*2); i++){
			queenPositions[i] = -1;
		}

		// Initialize solutions vector
		vector<int*> solutions;
		
		// Solution algorithm
		while(solutionsRemaining){ // runs as long as not every solution has been found
			updatePosition(yPos, xPos, n); // needs to check against "tried positions"
			if(board[yPos][xPos] == 99){ // position found
				// update queen positions
				// edit board
				// remove columns and rows, diagonals, knights
				// increment numqueens					
			} // end if
			else { // position not found
				if((yPos == (n-1)) && (xPos == (n-1))){		
					if(numQueens == n){
						// new solution found
						// store solution
					}
					else {
						// if function checkRemainingPositions turns up nothing, clear "tried positions"
					}
					// add position of last queen to "tried positions"
					// remove last placed queen and clear blocked out spaces
					// decrement numQueens
					// if numQueens = 0 and you are at the last position, break
				}
			}	
		} // end while solutionsRemaining
	} // end if n
	return 0;
}
