#include <ReaderConfigFile.h>

namespace Configurator {
    size_t readConfigurationFile(const std::string &fileName, std::vector<Config> &configurations) {
        std::ifstream configFile(fileName);
        std::string line;
        size_t curPosition;
        while (std::getline(configFile, line)) {
            curPosition = 0;
            if (line[curPosition] == '#')
                continue;
            else if ((curPosition = line.find("mix")) != -1) {
                Config config;
                size_t input2;
                if (line[curPosition + 4] == '$') {
                    curPosition += 5;
                    input2 = line[curPosition] - '0';
                } else
                    return Error::printError(Error::ERROR_PARSE_CONFIG, Error::CODE_ERROR_PARSE_CONFIG);
                curPosition += 2;
                size_t lastPos = curPosition;
                while (line[curPosition] != '\n' && curPosition < line.size())
                    curPosition++;
                config.tag = Converter::mixConverterTag;
                config.iConverterStruct.startPos = std::stoi(line.substr(lastPos, curPosition - lastPos));
                config.iConverterStruct.idStream = input2 - 1;
                configurations.push_back(config);
            } else if ((curPosition = line.find("mute")) != -1) {
                Config config;
                curPosition += 5;
                size_t lastPos = curPosition;
                if (line[curPosition] >= '0' and line[curPosition] <= '9') {
                    while (line[curPosition] != ' ' && curPosition < line.size())
                        curPosition++;
                    config.iConverterStruct.startPos = std::stoi(line.substr(lastPos, curPosition - lastPos));
                } else
                    return Error::printError(Error::ERROR_PARSE_CONFIG, Error::CODE_ERROR_PARSE_CONFIG);
                curPosition++;
                lastPos = curPosition;
                if (line[curPosition] >= '0' and line[curPosition] <= '9') {
                    while (line[curPosition] != ' ' && curPosition < line.size())
                        curPosition++;
                    if (curPosition == lastPos) return 1;
                    config.iConverterStruct.endPos = std::stoi(line.substr(lastPos, curPosition - lastPos));
                } else
                    return Error::printError(Error::ERROR_PARSE_CONFIG, Error::CODE_ERROR_PARSE_CONFIG);
                config.tag = Converter::muteConverterTag;
                configurations.push_back(config);
            } else if ((curPosition = line.find("flex")) != -1) {
                Config config;
                curPosition += 5;
                size_t lastPos = curPosition;
                if (line[curPosition] >= '0' and line[curPosition] <= '9') {
                    while (line[curPosition] != ' ' && curPosition < line.size())
                        curPosition++;
                    config.iConverterStruct.duration = std::stoi(line.substr(lastPos, curPosition - lastPos));
                } else
                    return Error::printError(Error::ERROR_PARSE_CONFIG, Error::CODE_ERROR_PARSE_CONFIG);
                config.tag = Converter::flexConverterTag;
                configurations.push_back(config);
            } else
                return Error::printError(Error::ERROR_PARSE_CONFIG, Error::CODE_ERROR_PARSE_CONFIG);
        }
        return 0;
    }
}