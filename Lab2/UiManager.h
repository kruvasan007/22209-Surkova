#pragma once

#include <vector>
#include <Windows.h>

const int DATA_STRING = 4;
const std::string helpData = "dump <filename> - save universe to file\n tick <n=1> - start doing n iteration \n exit - end game\n help - print man";

class UiManager {
private:
    HANDLE console;
    CONSOLE_CURSOR_INFO info;
    std::string name;
    std::string rules;

    void resetConsole();

public:

    void pullConsoleToCommand(int size);

    UiManager();

    void printHelp();

    void setPrintData(std::string n, std::string r);

    void printFieldConsole(std::vector<std::vector<bool>> field, int size, int iterationCount);

    void printFieldFile(std::vector<std::vector<bool>> field, int size, int iterationCount, const std::string& fileName);

};
