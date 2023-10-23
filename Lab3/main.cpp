#include "Configurator.h"

const std::string HELP_STRING = "Type of converter:\n \tmix - Two parameters: an additional stream and the insertion location (in seconds, 0 by default). Output stream: Each sample is the average of the corresponding samples of the input streams. The length of the output stream corresponds to the length of the main input stream. If the additional stream is longer than the main one, then part of it is cut off (not used), and if it is shorter, then the output stream outside it is equal to the main input stream. \n"
                                "\tmute - Two parameters: the beginning and the end of the time interval (in seconds). There is silence in the output stream in this time interval, the rest is like in the input stream.\n"
                                "\tflex - Two parameters: duration of mix two streams and additional stream";

int main(int argv, char **argc) {
    if (argv == 2) {
        if (argc[1][1] == 'h') {
            std::cout << HELP_STRING << std::endl;
        } else {
            Error::printError(Error::ERROR_PARSE_ARGUMENTS, Error::CODE_ERROR_PARSE_ARGUMENTS);
        }
    } else if (argv >= 4) {
        std::string configFileName(argc[1]);
        std::string outputFileName(argc[2]);
        std::vector<std::string> inputStreams;
        for (int i = 3; i < argv; ++i) {
            std::string inputFileName(argc[i]);
            inputStreams.push_back(inputFileName);
        }
        auto configurator = new Configurator::Configurator(configFileName, outputFileName, inputStreams);
        configurator->process();
    } else {
        Error::printError(Error::ERROR_PARSE_ARGUMENTS, Error::CODE_ERROR_PARSE_ARGUMENTS);
    }
    return 0;
}