#include<iostream>
#include "Person.h"
#include "SmartArray.h"
using namespace std;

int main() {
    //Person p("Mi Dleaged", 42, 1.69, 130);
    Person p;

    cin >> p;
    // NOTE: We have declared this operation in Person.h and implemented it in Person.cpp
    cout << p << endl;

    SmartArray arr1(SmartArray::fromString("1 2 3"));
    SmartArray arr2(SmartArray::fromString("4 5 6"));

    // NOTE: += is a bit questionable, << would have been a better overload for this behavior (it is called an "insertion" operator and that's what we do here, the QT framework uses that),
    // but we've already shown << overload for Person and that's why we're using something else so we can show other operators too
    arr1 += arr2;

    cout << arr1.toString() << endl;
    cout << arr2.toString() << endl;

    return 0;
}
