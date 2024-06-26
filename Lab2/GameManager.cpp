#include <iostream>
#include "GameManager.h"
#include "ParserInputFile.h"

namespace {
    void setInitialBaseParams(GameParams &gameParams) {
        gameParams.BirthdayCellsCount[3] = true;
        gameParams.SurviveCellCount[3] = true;
        gameParams.SurviveCellCount[2] = true;
        gameParams.firstCells = {{0, 2},
                                 {1, 0},
                                 {1, 2},
                                 {2, 1},
                                 {2, 2}};
    }
}

GameManager::GameManager() {
    uiManager = std::make_unique<UiManager>();
    setInitialBaseParams(gameParams);
    uiManager->setGameInformation(gameParams.name, gameParams.rulesOfGame);
    lifeManager = std::make_unique<LifeManager>(gameParams);
}

GameManager::GameManager(const std::string &in, const std::string &out) {
    gameParams.outputFileName = out;
    uiManager = std::make_unique<UiManager>();
    std::unique_ptr<ParserInputFile> parser = std::make_unique<ParserInputFile>();
    if (!parser->readFile(in, gameParams)) return;
    uiManager->setGameInformation(gameParams.name, gameParams.rulesOfGame);
    lifeManager = std::make_unique<LifeManager>(gameParams);
}

void GameManager::startOfflineGame(int i) {
    doIteration(i, GameMode::Offline);
    uiManager->printFieldFile(lifeManager->getField(), lifeManager->getIteration(), gameParams.outputFileName);
}

void GameManager::startGame() {
    uiManager->printFieldConsole(lifeManager->getField(), lifeManager->getIteration());
    std::string instruction;
    int n;
    while (instruction != "exit") {
        uiManager->updateCursor();
        std::cout << "Enter command: " << std::ends;
        std::cin >> instruction;
        std::cout << "" << std::endl;
        if (instruction.find("tick") == 0) {
            std::cin >> n;
            if (n > 0) {
                uiManager->clearConsole();
                if (doIteration(n, GameMode::Online)) {
                    uiManager->printFieldConsole(lifeManager->getField(), lifeManager->getIteration());
                }
            } else
                std::cout << "Error: Incorrect tick number" << std::endl;
        } else if (instruction.find("help") == 0) {
            uiManager->clearConsole();
            uiManager->printHelp();
        } else if (instruction.find("dump") == 0) {
            std::cin >> gameParams.outputFileName;
            uiManager->printFieldFile(lifeManager->getField(), lifeManager->getIteration(), gameParams.outputFileName);
        }
    }
}

bool GameManager::doIteration(int n, GameMode gameMode) {
    for (int i = 0; i < n; ++i) {
        if (!lifeManager->nextIteration()) {
            std::cout << "End the game" << std::endl;
            return true;
        }
        if (gameMode == GameMode::Online)
            uiManager->printFieldConsole(lifeManager->getField(), lifeManager->getIteration());
    }
    return false;
}
