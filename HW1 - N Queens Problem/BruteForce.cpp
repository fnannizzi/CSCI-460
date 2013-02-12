// Author: Francesca Nannizzi					
// Date: 2.11.13									
// Purpose: HW1 for CSCI 460: N-Queens Problem	
// - - - - - - - - - - - - - - - - - - - - - - -	| 

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// Mark the column and row spaces as unavailable
void columnsAndRows(int y, int x, int **b, int nQ, int N){ 
	for(int i = 0; i < N; i++){
		if(b[y][i] == 99){
			b[y][i] = nQ;
		}
		if(b[i][x] == 99){
			b[i][x] = nQ;
		}
	}
}

// Mark the diagonal spaces as unavailable
void diagonalMoves(int y, int x, int **b, int nQ, int N, int yChange, int xChange){ 
	while((y >= 0) && (x >= 0) && (y < N) && (x < N)){
		if(b[y][x] == 99){
			b[y][x] = nQ;
		}
		y += yChange;
		x += xChange;
	}		
}

// Mark any spaces taken by knight moves as unavailable
void knightMoves(int y, int x, int **b, int nQ, int N){
	if((y >= 0) && (y < N)){
		if((x >= 0) && (x < N)){
			if(b[y][x] == 99){
				b[y][x] = nQ;	
			}
		}
	}
}

// Print the board (for testing)
void printArray(int **b, int N){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cout << setw(3) << b[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
}

// Print the solution array (for testing)
void printSolutions(int **qP, int N){
	for(int i = 0; i < N; i++){
		cout << "(" << qP[0][i] << "," << qP[1][i] << "), ";
	}
	cout << endl;
}

// Main 
int main(int argc, char *argv[]){

	// Variable Declarations
	int n, numSolutions = 0, numQueens = 0;
	int yPos = 0, xPos = -1;
	int yShift = 0, xShift = 0;
	bool solutionsRemaining = true, posFound = false;
	int numSolutionsRecorded = 0;

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

		// Declare arrays and vectors
		int** board = new int*[n];
		int** queenPositions = new int*[n];
		vector<int**> solutions;

		// Initialize 2D arrays
		for(int i = 0; i < n; i++){
			board[i] = new int[n];
			queenPositions[i] = new int[2];
		}
		
		// Mark all board spaces as 99 (an available space)
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				board[i][j] = 99;
			}
		}
		
		// Solution algorithm
		while(solutionsRemaining){
			posFound = false;
			while(!posFound){
				if(yPos < (n-1)){
					if(xPos < (n-1)){
						xPos++;
					}
					else {
						xPos = 0;
						yPos++;
					}
				}
				else {
					if(xPos < (n-1)){
						xPos++;
					}
				}

				if(board[yPos][xPos] == 99){
					board[yPos][xPos] = 60 + numQueens;
					queenPositions[0][numQueens] = xPos;
					queenPositions[1][numQueens] = yPos;				
					posFound = true;
				}
				else {
					if((yPos == (n-1)) && (xPos == (n-1))){		
						if(numQueens == (n-1)){
							solutionsRemaining = false;							
							break;
						}
						else {
							
						}
					}
				}
				cout << yPos << xPos << endl;
			}

			// Make spaces taken by horizontal or vertical moves unavailable
			//cout << "Removing columns and rows" << endl;
			columnsAndRows(yPos, xPos, board, numQueens, n); 
			
			// Make spaces taken by diagonal moves unavailable
			yShift = yPos - 1;
			xShift = xPos - 1;
			//cout << "Moving to upper left" << endl;
			diagonalMoves(yShift, xShift, board, numQueens, n, -1, -1);
			
			yShift = yPos + 1;
			xShift = xPos + 1;
			//cout << "Moving to lower right" << endl;
			diagonalMoves(yShift, xShift, board, numQueens, n, 1, 1);
			
			yShift = yPos + 1;
			xShift = xPos - 1;
			//cout << "Moving to lower left" << endl;
			diagonalMoves(yShift, xShift, board, numQueens, n, 1, -1);
			
			yShift = yPos - 1;
			xShift = xPos + 1;
			//cout << "Moving to upper right" << endl;
			diagonalMoves(yShift, xShift, board, numQueens, n, -1, 1);

			// Make spaces taken by knight moves unavailable			
			//cout << "Finding knight moves" << endl;
			yShift = yPos - 2;
			xShift = xPos - 1;
			knightMoves(yShift, xShift, board, numQueens, n);

			yShift = yPos - 2;
			xShift = xPos + 1;
			knightMoves(yShift, xShift, board, numQueens, n);
			
			yShift = yPos - 1;
			xShift = xPos + 2;
			knightMoves(yShift, xShift, board, numQueens, n);
		
			yShift = yPos + 1;
			xShift = xPos + 2;
			knightMoves(yShift, xShift, board, numQueens, n);

			yShift = yPos + 2;
			xShift = xPos + 1;
			knightMoves(yShift, xShift, board, numQueens, n);

			yShift = yPos + 2;
			xShift = xPos - 1;
			knightMoves(yShift, xShift, board, numQueens, n);

			yShift = yPos - 1;
			xShift = xPos - 2;
			knightMoves(yShift, xShift, board, numQueens, n);

			yShift = yPos + 1;
			xShift = xPos - 2;
			knightMoves(yShift, xShift, board, numQueens, n);

			numQueens++;
			printArray(board, n);
		}
	}
	return 0;
}
