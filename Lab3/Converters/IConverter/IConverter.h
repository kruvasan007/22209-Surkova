#pragma once

#include <../WAVFileManager/include/WAVHeader.h>
#include <IConverterStruct.h>
#include <fstream>
#include <vector>

namespace Converter {
    using SampleStream = std::vector<std::vector<char>>;

    class IConverter {
    protected:
        size_t secondCounter_ = 0;
        size_t idStream_ = 0;
        size_t startPos_ = 0;
    public:
        virtual ~IConverter() = default;

        virtual void setUp(IConverterStruct iConverterStruct) = 0;

        size_t getStreamId() const {
            return idStream_;
        }

        virtual void convert(SampleStream &sampleStream) = 0;
    };
}
