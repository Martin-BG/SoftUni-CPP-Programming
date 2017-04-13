#include<string>
#include<sstream>
#include<vector>
#include<iostream>

class SmartString : public std::string {
public:
    SmartString(const std::string& s) :
        std::string(s) {
    }

    SmartString(const char* cstring) :
        std::string(cstring) {
    }

    // calls default ctor of std::string, as well as the words field (std::vector)
    SmartString() {
    }

    int getWordCount() {
        return getWords(*this).size();
    }

    std::string getWord(int index) {
        return getWords(*this).at(index);
    }

    void changeWord(int index, std::string substitute) {
        std::string word = getWord(index);

        this->replace(this->find(word), word.size(), substitute);
    }
private:
    std::vector<std::string> getWords(const std::string &s) {
        std::istringstream stream(s);

        std::vector<std::string> words;

        std::string word;
        while(stream >> word) {
            words.push_back(word);
        }

        return words;
    }
};

int main() {
    // NOTE: this works thanks to the constructor we declared that accepts a const char *
    SmartString s = "the quick brown fox jumps over the lazy dog";

    std::cout << s.getWordCount() << std::endl;

    s.changeWord(3, "kitten");

    std::cout << s << std::endl;

    // NOTE: this works, because it calls std::string operator+=(const char*)
    s += "... or does it?";

    // NOTE: this works, because the const char* is implicitly convertible to std::string, then the result of the
    // operation is an std::string, which is implicitly convertible to SmartString
    s = (s + " yep, it does.");

    std::cout << s << std::endl;

    return 0;
}
