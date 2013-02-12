#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

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

void diagonalMoves(int y, int x, int **b, int nQ, int N, int yChange, int xChange){ 
	while((y >= 0) && (x >= 0) && (y < N) && (x < N)){
		if(b[y][x] == 99){
			b[y][x] = nQ;
		}
		y += yChange;
		x += xChange;
	}		
}

void knightMoves(int y, int x, int **b, int nQ, int N){
	if((y >= 0) && (y < N)){
		if((x >= 0) && (x < N)){
			if(b[y][x] == 99){
				b[y][x] = nQ;	
			}
		}
	}
}

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

int main(){ //Attempt to optimize or find pattern in the placement of the first queen

	int n, numSolutions = 0, numQueens = 0;
	int yPos = 0, xPos = -1;
	int yShift = 0, xShift = 0;
	bool solutionsRemaining = true, posFound = false;

	cout << "Enter a number between 0 and 14: " << endl;
	cin >> n;
	cout << "You have entered: " << n << endl;

	if(n > 9) {

		int** board = new int*[n];
		int** queenPositions = new int*[n];
		int* newSolution = new int[n];
		vector<int*> solutions;

		for(int i = 0; i < n; i++){
			board[i] = new int[n];
			queenPositions[i] = new int[2];
		}
		

		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				board[i][j] = 99;
			}
		}
		
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
					posFound = true;
				}
				else {
					if((yPos == n) && (xPos == n)){
						solutionsRemaining = false;
						break;
					}
				}
			}

			//cout << "Removing columns and rows" << endl;
			columnsAndRows(yPos, xPos, board, numQueens, n); 
			
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
