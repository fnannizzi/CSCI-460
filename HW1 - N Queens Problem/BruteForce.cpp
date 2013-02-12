#include <iostream>
#include <iomanip>

using namespace std;

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
				cout << "after while posfound  " << xPos << yPos << endl;
				if(yPos < (n-1)){
					if(xPos < (n-1)){
						xPos++;
						cout << "in xpos < n" << endl;
					}
					else {
						xPos = 0;
						yPos++;
					}
				}
				else {
					posFound = true;
					solutionsRemaining = false;
					cout << "solutionsRemaining " << solutionsRemaining << endl;
					cout << "X" << xPos << "     Y" << yPos << endl;
					break;
				}
				if(board[yPos][xPos] == 99){
					board[yPos][xPos] = 69;
					posFound = true;
				}
			}
			cout << "X" << xPos << "     Y" << yPos << endl;	
			//cout << "Removing columns and rows" << endl;
			for(int i = 0; i < n; i++){ //take out columns and rows
				if(board[yPos][i] == 99){
					board[yPos][i] = numQueens;
				}
				if(board[i][xPos] == 99){
					board[i][xPos] = numQueens;
				}
			}
			
			yShift = yPos - 1;
			xShift = xPos - 1;
			//cout << "Moving to upper left" << endl;
			while((yShift >= 0) && (xShift >= 0)){ //move to upper left
				if(board[yShift][xShift] == 99){
					board[yShift][xShift] = numQueens;
				}
				yShift--;
				xShift--;
			}
			
			yShift = yPos + 1;
			xShift = xPos + 1;
			//cout << "Moving to lower right" << endl;
			while((yShift < n) && (xShift < n)){ //move to lower right 
				if(board[yShift][xShift] == 99){
					board[yShift][xShift] = numQueens;
				}
				//cout << yShift << xShift << endl;
				yShift++;
				xShift++;				
			}
			
			yShift = yPos + 1;
			xShift = xPos - 1;
			//cout << "Moving to lower left" << endl;
			while((yShift < n) && (xShift >= 0)){ //move to lower left 
				if(board[yShift][xShift] == 99){
					board[yShift][xShift] = numQueens;
				}
				yShift++;
				xShift--;				
			}
			
			yShift = yPos - 1;
			xShift = xPos + 1;
			//cout << "Moving to upper right" << endl;
			while((yShift >= 0) && (xShift < n)){ //move to upper right
				if(board[yShift][xShift] == 99){
					board[yShift][xShift] = numQueens;	
				}
				yShift--;
				xShift++;			
			}
			
			numQueens++;
			for(int i = 0; i < n; i++){
				for(int j = 0; j < n; j++){
					cout << setw(3) << board[i][j];
				}
				cout << endl;
			}	
		
			
		}
	}

	/*Cases
	- 0 no queens
	- 1 1 queen
	- 2 no queens
	- 3 no queens
	- 4 no queens
	- 5 no queens
	- 6 ??
	*/


	return 0;
}
