#include "GameManager.h"
#include "LifeManager.h"
#include "UiManager.h"
#include "FileData.h"

GameManager::GameManager() {
    fileData.name = "Standard game";
    uiManager = new UiManager();
    fileData.size = 10;
    uiManager->setPrintData(fileData.name, "#R B3/S23");
    fileData.Bs = {3};
    fileData.Ss = {2, 3};
    lifeManager = new LifeManager(fileData.Bs, fileData.Ss, fileData.size);
    fileData.coords = {{0, 2},
                       {1, 0},
                       {1, 2},
                       {2, 1},
                       {2, 2}};
    for (std::pair<int, int> item: fileData.coords)
        lifeManager->setAlive(item.first, item.second);
}

GameManager::GameManager(std::string &in, std::string &out) {
    outputFileName = out;
    uiManager = new UiManager();
    readFile(in);
    lifeManager = new LifeManager(fileData.Bs, fileData.Ss, fileData.size);
    for (std::pair<int, int> item: fileData.coords)
        lifeManager->setAlive(item.first, item.second);
}

bool GameManager::readFile(std::string fName) {
    std::ifstream inputFile(fName);
    if (!inputFile.is_open()) {
        std::cout << "Error: File isn't open" << std::endl;
        return false;
    }
    std::string currentString;
    while (getline(inputFile, currentString))
        parseString(currentString);
    return true;
}

void GameManager::startGame() {
    uiManager->printFieldConsole(lifeManager->getField(), lifeManager->getFieldSize(), lifeManager->getIteration());
    std::string instruction;
    int n;
    while (instruction != "exit") {
        uiManager->pullConsoleToCommand(lifeManager->getFieldSize());
        std::cout << "Enter command: " << std::ends;
        std::cin >> instruction;
        std::cout << "" << std::endl;
        if (instruction.find("tick") == 0) {
            std::cin >> n;
            if (n != 0) {
                if (doIteration(n)) {
                    uiManager->printFieldConsole(lifeManager->getField(), lifeManager->getFieldSize(),
                                                 lifeManager->getIteration());
                }
            } else
                std::cout << "Error: Incorrect tick number" << std::endl;
        } else if (instruction.find("help") == 0) {
            uiManager->printHelp();
            uiManager->pullConsoleToCommand(lifeManager->getFieldSize());
        } else if (instruction.find("dump") == 0) {
            uiManager->printFieldFile(lifeManager->getField(), lifeManager->getFieldSize(), lifeManager->getIteration(),
                                      outputFileName);
        }
    }
}

void GameManager::parseString(std::string str) {
    char firstSymbol = str[0];
    if (firstSymbol == '#') {
        char modification = str[1];
        if (modification == 'N') {
            fileData.name = str.substr(NAME_POS, str.length());
        } else if (modification == 'R') {
            uiManager->setPrintData(fileData.name, str);
            readRule(str);
        } else if (modification == 'S') {
            readSize(str);
        } else {
            return;
        }
    } else if ('9' >= firstSymbol and firstSymbol >= '0') {
        fileData.coords.push_back(getCoords(str));
    }
}

bool GameManager::readSize(std::string str) {
    int lastPos = SIZE_POS, pos = SIZE_POS;
    while (str[pos] != '\n' && pos < str.length()) {
        pos++;
    }
    fileData.size = std::stoi(str.substr(lastPos, pos - lastPos));
    return true;
}

bool GameManager::readRule(std::string str) {
    int pos = 1;
    while (str[pos] != 'B' && pos < str.length())
        pos++;
    if (pos == str.length()) {
        std::cout << "Error: No rules. Use standart" << std::endl;
        return false;
    }
    pos++;
    while (str[pos] != '/') {
        if ('9' >= str[pos] and str[pos] >= '0')
            fileData.Bs.push_back(toInt(str[pos]));
        else {
            std::cout << "Error: Wrong rules number" << std::endl;
            return false;
        }
        pos++;
    }
    while (str[pos] != 'S' && pos < str.length())
        pos++;
    pos++;
    while (pos < str.length()) {
        if ('9' >= str[pos] and str[pos] >= '0')
            fileData.Ss.push_back(toInt(str[pos]));
        else {
            std::cout << "Error: Wrong rules number" << std::endl;
            return false;
        }
        pos++;
    }
    return true;
}

int GameManager::toInt(char c) {
    return c - '0';
}

std::pair<int, int> GameManager::getCoords(std::string str) {
    int lastPos = 0, pos = 1;
    int count = 0;
    std::pair<int, int> crds;
    while (pos <= str.length()) {
        if (str[pos] == ' ' && count == 0) {
            crds.first = std::stoi(str.substr(lastPos, pos - lastPos));
            lastPos = pos + 1;
            count++;
        } else if (str[pos] == ' ' or str[pos] == '\n' or pos == str.length()) {
            crds.second = std::stoi(str.substr(lastPos, pos - lastPos));
            break;
        }
        pos++;
    }
    return crds;
}

bool GameManager::doIteration(int n) {
    uiManager->pullConsoleToCommand(lifeManager->getFieldSize());
    for (int i = 0; i < n; ++i) {
        if (!lifeManager->iteration()) {
            std::cout << "End the game" << std::endl;
            return true;
        }
        uiManager->printFieldConsole(lifeManager->getField(), lifeManager->getFieldSize(), lifeManager->getIteration());
    }
    return false;
}
