#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

class Object {
private:
    unordered_map<string, string> properties;
public:
    Object() {
    }

    Object(string objectString) {
        istringstream objectStringIn(objectString);

        string name;
        string value;
        while (objectStringIn >> name >> value) {
            this->properties[name] = value;
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

int main() {
    string index;
    getline(cin, index);

    unordered_map<string, vector<Object> > objectsByIndex;

    ostringstream output;

    string line;
    getline(cin, line);
    while(line != "[queries]") {
        Object o(line);

        if (o.has(index)) {
            objectsByIndex[o.get(index)].push_back(o);
        }

        getline(cin, line);
    }

    getline(cin, line);
    while(line != "end") {
        istringstream lineIn(line);
        string indexQuery, property;
        lineIn >> indexQuery >> property;

        auto objectsEntryIter = objectsByIndex.find(indexQuery);
        if (objectsEntryIter != objectsByIndex.end()) {
            for(Object o : objectsEntryIter->second) {
                if (o.has(property)) {
                    output << o.get(property) << " ";
                }
            }
            output << endl;
        } else {
            output << "[not found]" << endl;;
        }

        getline(cin, line);
    }

    cout << output.str();

    return 0;
}
