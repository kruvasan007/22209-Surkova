#include "Configurator.h"
#include "FactoryItems.h"
#include "IConverter.h"
#include "../Errors.h"
#include <utility>

namespace Configurator {
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

    size_t Configurator::process() {
        size_t err;

        wavHeaderParser = std::make_unique<WAVHeaderParser>();
        Factory::FactoryMap factoryMap = Converter::getFactoryItemsMap();
        factory = Factory::createFactory(factoryMap);

        for (auto &inputStreamName: inputStreamNames_) {
            if ((err = wavHeaderParser->parseFileHeader(inputStreamName)))
                return err;
        }

        wavStreamWriter = std::make_unique<WAVFManager::WAVStreamWriter>(outputFileName_);
        auto reader = std::make_shared<WAVFManager::WAVStreamReader>(inputStreamNames_,
                                                                     wavHeaderParser);
        wavStreamReader = std::dynamic_pointer_cast<Converter::StreamReader>(reader);
        wavStreamWriter->writeHeader(wavHeaderParser->getWAVHeader(0));

        ConverterStruct converters;
        std::vector<char> stream(wavHeaderParser->getWAVHeader(0).byteRate);
        if ((err = readConfigurationFile(converters))) return err;
        while (!(stream = wavStreamReader->getStream(0)).empty()) {
            for (const auto &converter: converters) {
                if ((err = converter->convert(stream, wavStreamReader))) return err;
            }
            wavStreamWriter->writeSample(stream);
        }
        return 0;
    }
}