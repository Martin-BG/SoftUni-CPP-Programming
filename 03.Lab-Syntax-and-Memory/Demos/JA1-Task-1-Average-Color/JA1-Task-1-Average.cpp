#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;

const int HexComponentLength = 2;
const int HexadecimalBase = 16;

int hexToDec(string hex) {
    int dec = 0;
    for (int i = 0; i < hex.size(); i++) {
        // this is easier to imagine if the string was in decimal (0-9) and the base is 10. We add the leftmost number,
        // then for each number we "move" the other numbers with 1 position to the left (for decimal, multiplying by 10
        // "moves" to the left, leaving a 0 at the end for the new digit to occupy)
        dec = dec * HexadecimalBase;

        int digit = 0;
        if (isalpha(hex[i])) { //digit is a-f, i.e. 10-15
            digit = 10 + (hex[i] - 'a'); //A = 10, each larger letter will have a larger value of hex[i] - 'A'
        } else { //digit is 0-9
            digit = hex[i] - '0'; //0 = 0, each larger digit will have a larger value of hex[i] - '0'
        }

        dec += digit;
    }

    return dec;
}

int getColorComponent(string hexColor, int componentInd) {
    string component = hexColor.substr(HexComponentLength * componentInd, HexComponentLength);

    return hexToDec(component);
}

// NOTE: not needed, unless you uncomment line 75
/*string decToHex(int dec) {
    stringstream hexStream;
    while (dec > 0) {
        int hexDigit = dec % HexadecimalBase;
        char hexDigitChar = '0';
        if (hexDigit > 9) {
            hexDigitChar = 'a' + (hexDigit - 10);
        } else {
            hexDigitChar = '0' + hexDigit;
        }

        hexStream << hexDigitChar;
        dec /= HexadecimalBase;
    }

    string backwards = hexStream.str();
    string hexNumber;
    for (int i = backwards.size() - 1; i >= 0; i--) {
        hexNumber += backwards[i];
    }

    // NOTE: this would do the same as the above - we'll learn about it when we talk about STL
    // string hexNumber(backwards.rbegin(), backwards.rend());

    return hexNumber;
}*/

int main() {
    string hex1, hex2;

    cin >> hex1 >> hex2;

    // Cut-out the first symbol ('#') so we can just deal with the numbers
    hex1 = hex1.substr(1);
    hex2 = hex2.substr(1);

    int redAverage = (getColorComponent(hex1, 0) + getColorComponent(hex2, 0)) / 2;
    int greenAverage = (getColorComponent(hex1, 1) + getColorComponent(hex2, 1)) / 2;
    int blueAverage = (getColorComponent(hex1, 2) + getColorComponent(hex2, 2)) / 2;

    cout << "#" << hex << setw(2) << setfill('0') << redAverage
        << setw(2) << setfill('0') << greenAverage
        << setw(2) << setfill('0') << blueAverage << endl;
    // NOTE: if you really want to convert to hex yourself, use this:
    // cout << decToHex(redAverage) << decToHex(greenAverage) << decToHex(blueAverage) << endl;

    return 0;
}
