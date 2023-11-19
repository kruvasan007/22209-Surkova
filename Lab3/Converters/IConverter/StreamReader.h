#pragma once

#include <vector>

namespace Converter {
    class StreamReader {
    public:
        virtual ~StreamReader() = default;

        virtual std::vector<char> getStream(std::size_t idx) = 0;
    };
}
