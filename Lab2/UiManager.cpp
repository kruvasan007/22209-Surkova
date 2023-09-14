#include <iostream>
#include <utility>
#include <fstream>
#include "UiManager.h"

UiManager::UiManager() {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
}

void UiManager::setPrintData(std::string n, std::string r) {
    name = std::move(n);
    rules = std::move(r);
}

void UiManager::pullConsoleToCommand(int size) {
    info.bVisible = TRUE;
    COORD tl = {0, static_cast<SHORT>(DATA_STRING + size)};
    CONSOLE_SCREEN_BUFFER_INFO s;
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
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

void UiManager::printFieldConsole(std::vector<std::vector<bool>> field, int size, int iterationCount) {
    resetConsole();
    std::cout << name << " " << rules << std::endl;
    std::cout << "iteration: " << iterationCount << std::endl;
    std::cout << std::string(size + 4, '~') << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << "| " << std::ends;
        for (int j = 0; j < size; ++j) {
            std::cout << (field[i][j] ? '*' : ' ') << std::ends;
        }
        std::cout << " |" << std::endl;
    }
    std::cout << std::string(size + 4, '~') << std::endl;
}

void UiManager::printFieldFile(std::vector<std::vector<bool>> field, int size, int iterationCount,
                               const std::string &fileName) {
    std::ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        outputFile << name << " " << rules << "\n";
        outputFile << "iteration: " << iterationCount << "\n";
        outputFile << std::string(size + 4, '~') << "\n";
        for (int i = 0; i < size; ++i) {
            outputFile << "| ";
            for (int j = 0; j < size; ++j) {
                outputFile << (field[i][j] ? '*' : ' ');
            }
            outputFile << " |" << "\n";
        }
        outputFile << std::string(size + 4, '~') << "\n";
    } else {
        std::cout << "Error: File isn't open" << std::endl;
    }
}
