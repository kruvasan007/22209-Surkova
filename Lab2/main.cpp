#include <iostream>
#include "GameManager.h"

int main(int argc, char **argv) {
    if (argc == 1) {
        GameManager gameManager = GameManager();
        gameManager.startGame();
    } else if (argc == 3) {
        std::string input = argv[1];
        std::string output = argv[2];
        GameManager gameManager = GameManager(input, output);
        gameManager.startGame();
    } else {
        std::cout << "Error: incorrect input. Expected 3 arguments" << std::endl;
        return 1;
    }
}
