// https://judge.softuni.bg/Contests/Compete/Index/502#2

#include<iostream>

using namespace std;

void filler(int, int, char[][20], const int, const int, const char, const char);

int main()
{
    int rows, columns;
    cin >> rows >> columns;

    char arr[rows][20];

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            cin >> arr[r][c];
        }
    }

    char fill_char;
    cin >> fill_char;

    int start_row, start_col;
    cin >> start_row >> start_col;

    char start_char = arr[start_row][start_col];

    filler(start_row, start_col, arr, rows, columns, fill_char, start_char);

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            cout << arr[r][c] << " ";
        }

        cout << endl;
    }

    return 0;
}

void filler(int row, int col, char arr[][20], const int rows, const int columns, const char fill_char, const char start_char)
{
    arr[row][col] = fill_char;

    if (row + 1 < rows && arr[row + 1][col] == start_char)
    {
        filler(row + 1, col, arr, rows, columns, fill_char, start_char);
    }

    if (row - 1 >= 0 && arr[row - 1][col] == start_char)
    {
        filler(row - 1, col, arr, rows, columns, fill_char, start_char);
    }

    if (col + 1 < columns && arr[row][col + 1] == start_char)
    {
        filler(row, col + 1, arr, rows, columns, fill_char, start_char);
    }

    if (col - 1 >= 0 && arr[row][col - 1] == start_char)
    {
        filler(row, col - 1, arr, rows, columns, fill_char, start_char);
    }
}
