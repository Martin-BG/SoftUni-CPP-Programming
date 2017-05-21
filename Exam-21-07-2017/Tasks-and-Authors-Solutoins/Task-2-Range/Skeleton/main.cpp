#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Range.h"

Range readRange(std::string line) {
    Range r;
    std::istringstream in(line);

    int number;
    while(in >> number) {
        r.add(number);
    }

    return r;
}

int main() {
    std::ios::sync_with_stdio(false);

    std::string line;
    std::getline(std::cin, line);

    std::vector<Range> allRanges;

    while(line != "end") {
        Range r = readRange(line);
        allRanges.push_back(r);
        std::getline(std::cin, line);
    }

    int query;
    std::cin >> query;

    Range maxOccurrencesRange(allRanges[0]);
    for (size_t i = 1; i < allRanges.size(); i++) {
        if (allRanges[i].getCount(query) > maxOccurrencesRange.getCount(query)) {
            maxOccurrencesRange = allRanges[i];
        }
    }

    for (T value : maxOccurrencesRange) {
        std::cout << value << " ";
    }

    return 0;
}
