#pragma once


#include <cstddef>
namespace Converter {
    struct IConverterStruct {
        size_t idStream;
        size_t startPos;
        size_t endPos;
        size_t duration;
    };
}
