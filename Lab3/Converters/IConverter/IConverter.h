#pragma once

#include "StreamReader.h"
#include <string>
#include <memory>
#include <vector>

namespace Converter {
    using SampleStream = std::vector<std::vector<char>>;

    struct IConverterStruct {
        std::vector<size_t> idStreams;
        size_t startPos;
        size_t endPos;
        size_t duration;
    };

    class IConverter {
    protected:
        size_t secondCounter_ = 0;
        std::vector<size_t> idStream_;
        size_t startPos_ = 0;

        virtual void setUp(IConverterStruct iConverterStruct) = 0;

    public:
        virtual ~IConverter() = default;

        virtual size_t convert(std::vector<char> &stream, std::shared_ptr<StreamReader> &streamReader) = 0;

        virtual size_t parseConfigString(std::string str) = 0;
    };
}
