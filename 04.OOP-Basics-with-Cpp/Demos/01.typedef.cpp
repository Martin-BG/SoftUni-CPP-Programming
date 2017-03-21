#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;

double * allocateArray(int arrSize, double fillNumber) {
    double * arr = new double[arrSize];

    for (int i = 0; i < arrSize; i++) {
        arr[i] = fillNumber;
    }

    return arr;
}

typedef string TenStrings[10];

void printArray(TenStrings strings) {
    for (int i = 0; i < 10; i++) {
        cout << strings[i] << " ";
    }
    cout << endl;
}

typedef bool (*StringComparator)(const string&, const string&);

void printArraySorted(TenStrings strings, StringComparator comparator) {
    if (comparator != NULL) {
        sort(strings, strings + 10, comparator);
    }

    printArray(strings);
}

bool compareByLastLetter(const string& a, const string& b) {
    return a[a.size() - 1] < b[b.size() - 1];
}

bool compareByLength(const string& a, const string& b) {
    return a.size() < b.size();
}

int main() {
    typedef unsigned long long ull;
    ull number = 42; //unsigned long long number = 42;

    TenStrings words = {"the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog", "!"};

    // print NOT sorted
    printArraySorted(words, NULL);
    cout << "---------" << endl;
    // print sorted by last letter
    printArraySorted(words, compareByLastLetter);
    cout << "---------" << endl;
    // print sorted by last letter
    printArraySorted(words, compareByLength);
    cout << "---------" << endl;
}
