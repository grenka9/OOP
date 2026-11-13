Проект Matrix — разделение исходного кода по классам.

Структура:
- main.cpp — точка входа.
- ApplicationManager.h/.cpp — ввод параметров, проверка аргументов и управление программой.
- ConsoleSystem.h/.cpp — функции управления консолью Windows.
- Symbol.h/.cpp — символ и операции его отображения/стирания.
- Line.h/.cpp — логика движения одной линии.

Сборка из корневой папки проекта в MSYS2 UCRT64:
g++ -std=c++17 -Wall -Wextra src/*.cpp -o matrix.exe

Если исходные файлы лежат не в src, а прямо в текущей папке:
g++ -std=c++17 -Wall -Wextra *.cpp -o matrix.exe
