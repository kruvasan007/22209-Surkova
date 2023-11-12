#pragma once

#include <cstddef>
#include <vector>

namespace Converter {
    struct IConverterStruct {
        std::vector<size_t> idStreams;
        size_t startPos;
        size_t endPos;
        size_t duration;
    };
}
