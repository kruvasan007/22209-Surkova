#include <iostream>
#include "Letter.h"
#include "CountWords.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "Error: Incorrect arguments" << endl;
        return 1;
    }
    string input = argv[INPUT_FILE_NAME];
    string output = argv[OUTPUT_FILE_NAME];
    CountWords countWords = CountWords();
    countWords.getCSV(input, output);
    return 0;
}
