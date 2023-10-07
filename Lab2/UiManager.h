#pragma once

#include <vector>
#include <memory>
#include "LifeManager.h"
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

    void updateCursor();

    void clearConsole();

    void printHelp();

    void setGameInformation(const std::string &gameName, const std::string &rulesOfGame);

    void printFieldConsole(const FieldManager &fieldManager, size_t iteration);

    void printFieldFile(const FieldManager &fieldManager, size_t iteration, const std::string &fileName);

};
