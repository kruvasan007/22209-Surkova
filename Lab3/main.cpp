#include "Configurator.h"

int main(int argv, char **argc) {
    std::string configFileName(argc[1]);
    std::string outputFileName(argc[2]);
    std::string input1FileName(argc[3]);
    std::string input2FileName(argc[4]);
    std::vector<std::string> inputStreams;
    inputStreams.push_back(input1FileName);
    inputStreams.push_back(input2FileName);

    auto configurator = new Configurator::Configurator(configFileName, outputFileName, inputStreams);
    configurator->process();
    return 0;
}