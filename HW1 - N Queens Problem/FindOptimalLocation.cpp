#include <iostream>

using namespace std;

int main(){ //Attempt to optimize or find pattern in the placement of the first queen

	int n; 

	cout << "Enter a number between 0 and 14: " << endl;
	cin >> n;
	cout << "You have entered: " << n << endl;

	int** board = new int*[n];
	for(int i = 0; i < n; i++){
		board[i] = new int[n];
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			board[i][j] = 0;
		}
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << board[i][j] << "   ";
		}
		cout << endl;
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
