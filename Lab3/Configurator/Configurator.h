#pragma once

#include <memory>
#include <WAVHeaderParser.h>
#include <WAVFileManager.h>
#include <WAVFileManager.h>
#include <FactoryCreator.h>
#include <IConverterStruct.h>
#include <IFactory.h>
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

        size_t checkSubStream(ConverterStruct &converters);

        size_t readConfigurationFile(ConverterStruct &converters);

    public:
        Configurator(std::string configFileName, std::string outputFileName,
                     const std::vector<std::string> &inputStreamNames);

        size_t process();
    };
}
