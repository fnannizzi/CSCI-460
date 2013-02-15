// Author: Francesca Nannizzi					
// Date: 2.11.13									
// Purpose: HW1 for CSCI 460: N-Queens Problem	
// - - - - - - - - - - - - - - - - - - - - - - -	| 

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// Increment y or x position marker
void updatePosition(int &y, int &x, int N){
	if(y < (N-1)){
		if(x < (N-1)){
			x++;
		}
		else {
			x = 0;
			y++;
		}
	}
	else {
		if(x < (N-1)){
			x++;
		}
	}
}

// Mark the column and row spaces as unavailable
void columnsAndRows(int y, int x, int **b, int nQ, int N){ 
	for(int i = 0; i < N; i++){
		if(b[y][i] == 99){
			cout << "Removing rows " << i << endl;
			b[y][i] = nQ;
		}
		if(b[i][x] == 99){
			cout << "Removing columns " << i << endl;
			b[i][x] = nQ;
		}
	}
}

// Mark the diagonal spaces as unavailable
void checkDiagonalMoves(int y, int x, int **b, int nQ, int N, int yChange, int xChange){ 
	while((y >= 0) && (x >= 0) && (y < N) && (x < N)){
		if(b[y][x] == 99){
			cout << "Removing diagonals " << x << y << endl;
			b[y][x] = nQ;
		}
		y += yChange;
		x += xChange;
	}		
}

// Call checkDiagonalMoves with correct arguments to search in all directions
void diagonalMoves(int y, int x, int **b, int nQ, int N){
	int yShift, xShift;
	
	yShift = y - 1;
	xShift = x - 1;
	//cout << "Moving to upper left" << endl;
	checkDiagonalMoves(yShift, xShift, b, nQ, N, -1, -1);
			
	yShift = y + 1;
	xShift = x + 1;
	//cout << "Moving to lower right" << endl;
	checkDiagonalMoves(yShift, xShift, b, nQ, N, 1, 1);
			
	yShift = y + 1;
	xShift = x - 1;
	//cout << "Moving to lower left" << endl;
	checkDiagonalMoves(yShift, xShift, b, nQ, N, 1, -1);
			
	yShift = y - 1;
	xShift = x + 1;
	//cout << "Moving to upper right" << endl;
	checkDiagonalMoves(yShift, xShift, b, nQ, N, -1, 1);
}

// Mark any spaces taken by knight moves as unavailable
void checkKnightMoves(int y, int x, int **b, int nQ, int N){
	if((y >= 0) && (y < N)){
		if((x >= 0) && (x < N)){
			if(b[y][x] == 99){
				cout << "Removing knights " << x << y << endl;
				b[y][x] = nQ;	
			}
		}
	}
}

// Call checkKnightMoves with correct arguments to search in all directions
void knightMoves(int y, int x, int **b, int nQ, int N){
	int yShift, xShift;
	
	yShift = y - 2;
	xShift = x - 1;
	checkKnightMoves(yShift, xShift, b, nQ, N);

	yShift = y - 2;
	xShift = x + 1;
	checkKnightMoves(yShift, xShift, b, nQ, N);
			
	yShift = y - 1;
	xShift = x + 2;
	checkKnightMoves(yShift, xShift, b, nQ, N);
		
	yShift = y + 1;
	xShift = x + 2;
	checkKnightMoves(yShift, xShift, b, nQ, N);

	yShift = y + 2;
	xShift = x + 1;
	checkKnightMoves(yShift, xShift, b, nQ, N);

	yShift = y + 2;
	xShift = x - 1;
	checkKnightMoves(yShift, xShift, b, nQ, N);

	yShift = y - 1;
	xShift = x - 2;
	checkKnightMoves(yShift, xShift, b, nQ, N);

	yShift = y + 1;
	xShift = x - 2;
	checkKnightMoves(yShift, xShift, b, nQ, N);
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
void printSolution(int *qP, int N){
	for(int i = 0; i < N; i++){
		cout << "(" << qP[(i*2) + 1] << "," << qP[i*2] << "), ";
	}
	cout << endl;
}

// Print multiple solutions (for testing)
void printAllSolutions(vector<int*> &s, int N){
	int* sArr;  
	for(int i = 0; i < s.size(); i++){
		sArr = s[i];
		cout << "Solution " << (i + 1) << ":" << endl;
		for(int j = 0; j < N; j++){
			cout << "(" << sArr[j*2] << "," << sArr[(j*2) + 1] << "), ";
		}
		cout << endl;
	}	
}

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
		while(solutionsRemaining){
			while(!solutionsFound){
				initialTrace = true;
				while(initialTrace){
					while(!positionFound){
						updatePosition(yPos, xPos, n);
						if(board[yPos][xPos] == 99){
							board[yPos][xPos] = (40 + numQueens);
							queenPositions[numQueens*2] = yPos;
							queenPositions[(numQueens*2) + 1] = xPos;	
							printSolution(queenPositions, n);	
						}
						else {
							if((yPos == (n-1)) && (xPos == (n-1))){		
								if(numQueens == n){
									solutions.push_back(queenPositions);
									printAllSolutions(solutions, n);
									solutionFound = true;							
									break;
								}
								else {
									cout << "beginning backtrace" << endl;
									beginBacktrace = true;
									updatePosition(yPos, xPos, n);
									for(int i = 0; i < n; i++){
										for(int j = 0; j < n; j++){
											if(board[i][j] == numQueens){
												board[i][j] = 99;
											}
										}
									}
									numQueens--;	
									printSolution(queenPositions, n);
									board[queenPositions[numQueens*2]][queenPositions[(numQueens*2) + 1]] = 99;
									queenPositions[numQueens*2] = -1;
									queenPositions[(numQueens*2) + 1] = -1;
									posFound = true;
								}
							}
						}
					}
					// Make spaces taken by horizontal or vertical moves unavailable
					columnsAndRows(yPos, xPos, board, numQueens, n); 
			
					// Make spaces taken by diagonal moves unavailable
					diagonalMoves(yPos, xPos, board, numQueens, n);

					// Make spaces taken by knight moves unavailable			
					knightMoves(yPos, xPos, board, numQueens, n);

					numQueens++;
					count++;
					cout << count << endl;
					printArray(board, n);
					if(count == 11){
						break;
					}	
				}
			}
			if((yStart == (n-1)) && (xStart == (n-1))){

			}
			updatePosition(yStart, xStart, n);
			solutionsFound = false;
		}
	}
	return 0;
}
