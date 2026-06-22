#include <iostream>
#include <vector>
using namespace std;

bool isSafe(int row, int col, int n, vector<string> &board) {
    //horizontal check
    for (int j=0; j<n; j++) {
        if (board[row][j] == 'Q') {
            return false;
        }
    }

    //vertical check
    for (int i=0; i<n; i++) {
        if (board[i][col] == 'Q') {
            return false;
        }
    }

    //left-top diagonal check
    for (int i=row, j=col; i>=0 && j>=0; i--, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    //right-top diagonal
    for (int i=row, j=col; i>=0 && j<n; i--, j++) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    return true;
}

void nQueensCalculator(vector<vector<string>> & ans, vector<string> &board, int &count, int n, int row) {
    if (row == n) {
        ans.push_back(board);
        count++;
        return;
    }

    for (int j=0; j<n; j++) {
        if (isSafe(row, j, n, board)) {
            board[row][j] = 'Q';
            nQueensCalculator(ans, board, count, n, row+1); //going forward until the nth row
            board[row][j] = '.'; //backtraacking: marking the node as not visited, so that it can be used again
        }
    }
}

vector<vector<string>> nQueens(int n, int &count) {
    vector<string> board(n, string(n, '.'));
    vector<vector<string>> ans;
    nQueensCalculator(ans, board, count, n, 0);
    return ans;
}
int main() {
    int n = 6;
    int count = 0;
    vector<vector<string>> queenPlacement = nQueens(n, count);
    for (auto &it: queenPlacement) {
        for (int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                cout << it[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    cout << count;
    return 0;
}




// function solve(row):
//     if row == N:
//         print solution
//         return

//     for col in range(N):
//         if isSafe(row, col):
//             place queen
//             solve(row + 1)
//             remove queen