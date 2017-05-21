#ifndef PASTE_TRANSFORM
#define PASTE_TRANSFORM

#include <memory>
#include <string>
#include "TextTransform.h"
#include "CutTransform.h"

class PasteTransform : public TextTransform {
    std::shared_ptr<CutTransform> cutTransform;
public:
    PasteTransform(std::shared_ptr<CutTransform> cutTransform) : cutTransform{cutTransform} {}

    void invokeOn(std::string& text, int startInd, int endInd) override {
        // NOTE: this can be done with indices instead of iterators, but the author wants to show another approach to working with strings
        std::string::iterator startIter = text.begin() + startInd;
        std::string::iterator endIter = text.begin() + endInd;

        text.replace(startIter, endIter, this->cutTransform->getLastCut());
    }
};

#endif // PASTE_TRANSFORM

