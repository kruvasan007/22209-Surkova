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
        std::ifstream *_inputFile;
        size_t sizeOfArgs;
        bool endOfFile = false;
    protected:

        template<typename T, std::size_t...IndexSeq>
        void checkEach(int i, T &tuple, std::stringstream &str, std::index_sequence<IndexSeq...>) {
            auto setValue = [&i, &str](auto &x, auto indexSeq) {
                if (i == indexSeq)
                    str >> x;
            };
            (setValue(std::get<IndexSeq>(tuple), IndexSeq), ...);
        }

        void fillValue(size_t i, std::stringstream &str) {
            checkEach(i, tCurrent, str, std::make_index_sequence<sizeof...(Args)>());
        }

    public:
        class Iterator {
        protected:
            CSVParser *_date;
        public:
            explicit Iterator(CSVParser *date) : _date(date) {}

            ~Iterator() = default;

            bool operator==(Iterator &it) {
                return it._date == _date;
            }

            bool operator!=(Iterator &it) {
                return it._date != _date or !_date->endOfFile;
            }

            Iterator &operator++() {
                _date->readString();
                return *this;
            }

            std::tuple<Args...> &operator*() {
                return _date->tCurrent;
            }
        };

        CSVParser(std::ifstream *inputFile, size_t skipLinesCount) : sizeOfArgs(sizeof...(Args)) {
            tCurrent = std::make_tuple(Args()...);
            _inputFile = inputFile;
            size_t linesCounter = 0;
            char c;
            while (!_inputFile->eof() and linesCounter < skipLinesCount) {
                _inputFile->read(&c, 1);
                if (c == '\n') linesCounter++;
            }
            readString();
        }

        void readString() {
            std::vector<std::stringstream> args;
            char c = '\0';
            int i = 0;
            if (_inputFile->eof()) endOfFile = true;
            else {
                while (i < sizeOfArgs) {
                    std::stringstream str;
                    _inputFile->read(&c, 1);
                    while (c != ',' and c != '\n' and !_inputFile->eof()) {
                        str << &c;
                        _inputFile->read(&c, 1);
                    }
                    fillValue(i, str);
                    str.clear();
                    i++;
                }
            }
        }

        Iterator begin() { return Iterator(this); };

        Iterator end() { return Iterator(this); };
    };
};
