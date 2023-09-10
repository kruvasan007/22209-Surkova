#include <string>

void toLower(std::string &word) {
    for (char &c: word)
        c = std::tolower(static_cast<unsigned char>(c));
}

bool isLetter(unsigned char symbol) {
    return (symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z') || (symbol >= '0' && symbol <= '9');
}
