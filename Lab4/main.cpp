#include <iostream>
#include <CSVParser.h>
#include <tuple>

template<class Ch, class Tr, class... Args>
auto &operator<<(std::basic_ostream<Ch, Tr> &os, std::tuple<Args...> const &t) {
    std::apply([&os](auto &&... args) { ((os << args << " "), ...); }, t);
    return os;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;
    std::ifstream file(argv[1]);
    CSVManager::CSVParser<int, std::string, std::string> parser(file, 0);
    for (const auto &ps: parser) {
        std::cout << ps << std::endl;
    }
    return 0;
}