#include<iostream>
using namespace std;

const int MAX_ROWS = 20;
const int MAX_COLS = 20;

char matrix[MAX_ROWS][MAX_COLS];

void fillDfs(char fillChar, char paintableChar, int row, int col) {
    // NOTE: we don't try to stay in the actual bounds of the matrix coming from the input, because:
    // 1. The max rows and cols are not big enough to affect the speed of the algorithm
    // 2. Since matrix is global, all its values are \0, which means we will never "step" on them,
    //    as our paintableChars can only be alphanumerics, since only those can be entered, according to the task description
    if (row < 0 || row >= MAX_ROWS || col < 0 || col >= MAX_COLS
        || matrix[row][col] != paintableChar) {
        return;
    }

    matrix[row][col] = fillChar;

    // fill starting from the neighboring cells, "clockwise"
    fillDfs(fillChar, paintableChar, row - 1, col);
    fillDfs(fillChar, paintableChar, row, col + 1);
    fillDfs(fillChar, paintableChar, row + 1, col);
    fillDfs(fillChar, paintableChar, row, col - 1);
}

int main() {
    int rows, cols;
    cin >> rows >> cols;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            cin >> matrix[row][col];
        }
    }

    char fillChar;
    cin >> fillChar;

    int startRow, startCol;
    cin >> startRow >> startCol;

    char startChar = matrix[startRow][startCol];

    fillDfs(fillChar, startChar, startRow, startCol);

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            cout << matrix[row][col];
        }

        cout << endl;
    }

    return 0;
}
