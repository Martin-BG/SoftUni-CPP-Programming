#include<iostream>
#include<sstream>
using namespace std;

#define HALF(value) value / 2.0
#define CORRECT_HALF(value) ((value) / 2.0)

int main() {
    cout << 1 / HALF(4) << endl;
    cout << HALF(4 + 4) << endl;

    cout << endl;

    cout << 1 / CORRECT_HALF(4) << endl;
    cout << CORRECT_HALF(4 + 4) << endl;

    return 0;
}
