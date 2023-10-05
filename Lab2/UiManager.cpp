#include <iostream>
#include <utility>
#include <fstream>
#include "UiManager.h"

namespace {
    const int DATA_STRING = 4;
    const std::string helpData = "dump <filename> - save universe to file\n tick <n=1> - start doing n nextIteration \n exit - end game\n help - print man";
}

UiManager::UiManager() {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
}

void UiManager::setGameInformation(const std::string &gameName, const std::string &rulesOfGame) {

    name = gameName;
    rules = rulesOfGame;
}

void UiManager::pullConsoleToCommand(size_t size) {
    info.bVisible = TRUE;
    COORD tl = {0, static_cast<SHORT>(DATA_STRING + size)};
    CONSOLE_SCREEN_BUFFER_INFO s;
    GetConsoleScreenBufferInfo(console, &s);
    DWORD cells = s.dwSize.X * s.dwSize.Y;
    DWORD written = cells;
    FillConsoleOutputCharacter(console, ' ', cells, tl, &written);
    SetConsoleCursorInfo(console, &info);
    SetConsoleCursorPosition(console, tl);
}

void UiManager::printHelp() {
    std::cout << helpData << std::endl;
}

void UiManager::resetConsole() {
    COORD tl = {0, 0};
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &info);
    SetConsoleCursorPosition(console, tl);
    Sleep(100);
}

void UiManager::printFieldConsole(const std::vector<CellState> &field, size_t size, size_t iterationCount) {
    resetConsole();
    std::cout << name << " " << rules << std::endl;
    std::cout << "iteration: " << iterationCount << std::endl;
    std::cout << std::string(size + 4, '~') << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << "| " << std::ends;
        for (int j = 0; j < size; ++j) {
            std::cout << (field[i * size + j] == CellState::Alive ? '*' : ' ') << std::ends;
        }
        std::cout << " |" << std::endl;
    }
    std::cout << std::string(size + 4, '~') << std::endl;
}

void UiManager::printFieldFile(const std::vector<CellState> &field, size_t size, size_t iterationCount,
                               const std::string &fileName) {
    std::ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        outputFile << name << " " << rules << "\n";
        outputFile << "nextIteration: " << iterationCount << "\n";
        outputFile << std::string(size + 4, '~') << "\n";
        for (int i = 0; i < size; ++i) {
            outputFile << "| ";
            for (int j = 0; j < size; ++j) {
                outputFile << (field[i * size + j] == CellState::Alive ? '*' : ' ');
            }
            outputFile << " |" << "\n";
        }
        outputFile << std::string(size + 4, '~') << "\n";
    } else {
        std::cout << "Error: File isn't open" << std::endl;
    }
}
