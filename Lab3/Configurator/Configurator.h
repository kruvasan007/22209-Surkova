#pragma once

#include <memory>
#include <WAVHeaderParser.h>
#include <ReaderConfigFile.h>
#include <WAVFileManager.h>
#include <WAVFileManager.h>
#include <FactoryCreator.h>
#include <IConverterStruct.h>
#include <Config.h>

namespace Configurator {
    using ConverterStruct = std::vector<Converter::IConverterPtr>;

    class Configurator {
    private:
        std::string configFileName_;
        std::string outputFileName_;
        std::vector<std::string> inputStreamNames_;
        std::unique_ptr<WAVHeaderParser> wavHeaderParser;
        std::unique_ptr<WAVFManager::WAVFileManager> wavFileManager;
        std::shared_ptr<Factory::IFactory> factory;
        std::vector<Config> convertConfigurations;
    public:
        Configurator(std::string configFileName, std::string inputFileName,
                     const std::vector<std::string> &outputStreamName);

        size_t generateConverters(ConverterStruct &converters);

        void process();
    };
}
