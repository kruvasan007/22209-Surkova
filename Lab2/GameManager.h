#pragma once

#include <string>
#include "LifeManager.h"
#include "UiManager.h"
#include "GameParams.h"
#include "ParserInputFile.h"
#include "Coords.h"
#include <memory>

enum class GameMode {
    Offline,
    Online,
};

class GameManager {
private:
    GameParams gameParams;
    std::unique_ptr<LifeManager> lifeManager;
    std::unique_ptr<UiManager> uiManager;

    bool doIteration(int stoi, GameMode gameMode);

public:
    GameManager(const std::string &in, const std::string &out);

    GameManager();

    void startGame();

    void startOfflineGame(int i);
};
