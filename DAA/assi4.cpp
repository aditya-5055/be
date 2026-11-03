#include <iostream>
#include <vector>
using namespace std;

// Check whether it is safe to place a queen
bool isSafe(vector<vector<int>>& board, int row, int col, int n) {

    // Check same column
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1)
            return false;
    }

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1;
         i >= 0 && j >= 0;
         i--, j--) {
        if (board[i][j] == 1)
            return false;
    }

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1;
         i >= 0 && j < n;
         i--, j++) {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}

// Place queens using backtracking
bool solve(vector<vector<int>>& board, int row, int n) {

    // All queens are placed
    if (row == n)
        return true;

    // Try every column in the current row
    for (int col = 0; col < n; col++) {

        if (isSafe(board, row, col, n)) {

            // Place queen
            board[row][col] = 1;

            // Place queen in next row
            if (solve(board, row + 1, n))
                return true;

            // Backtrack
            board[row][col] = 0;
        }
    }

    return false;
}

int main() {
    int n;
    cout << "Enter value of N: ";
    cin >> n;

    // Create N x N board
    vector<vector<int>> board(n, vector<int>(n, 0));

    // Solve the N-Queens problem
    if (solve(board, 0, n)) {

        cout << "\nSolution:\n";

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
    else {
        cout << "No solution exists";
    }

    return 0;
}