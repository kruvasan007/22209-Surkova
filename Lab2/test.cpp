#include <gtest/gtest.h>
#include "GameManager.h"
#include "googletest/googlemock/include/gmock/gmock.h"
#include "googletest/googletest/include/gtest/gtest.h"

struct MyClassTest : public testing::Test {
    GameManager *gameManager;
    std::string inputName = "input.txt";
    std::string outputName = "output.txt";

    void SetUp() {
        gameManager = new GameManager(inputName, outputName);
    }

    void TearDown() {
        delete gameManager;
    }
};

TEST_F(MyClassTest, Subtest_offlineGame) {
    gameManager->startOfflineGame(1000);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
