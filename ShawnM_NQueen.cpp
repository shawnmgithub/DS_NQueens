#include <stack>
#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> board;
// checks to see if there are any conflicts.  it takes in the size of the board/amount of queens the current
bool QueenConflicts(int n,int currentRow,int currentCol,vector<vector<int>> board){
	for(int i =0; i<n; i++){
		for(int j =0;j<n;j++){
			// if there is a queen placed on the current part of the loop, then test all of the possible conflicts
			if(board[i][j]==1){
				// testing the horizontal, the row is always correct but it is needed as a case to keep the program moving.
				if(currentRow==i){
				}
				// testing the vertical
				else if(currentCol == j){
					return true;
				}
				// testing the diagonal by testing the absolute value of the difference of the rows and cols 
				else if (abs(currentCol - j) == abs(currentRow - i)) {
					return true;
				}
			}	
		}
	}
	return false; 
}
int main() {
	// set variables 
	int filled = 0;
	int currentRow =0;
	int currentCol =0;
	//goback boolean variable for the main while loop. when it is false we are not going back(popping and subtracting 1 from the filled variable) when it is true we are going back.
	bool goback = false;
	//user sets the n
	int n = 0;
	// ensures the user enters a number within the datarange. 
	cout << "Type a number more than 3 and less than or equal to 20: "; 
	while(n==0) {
		cin >> n; // Get user input from the keyboard
		if(n<3||n>20){
			cout << "Please type a number is the range ";
			n=0;
		}
	}
	cout << "Your number is: " << n <<endl; // Display the input value
	// create a struct that holds 2 integers, this is so each element in the stack can hold a row value and col value.
	 struct data {
		data(int Row, int Col) : row(Row), col(Col) {}
        int row;
        int col;
    };
	//create the stack from the previously created data struct
    stack<struct data> stackQueen;
	
	// i = row
	// j = col
	// creates an n by n vector(2d-array) which will act as the board. 0's represent open spaces and 1's represent where queens are.
	vector<vector<int>> board(n, vector<int>(n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				board[i][j] = 0;
				}}
		cout<<"Inital board: " <<endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << board[i][j]<<" ";
			}
			cout << endl;
		}
	
	// place the first queen on the first spot
	board[0][0] = 1;
	// push that information to the stack.
	stackQueen.push(data(currentRow, currentCol));
	// boolean variable set to true to dictate when the while loop stops more precisly
	bool checker = true;
	// continue the loop until checker is false
  while(checker){
	  // if there isnt a conflict with the queens and the loop is not backtracking
	  if(!QueenConflicts(n,currentRow,currentCol,board) && goback == false ){
		  // add one to filled because a queen is being added
		  filled++;
		  // if filled is the same as n and there are no conflicts then end the loop.
		  if(filled == n){
			  checker = false;
		  }
		  // if it is not complete then go on to the next queen and move up a row. reset the col to check all of the columns in the new row.
		  else{
		  currentRow++;
		  currentCol=0;
		  // place a queen
		  board[currentRow][currentCol]=1;
		  // push the new queen's location to the stack.
		  stackQueen.push(data(currentRow,currentCol));
		  }
	  }
	 	// since there was a conflict pop the old queen and move it if you can still move in the current row
		else if((currentCol+1) <= (n-1)){
			//reset and pop the one that was pushed previously
			board[currentRow][currentCol] = 0;
			stackQueen.pop();
			// add one to the column to move it over to the right
			currentCol++;
			board[currentRow][currentCol] = 1;
			// push the new location of the shifted queen
			stackQueen.push(data(currentRow,currentCol));
			goback = false;
		}
		// since the queen cannot be shifted, we need to backtrack.
		else{
			// we are backtracking so goback will be true
			goback = true;
			// subtract from filled to keep it on the right queen
			filled--;
			// takes away the current queen because it needs to be popped from the stack
			board[currentRow][currentCol] = 0;
			stackQueen.pop();
			// reset the current poisiton to the queen that previously worked.
			currentCol = stackQueen.top().col;
			currentRow = stackQueen.top().row;
		}
  }
// print out the final board.
cout<<"Final Board: " << endl; 
for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << board[i][j]<<" ";
			}
			cout << endl;
		}
cout<<"1's represent queens and 0's represent blank spaces"<<endl;					
} 
/*
Queen conflict
    0.1.2.3.
0.	0 0 0 0 
1.	0 0 1 0 
2.	0 0 0 0 
3.	1 0 0 0

|2-0| = 2
|1-3| = 2

if row = testrow -> conflict
if col = test -> conflict
"current r/c"
*/
