#pragma once

#include <IConverterStruct.h>
#include <string>
#include <vector>

namespace Converter {
    using SampleStream = std::vector<std::vector<char>>;

    class IConverter {
    protected:
        size_t secondCounter_ = 0;
        size_t idStream_ = 0;
        size_t startPos_ = 0;

        virtual void setUp(IConverterStruct iConverterStruct) = 0;

    public:
        virtual ~IConverter() = default;

        size_t getStreamId() const {
            return idStream_;
        }

        virtual size_t convert(SampleStream &sampleStream) = 0;

        virtual size_t parseConfigString(std::string str) = 0;
    };
}
