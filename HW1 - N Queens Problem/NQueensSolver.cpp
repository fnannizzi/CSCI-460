// Author: Francesca Nannizzi					
// Date: 2.11.13									
// Purpose: HW1 for CSCI 460: N-Queens Problem	
// - - - - - - - - - - - - - - - - - - - - - - -	| 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

// Define position struct
struct coordinate {
	int x, y;
}; 

// Find a new, unblocked position
void incrementPosition(int &y, int &x, int N, int** b){
	int last = x;
	x = -2; 
	
	for(int i = last; i < N; i++){
		if(b[y][i] == 99){
			x = i;
			break;
		}
	}
}

// Verify new position
bool updatePosition(int &y, int &x, int N, int** b){
	bool check = true;
	int xTemp = x + 1;
	
	incrementPosition(y, xTemp, N, b);
	
	if(xTemp > x){
		x = xTemp;
	}	
	else {
		check = false;
	}
	return check;
}

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
void checkDiagonalMoves(int y, int x, int **b, int nQ, int N, int yChange, int xChange){ 
	while((y >= 0) && (x >= 0) && (y < N) && (x < N)){
		if(b[y][x] == 99){
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
	checkDiagonalMoves(yShift, xShift, b, nQ, N, -1, -1);
			
	yShift = y + 1;
	xShift = x + 1;
	checkDiagonalMoves(yShift, xShift, b, nQ, N, 1, 1);
			
	yShift = y + 1;
	xShift = x - 1;
	checkDiagonalMoves(yShift, xShift, b, nQ, N, 1, -1);
			
	yShift = y - 1;
	xShift = x + 1;
	checkDiagonalMoves(yShift, xShift, b, nQ, N, -1, 1);
}

// Mark any spaces taken by knight moves as unavailable
void checkKnightMoves(int y, int x, int **b, int nQ, int N){
	if((y >= 0) && (y < N)){
		if((x >= 0) && (x < N)){
			if(b[y][x] == 99){
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

bool checkRemainingPositions(int **b, int N, vector<coordinate> tP){
	bool positionAvailable = false;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(b[i][j] == 99){ // position empty
				for(int k = 0; k < tP.size(); k++){
					if((i == tP[k].y) && (j == tP[k].x)){}
					else {
						return true;
					}
				}
			}
		}
	}
	return positionAvailable;
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
void printSolution(vector<coordinate> qP){
	for(int i = 0; i < qP.size(); i++){
		cout << "(" << qP[i].x << "," << qP[i].y << "), ";
	}
	cout << endl;
}

// Print multiple solutions (for testing)
void printAllSolutions(vector<vector<coordinate> > &s){ 
	for(int i = 0; i < s.size(); i++){
		cout << "Solution " << (i + 1) << ":" << endl;
		for(int j = 0; j < s[i].size(); j++){
			cout << "(" << s[i][j].x << "," << s[i][j].y << "), ";
		}
		cout << endl;
	}	
}

// Write the output to a file
void writeSolutionsToFile(string f, int N, vector<vector<coordinate> > &s){
	ofstream file;
	file.open(f.c_str());
	file << "Number of Super Queens: " << N << "\n";
	for(int i = 0; i < s.size(); i++){
		file << "Solution " << (i + 1) << ": ";
		for(int j = 0; j < s[i].size(); j++){
			file << "(" << s[i][j].x << "," << s[i][j].y << ")";
			if(j != (s[i].size() - 1)){
				file << ", ";
			}
		}
		file << "\n";
	}
	file << "Total number of solutions: " << s.size();
	file.close();
}

// Main 
int main(int argc, char *argv[]){

	// Variable Declarations
	int n, numSolutions = 0, numQueens = 0;
	int row = 0, column = -1;
	bool solutionsRemaining = true, positionFound = false;
	int numSolutionsRecorded = 0;
	string filename = "";

	// Handling command line arguments
	if(argc == 0){ // if user forgets to specify n, ask them
		cout << "Enter a number between 0 and 14: " << endl;
		cin >> n;
		cout << "You have entered: " << n << endl;
	}
	else { // otherwise, process the arguments
		n = atoi(argv[1]);
		filename = argv[2];
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
		
		// Set up a dummy coordinate to initialize queenPositions with
		coordinate blank;
		blank.x = -1;
		blank.y = -1;

		// Initialize current positions vector
		// This vector's data is overwritten often, and never fully cleared out.
		vector<coordinate> queenPositions (n, blank);

		// Initialize solutions vector
		vector<vector<coordinate> > solutions;
		
		// Solution algorithm
		
		// Reset board and data
		int count = 0;	
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				board[i][j] = 99;	
			} // end inner for
		} // end outer for
			
		// Place first queen
		numQueens = 0;
		queenPositions[numQueens].y = 0;
		queenPositions[numQueens].x = count;
		board[0][count] = (40 + numQueens);
			
		// Make spaces taken by superqueen moves unavailable
		columnsAndRows(0, count, board, numQueens, n); 
		diagonalMoves(0, count, board, numQueens, n);			
		knightMoves(0, count, board, numQueens, n);
			
		// Move down one row
		row = 1;
		column = 0;
		numQueens = 1;
			
		// Blank out all but first position
		for(int i = 1; i < n; i++){
			queenPositions[i].y = -1;
			queenPositions[i].x = -1;				
		} // end for
			
		// Begin search
		while(solutionsRemaining){				
			positionFound = updatePosition(row, column, n, board);
			if(positionFound){ // position available
				board[row][column] = (40 + numQueens);
				queenPositions[numQueens].y = row;
				queenPositions[numQueens].x = column;	
					
				// Make spaces taken by superqueen moves unavailable
				columnsAndRows(row, column, board, numQueens, n); 
				diagonalMoves(row, column, board, numQueens, n);		
				knightMoves(row, column, board, numQueens, n);
					
				numQueens++;	
				if(row < (n-1)){
					row++;
					column = -1;
				} // end if
			} // end if(positionFound)
			else { // row is unavailable	
				if(numQueens == n){ // if there are n queens on the board
					solutions.push_back(queenPositions);
					numSolutionsRecorded++;					
				} // end if(numQueens == n)
					
				if(row == 0){ // we have backtracked all the way to row 0, and should restart
					solutionsRemaining = false;
					break;
				} // end if
					
				// Return to prior state with 1 less queen
				numQueens--;
				column = queenPositions[numQueens].x;
				row = queenPositions[numQueens].y;
					
				// Blank out bad position
				queenPositions[numQueens].x = -1;
				queenPositions[numQueens].y = -1;								
					
				// Remove all traces of prior queen
				board[row][column] = 99;
				for(int i = 0; i < n; i++){
					for(int j = 0; j < n; j++){
						if(board[i][j] == numQueens){
							board[i][j] = 99;
						} // end if
					} // end inner for
				} // end outer for
			} // end else (position not available)
		} // end while
		writeSolutionsToFile(filename, n, solutions);
	} // end if((n >= 0) && (n < 15)) 
	return 0;
} // end main
