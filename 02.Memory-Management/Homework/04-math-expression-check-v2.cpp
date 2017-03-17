/* Write a program that reads a line from the console containing a
mathematical expression. Write a bool function that checks
whether the brackets in the expression () are placed correctly
(assume everything else is correct, i.e. you don’t need to check for
correct signs, correct variables/numbers, etc.) and returns true if
they are correct and false if they are not correct
Examples of correctly placed brackets: ((a+b)/5-d); a+b; a+(b); ((a))
Examples of incorrectly placed brackets: ((a+b)/5-d; (a+b; a+b); (a)) */

#include<iostream>

bool checkBracketsInExpression(const std::string&);

int main()
{
    std::string expression;

    std::cout << "Your expression: ";

    getline(std::cin, expression);

    std::cout << std::endl << expression << " expression is "
        << (checkBracketsInExpression(expression) ? "" : "NOT ")
        << "correct." << std::endl;

    return 0;
}

bool checkBracketsInExpression(const std::string& expression)
{
    bool is_expression_correct = true;
    int brackets = 0;
    int text_size = expression.size();

    for (int i = 0; i < text_size; i++)
    {
        switch (expression[i])
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
    }

    if (brackets != 0)
    {
        is_expression_correct = false;
    }

    return is_expression_correct;
}
