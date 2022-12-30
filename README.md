# N-Queen Problem (with Hill Climbing)

This program solves the N-Queen problem on a board with user-specified size. It solves it with Hill-Climbing, using the number of collisions (pairs of queens that can attack each other) as a heuristic.

## Usage
When running the compiled program, the user will be prompted for the size of the chessboard.

After entering it, the solution for a board of that size will be displayed (where 0 stands for empty cell, and 1 for cell with a queen on it), alongside the number of collisions on said board and the number of steps taken by the Hill Climbing process.

## Notes
- For simplicity purposes, the inner mechanics of the code handle the queens positions as a numeric array of size N, where every item represents a row, and the number inside of it represents the column on which the queen sits. In other words, every row has one and only one queen on it, by design, which also simplifies the neighbor generation and collision count.
- To count collisions on the diagonals, two small tricks are used. Adding the row and column number of a given cell helps identify the ascending (↗) diagonals, since two cells on the same diagonal will always have the same sum. For descending (↘) diagonals, subtracting the the column number from the row number achieves the same thing.