#include <tuple>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

namespace CSVManager {

    template<typename...Args>
    class CSVParser {
    private:
        std::tuple<Args...> tCurrent;
        std::ifstream &_inputFile;
        size_t sizeOfArgs;
        char _nextLineSymbol;
        int _stringCounter = 1;
        char _nextColumnSymbol;
        char _escapingSymbol;
        bool endOfFile = false;
    protected:

        template<typename T, std::size_t...IndexSeq>
        void checkEach(int i, T &tuple, std::stringstream &str, std::index_sequence<IndexSeq...>) {
            auto setValue = [&i, &str](auto &x, auto indexSeq) {
                if (i == indexSeq) {
                    str >> x;
                }
            };
            (setValue(std::get<IndexSeq>(tuple), IndexSeq), ...);
        }

        void fillValue(size_t i, std::stringstream &str) {
            checkEach(i, tCurrent, str, std::make_index_sequence<sizeof...(Args)>());
        }

    public:
        class Iterator {
        private:
            CSVParser &_date;
            bool _end;
        public:

            explicit Iterator(CSVParser &date, bool endState = false) : _date(date), _end(endState) {}

            ~Iterator() = default;

            bool operator==(Iterator &it) {
                return _end == it._end;
            }

            bool operator!=(Iterator &it) {
                return _end != it._end;
            }

            Iterator &operator++() {
                _date.readString();
                if (_date.endOfFile) _end = true;
                return *this;
            }

            std::tuple<Args...> &operator*() {
                return _date.tCurrent;
            }
        };

        CSVParser(std::ifstream &inputFile, size_t skipLinesCount, char nextLineSymbol = '\n',
                  char nextColumnSymbol = ',', char escapingSymbol = '"') : sizeOfArgs(sizeof...(Args)),
                                                                            _nextColumnSymbol(nextColumnSymbol),
                                                                            _nextLineSymbol(nextLineSymbol),
                                                                            _escapingSymbol(escapingSymbol),
                                                                            _inputFile(inputFile){
            tCurrent = std::make_tuple(Args()...);
            size_t linesCounter = 0;
            char c;
            while (!_inputFile.eof() and linesCounter < skipLinesCount) {
                _inputFile.read(&c, 1);
                if (c == _nextLineSymbol) linesCounter++;
            }
            readString();
        }

        void readString() {
            char c = '\0';
            bool escapingEnable = false;
            int i = 0;
            if (_inputFile.eof()) endOfFile = true;
            else {
                while (i < sizeOfArgs) {
                    std::stringstream str;
                    _inputFile.read(&c, 1);
                    while ((c != _nextLineSymbol or escapingEnable) and (c != _nextColumnSymbol or escapingEnable) and
                           !_inputFile.eof()) {
                        if (c == _escapingSymbol)
                            escapingEnable = true;
                        else {
                            str << c;
                            escapingEnable = false;
                        }
                        _inputFile.read(&c, 1);
                    }

                    if (str.str().empty()) {
                        std::cout << "ERROR: Can't parse data: String " << _stringCounter << ", Arg: " << i
                                  << std::endl;
                        endOfFile = true;
                        return;
                    }
                    fillValue(i, str);
                    str.clear();
                    i++;
                }
                _stringCounter++;
            }
        }

        Iterator begin() { return Iterator(*this); };

        Iterator end() { return Iterator(*this, true); };
    };
};
