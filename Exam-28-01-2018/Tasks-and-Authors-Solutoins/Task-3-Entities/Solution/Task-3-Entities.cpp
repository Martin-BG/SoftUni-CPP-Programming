#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

class Object {
private:
    unordered_map<string, string> properties;
public:
    Object() {
    }

    Object(vector<string> fieldNames, vector<string> fieldValues) {
        for (int i = 0; i < fieldNames.size(); i++) {
            properties[fieldNames[i]] = fieldValues[i];
        }
    }

    bool has(string propName) {
        return this->properties.find(propName) != this->properties.end();
    }

    string get(string propName) {
        auto propIter = this->properties.find(propName);

        if (propIter != this->properties.end()) {
            return propIter->second;
        } else {
            return "";
        }
    }
};

vector<string> readLineOfStrings() {
    vector<string> strings;

    string line;
    getline(cin, line);

    istringstream lineIn(line);
    string str;
    while (lineIn >> str) {
        strings.push_back(str);
    }

    return strings;
}

int main() {
    vector<string> columnNames = readLineOfStrings();

    vector<string> objectValues = readLineOfStrings();

    vector<Object> objects;
    while (objectValues[0] != "end") {
        objects.push_back(Object(columnNames, objectValues));

        objectValues = readLineOfStrings();
    }

    string searchColumn = readLineOfStrings()[0];

    unordered_map<string, int> valueOccurrences;
    for (auto o : objects) {
        valueOccurrences[o.get(searchColumn)]++;
    }

    pair<string, int> maxOccurrencesPair("", 0);
    for (auto valueOccurrencesPair : valueOccurrences) {
        if (valueOccurrencesPair.second > maxOccurrencesPair.second) {
            maxOccurrencesPair = valueOccurrencesPair;
        }
    }

    cout << maxOccurrencesPair.first << " " << maxOccurrencesPair.second << endl;

    return 0;
}
