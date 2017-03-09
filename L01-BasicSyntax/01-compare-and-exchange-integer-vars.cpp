/*Write a conditional statement that examines two integer variables
and exchanges their values if the first one is greater than the
second one.*/

#include <iostream>
using namespace std;

int main()
{
    int num1;
    int num2;

    cout << "Enter two integer numbers: ";
	
    cin >> num1 >> num2;

    if (num1 > num2)
    {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }

    cout << num1 << " <= " << num2 << endl;

	return 0;
}
