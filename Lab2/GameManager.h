#pragma once

#include <string>
#include <fstream>
#include "LifeManager.h"
#include "UiManager.h"
#include "FileData.h"

const int SIZE_POS = 3;
const int NAME_POS = 3;

class GameManager {
private:
    std::string outputFileName;
    FileData fileData;
    std::unique_ptr <LifeManager> lifeManager;
    std::unique_ptr <UiManager> uiManager;

    void parseString(std::string basicString);

    bool readFile(std::string fName);

    bool readRule(std::string basicString);

    bool readSize(std::string basicString);

    bool doIteration(int stoi);

    int toInt(char c);

    std::pair<int, int> getCoords(std::string basicString);

public:
    GameManager(std::string &in, std::string &out);

    GameManager();

    void startGame();

    void startOfflineGame(int i);
};
