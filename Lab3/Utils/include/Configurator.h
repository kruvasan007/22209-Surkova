#pragma once

#include <memory>
#include <WAVStreamWriter.h>
#include <WAVStreamReader.h>
#include <WAVStreamReader.h>
#include <FactoryCreator.h>
#include <IFactory.h>
#include <ConvertersAliasNames.h>

namespace Configurator {
    using ConverterStruct = std::vector<Converter::IConverterPtr>;

    class Configurator {
    private:
        std::string configFileName_;
        std::string outputFileName_;
        std::vector<std::string> inputStreamNames_;
        std::unique_ptr<WAVHeaderParser> wavHeaderParser;
        std::unique_ptr<WAVFManager::WAVStreamWriter> wavStreamWriter;
        std::shared_ptr<Converter::StreamReader>  wavStreamReader;
        std::shared_ptr<Factory::IFactory> factory;

        size_t readConfigurationFile(ConverterStruct &converters);

    public:
        Configurator(std::string configFileName, std::string outputFileName,
                     const std::vector<std::string> &inputStreamNames);

        size_t process();
    };
}
