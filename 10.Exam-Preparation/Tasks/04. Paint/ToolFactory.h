#ifndef TOOL_FACTORY_H
#define TOOL_FACTORY_H

#include <string>
#include <memory>

#include "CommonDefinitions.h"

#include "Pencil.h"

class ToolFactory {
public:
    template<typename PixelT> static ToolPtr<PixelT> createTool(std::string toolId) {
        if (toolId == "pencil") {
            return std::make_shared<Pencil<PixelT> >();
        }

        return nullptr;
    }
};

#endif // TOOL_FACTORY_H
