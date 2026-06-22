// 1. Create board[n][n] and initialize with 0 (empty)

// 2. Define function isSafe(row, col):
//       check column above
//       check upper-left diagonal
//       check upper-right diagonal
//       if safe → return true

// 3. Define recursive function solve(row):

// 4. If row == n:
//       print board (one solution found)
//       increment count
//       return

// 5. For each column from 0 to n-1:
//       if isSafe(row, col):
//            place queen (board[row][col] = 1)

//            call solve(row + 1)

//            remove queen (backtrack → board[row][col] = 0)

// 6. Call solve(0)

// 7. Print total number of solutions



#include <iostream>
using namespace std;

int n = 4;
int board[4][4];
int totalSolutions = 0;


bool isSafe(int row, int col) {

   
    for(int i = 0; i < row; i++)
        if(board[i][col] == 1)
            return false;

    
    for(int i=row, j=col; i>=0 && j>=0; i--, j--)
        if(board[i][j] == 1)
            return false;

  
    for(int i=row, j=col; i>=0 && j<n; i--, j++)
        if(board[i][j] == 1)
            return false;

    return true;
}


void solve(int row) {

    if(row == n) {
        totalSolutions++;

        cout << "\nSolution " << totalSolutions << ":\n";
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        return;
    }

    for(int col = 0; col < n; col++) {

        if(isSafe(row, col)) {

            board[row][col] = 1;   

            solve(row + 1);       

            board[row][col] = 0;   //  (remove queen)
        }
    }
}

int main() {

   
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            board[i][j] = 0;

    solve(0);

    cout << "\nTotal Solutions: " << totalSolutions;

    return 0;
}


// Time Complexity  = O(N!)
// Space Complexity = O(N²)