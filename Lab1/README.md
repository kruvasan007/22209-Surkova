# LAB1 Реализация класса BitArray
## Инструкции сборки
```
cmake .
make
```
## Инструкция проверки покрытия кода
```
./Lab1 #запускаем тесты
lcov -c --directory ./CMakeFiles/Lab1.dir/ --output-file coverage.info
genhtml coverage.info #в index.html отчёт
```
## Функционал
Методы реализованы в соотвествии с заданием.
Использовались компоненты из стандартной библиотеки и библиотека математики: vector, cmath
