#include <iostream>
#include "Letter.h"
#include "CountWords.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "Error: Incorrect arguments" << std::endl;
        return 1;
    }
    std::string input = argv[inputFileNameIdx];
    std::string output = argv[outputFileNameIdx];
    CountWords countWords = CountWords();
    countWords.getCSV(input, output);
    return 0;
}