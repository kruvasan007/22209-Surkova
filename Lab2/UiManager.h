#pragma once

#include <vector>
#include "FieldManager.h"
#include <Windows.h>

class UiManager {
private:
    HANDLE console;
    CONSOLE_CURSOR_INFO info;
    std::string name;
    std::string rules;

    void resetConsole();

public:

    UiManager();

    void pullConsoleToCommand(size_t size);

    void printHelp();

    void setGameInformation(const std::string &gameName, const std::string &rulesOfGame);

    void printFieldConsole(const std::vector<CellState> &field, size_t size, size_t iterationCount);

    void
    printFieldFile(const std::vector<CellState> &field, size_t size, size_t iterationCount,
                   const std::string &fileName);

};
