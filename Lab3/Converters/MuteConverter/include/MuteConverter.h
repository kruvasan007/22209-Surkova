#pragma once

#include <IConverter.h>
#include <string>
#include <memory>

namespace Converter {
    class MuteConverter : public IConverter {
    private:
        size_t endPos_ = 0;

        void setUp(IConverterStruct iConverterStruct) override;

    public:
        size_t parseConfigString(std::string str) override;

        size_t
        convert(std::vector<char> &stream, std::shared_ptr<StreamReader> &streamReader) override;

    };
}