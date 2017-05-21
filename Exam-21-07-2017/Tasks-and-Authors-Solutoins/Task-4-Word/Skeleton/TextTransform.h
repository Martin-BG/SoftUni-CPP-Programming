#ifndef TEXT_TRANSFORM_H
#define TEXT_TRANSFORM_H

#include <string>

class TextTransform {
public:
    virtual void invokeOn(std::string& text, int startIndex, int endIndex) = 0;
	
	virtual ~TextTransform() = default;
};

#endif // TEXT_TRANSFORM_H
