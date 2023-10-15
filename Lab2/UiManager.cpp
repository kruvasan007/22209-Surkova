#include <iostream>
#include <fstream>
#include "UiManager.h"

namespace {
    const std::string helpData = "dump <filename> - save universe to file\n tick <n=1> - start doing n nextIteration \n exit - end game\n help - print man";
}

UiManager::UiManager() {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
}

void UiManager::setGameInformation(const std::string &gameName, const std::string &rulesOfGame) {
    name = gameName;
    rules = rulesOfGame;
}

void UiManager::clearConsole() {
    COORD clearCrds = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    GetConsoleScreenBufferInfo(console, &s);
    DWORD cells = s.dwSize.X * s.dwSize.Y;
    DWORD written = cells;
    FillConsoleOutputCharacter(console, ' ', cells, clearCrds, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, clearCrds, &written);
}

void UiManager::updateCursor() {
    info.bVisible = TRUE;
    SetConsoleCursorInfo(console, &info);
}

void UiManager::resetConsole() {
    COORD tl = {0, 0};
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &info);
    SetConsoleCursorPosition(console, tl);
    Sleep(100);
}

void UiManager::printHelp() {
    resetConsole();
    std::cout << helpData << std::endl;
}

void UiManager::printFieldConsole(const FieldManager &fieldManager, size_t iteration) {
    resetConsole();
    size_t size = fieldManager.getSize();
    std::cout << name << " " << rules << std::endl;
    std::cout << "iteration: " << iteration << std::endl;
    std::cout << std::string(size + 4, '~') << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << "| " << std::ends;
        for (int j = 0; j < size; ++j) {
            std::cout << (fieldManager.isCellAlive(i, j) ? '*' : ' ') << std::ends;
        }
        std::cout << " |" << std::endl;
    }
    std::cout << std::string(size + 4, '~') << std::endl;
}

void UiManager::printFieldFile(const FieldManager &fieldManager, size_t iteration, const std::string &fileName) {
    std::ofstream outputFile(fileName);
    size_t size = fieldManager.getSize();
    if (outputFile.is_open()) {
        outputFile << name << " " << rules << "\n";
        outputFile << "nextIteration: " << iteration << "\n";
        outputFile << std::string(size + 4, '~') << "\n";
        for (int i = 0; i < size; ++i) {
            outputFile << "| ";
            for (int j = 0; j < size; ++j) {
                outputFile << (fieldManager.isCellAlive(i, j) ? '*' : ' ');
            }
            outputFile << " |" << "\n";
        }
        outputFile << std::string(size + 4, '~') << "\n";
    } else {
        std::cout << "Error: File isn't open" << std::endl;
    }
}
