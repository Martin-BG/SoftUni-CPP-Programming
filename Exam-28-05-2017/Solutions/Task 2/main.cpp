#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

#include "IndexedSet.h"

int indexSum(IndexedSet& s, const std::vector<int>& indices) {
    int sum = 0;
    for (int index : indices) {
        sum += s[index];
    }

    return sum;
}

std::vector<IndexedSet> readSets() {
    std::vector<IndexedSet> sets;

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "end") {
            break;
        }

        std::istringstream lineStream(line);

        IndexedSet s;
        int number;
        while (lineStream >> number) {
            s.add(number);
        }
        sets.push_back(s);
    }

    return sets;
}

std::vector<int> readIndices() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream indicesStream(line);

    std::vector<int> indices;
    int index;
    while (indicesStream >> index) {
        indices.push_back(index);
    }

    return indices;
}

int main() {
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);

    std::vector<IndexedSet> sets = readSets();

    std::vector<int> indices = readIndices();

    IndexedSet maxSet = sets[0];
    for (size_t i = 1; i < sets.size(); i++) {
        if (indexSum(sets[i], indices) > indexSum(maxSet, indices)) {
            maxSet = sets[i];
        }
    }

    for (size_t i = 0; i < maxSet.size(); i++) {
        std::cout << maxSet[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
