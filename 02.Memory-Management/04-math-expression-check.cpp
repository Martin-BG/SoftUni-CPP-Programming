/* Write a program that reads a line from the console containing a
mathematical expression. Write a bool function that checks
whether the brackets in the expression () are placed correctly
(assume everything else is correct, i.e. you don’t need to check for
correct signs, correct variables/numbers, etc.) and returns true if
they are correct and false if they are not correct
Examples of correctly placed brackets: ((a+b)/5-d); a+b; a+(b); ((a))
Examples of incorrectly placed brackets: ((a+b)/5-d; (a+b; a+b); (a)) */

#include<iostream>

using namespace std;

const int MAX_INPUT_BUFFER = 256;

bool checkBracketsInExpression(char[]);

int main()
{
    char expression_char_array[MAX_INPUT_BUFFER];
    expression_char_array[0] = '\0';

    cout << "Enter a mathematical expression, no spaces, up to "
        << MAX_INPUT_BUFFER << " symbols long." << endl << endl << "Your expression: ";

    cin >> expression_char_array;

    cout << endl << expression_char_array << " expression is "
        << (checkBracketsInExpression(expression_char_array) ? "" : "NOT ") << "correct." << endl;

    return 0;
}

bool checkBracketsInExpression(char arr[])
{
    bool is_expression_correct = true;
    int brackets = 0;
    int index = 0;

    while (arr[index] != '\0')
    {
        switch (arr[index])
        {
            case '(' : brackets++; break;
            case ')' : brackets--; break;
            default: break;
        }

        if (brackets < 0)
        {
            is_expression_correct = false;
            break;
        }

        index++;
    }

    if (brackets != 0)
    {
        is_expression_correct = false;
    }

    return is_expression_correct;
}
