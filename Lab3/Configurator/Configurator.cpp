#include "Configurator.h"
#include "FactoryItems.h"
#include "IConverter.h"
#include "../Errors.h"
#include <utility>

namespace Configurator {

    const size_t MAX_COUNT_STREAMS = 2;

    Configurator::Configurator(std::string configFileName, std::string outputFileName,
                               const std::vector<std::string> &inputStreamNames) {
        configFileName_ = std::move(configFileName);
        outputFileName_ = std::move(outputFileName);
        inputStreamNames_ = inputStreamNames;
    }

    size_t Configurator::readConfigurationFile(ConverterStruct &converters) {
        std::ifstream configFile(configFileName_);
        std::string line;
        size_t curPosition;
        while (std::getline(configFile, line)) {
            curPosition = 0;
            if (line[curPosition] == '#')
                continue;
            else if (line.find("mix") != -1) {
                Converter::IConverterPtr converter = factory->create(Converter::mixConverterTag);
                if (converter->parseConfigString(line)) return Error::CODE_ERROR_PARSE_ARGUMENTS;
                converters.push_back(converter);
            } else if (line.find("mute") != -1) {
                Converter::IConverterPtr converter = factory->create(Converter::muteConverterTag);
                if (converter->parseConfigString(line)) return Error::CODE_ERROR_PARSE_ARGUMENTS;
                converters.push_back(converter);
            } else if (line.find("flex") != -1) {
                Converter::IConverterPtr converter = factory->create(Converter::flexConverterTag);
                if (converter->parseConfigString(line)) return Error::CODE_ERROR_PARSE_ARGUMENTS;
                converters.push_back(converter);
            }
        }
        return 0;
    }

    size_t Configurator::checkSubStream(ConverterStruct &converters) {
        for (const auto &converter: converters) {
            if (converter->getStreamId() != 0) {
                if (wavHeaderParser->getWAVHeader(converter->getStreamId()).byteRate !=
                    wavHeaderParser->getWAVHeader(0).byteRate) {
                    return Error::printError(Error::ERROR_CONVERTER, Error::CODE_ERROR_CONVERTER);
                }
                wavFileManager->openSubSample(inputStreamNames_[converter->getStreamId()],
                                              wavHeaderParser->getWAVHeader(
                                                      converter->getStreamId()).dataPosition);
            }
        }
        return 0;
    }

    size_t Configurator::process() {
        size_t err;

        wavHeaderParser = std::make_unique<WAVHeaderParser>();
        wavHeaderParser->parseFileHeader(inputStreamNames_[0]);
        Factory::FactoryMap factoryMap = Converter::getFactoryItemsMap();
        factory = Factory::createFactory(factoryMap);

        wavFileManager = std::make_unique<WAVFManager::WAVFileManager>(inputStreamNames_[0], outputFileName_);
        wavFileManager->writeHeader(wavHeaderParser->getWAVHeader(0));

        Converter::SampleStream stream(MAX_COUNT_STREAMS);
        for (int i = 0; i < MAX_COUNT_STREAMS; ++i) {
            if ((err = wavHeaderParser->parseFileHeader(inputStreamNames_[i])))
                return err;
            stream[i].resize(wavHeaderParser->getWAVHeader(i).byteRate);
        }
        ConverterStruct converters;
        if ((err = readConfigurationFile(converters))) return err;
        if (checkSubStream(converters)) return Error::CODE_ERROR_CONVERTER;
        while (!wavFileManager->readSample(stream[0])) {
            for (const auto &converter: converters) {
                if (converter->getStreamId()) {
                    wavFileManager->readSubSample(stream[converter->getStreamId()]);
                }
                if ((err = converter->convert(stream))) return err;
            }
            wavFileManager->writeSample(stream[0]);
        }
        return 0;
    }
}