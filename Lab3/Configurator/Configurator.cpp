#include "Configurator.h"
#include "FactoryItems.h"
#include "IConverter.h"
#include "ReaderConfigFile.h"
#include <iostream>
#include <utility>

namespace Configurator {

    const size_t MAX_COUNT_STREAMS = 2;

    Configurator::Configurator(std::string configFileName, std::string outputFileName,
                               const std::vector<std::string> &inputStreamNames) {
        configFileName_ = std::move(configFileName);
        outputFileName_ = std::move(outputFileName);
        inputStreamNames_ = inputStreamNames;
    }

    size_t Configurator::generateConverters(ConverterStruct &converters) {
        for (const auto &config: convertConfigurations) {
            Converter::IConverterPtr converter = factory->create(config.tag);
            converter->setUp(config.iConverterStruct);
            converters.push_back(converter);
            if (config.iConverterStruct.idStream != 0) {
                if (wavHeaderParser->getWAVHeader(config.iConverterStruct.idStream).byteRate !=
                    wavHeaderParser->getWAVHeader(0).byteRate) {
                    return Error::printError(
                            Error::ErrorContainer(Error::ERROR_CONVERTER, Error::CODE_ERROR_CONVERTER));
                }
                wavFileManager->openSubSample(inputStreamNames_[config.iConverterStruct.idStream],
                                              wavHeaderParser->getWAVHeader(
                                                      config.iConverterStruct.idStream).dataPosition);
            }
        }
        return 0;
    }

    void Configurator::process() {
        if (readConfigurationFile(configFileName_, convertConfigurations)) return;

        wavHeaderParser = std::make_unique<WAVHeaderParser>();
        wavHeaderParser->parseFileHeader(inputStreamNames_[0]);
        Factory::FactoryMap factoryMap = Converter::getFactoryItemsMap();
        factory = Factory::createFactory(factoryMap);

        wavFileManager = std::make_unique<WAVFManager::WAVFileManager>(inputStreamNames_[0], outputFileName_);
        wavFileManager->writeHeader(wavHeaderParser->getWAVHeader(0));

        Converter::SampleStream stream(MAX_COUNT_STREAMS);
        for (int i = 0; i < MAX_COUNT_STREAMS; ++i) {
            wavHeaderParser->parseFileHeader(inputStreamNames_[i]);
            stream[i].resize(wavHeaderParser->getWAVHeader(i).byteRate);
        }

        ConverterStruct converters;
        generateConverters(converters);
        while (!wavFileManager->readSample(stream[0])) {
            for (const auto &converter: converters) {
                if (converter->getStreamId()) {
                    wavFileManager->readSubSample(stream[converter->getStreamId()]);
                }
                converter->convert(stream);
            }
            wavFileManager->writeSample(stream[0]);
        }
    }
}