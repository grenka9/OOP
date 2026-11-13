#include "ApplicationManager.h"
#include "Line.h"

#include <algorithm>
#include <cctype>
#include <conio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <random>

namespace {
    // Задает минимальную и максимальную допустимую скорость линии (символов в секунду).
    constexpr int MIN_SPEED = 1;
    constexpr int MAX_SPEED = 30;
    // Задает минимальную и максимальную допустимую длину линии (в символах).
    constexpr int MIN_LENGTH = 1;
    constexpr int MAX_LENGTH = 30;
}

bool ApplicationManager::parseNumber(const std::string& text, int& result) {
    std::stringstream stream(text);
    char extra;

    if (!(stream >> result)) {
        return false;
    }

    if (stream >> extra) {
        return false;
    }

    return true;
}

int ApplicationManager::readNumber(
    const std::string& prompt, int minValue, int maxValue
) {
    while (true) {
        std::cout << prompt;

        std::string input;
        std::getline(std::cin, input);

        int value;
        if (parseNumber(input, value) &&
            value >= minValue && value <= maxValue) {
            return value;
        }

        std::cout << "Ошибка! Введите целое число от "
                  << minValue << " до " << maxValue << ".\n";
    }
}

bool ApplicationManager::readEpilepsyMode() {
    while (true) {
        std::cout << "Режим эпилепсии (Y/N): ";

        std::string input;
        std::getline(std::cin, input);

        if (input.size() == 1) {
            char answer = static_cast<char>(
                std::toupper(static_cast<unsigned char>(input[0]))
            );

            if (answer == 'Y') return true;
            if (answer == 'N') return false;
        }

        std::cout << "Ошибка! Введите Y или N.\n";
    }
}

void ApplicationManager::interactiveInput() {
    std::cout << "=== Матрица ===\n";

    speed = readNumber(
        "Скорость (1-30 символов/сек): ",
        MIN_SPEED, MAX_SPEED
    );

    length = readNumber(
        "Длина линии (1-30 символов): ",
        MIN_LENGTH, MAX_LENGTH
    );

    epilepsyMode = readEpilepsyMode();
}

bool ApplicationManager::parseArguments(int argc, char* argv[]) {
    if (argc == 1) {
        interactiveInput();
        return true;
    }

    if (argc == 2) {
        std::string arg = argv[1];
        if (arg == "--help" || arg == "/?") {
            printHelp();
            return false;
        }
    }

    if (argc != 4) {
        std::cerr << "Ошибка: неверное число аргументов.\n";
        printHelp();
        return false;
    }

    if (!parseNumber(argv[1], speed) ||
        speed < MIN_SPEED || speed > MAX_SPEED) {
        std::cerr << "Ошибка: скорость должна быть от 1 до 30.\n";
        return false;
    }

    if (!parseNumber(argv[2], length) ||
        length < MIN_LENGTH || length > MAX_LENGTH) {
        std::cerr << "Ошибка: длина должна быть от 1 до 30.\n";
        return false;
    }

    std::string mode = argv[3];
    if (mode.size() != 1) {
        std::cerr << "Ошибка: режим должен быть Y или N.\n";
        return false;
    }

    char answer = static_cast<char>(
        std::toupper(static_cast<unsigned char>(mode[0]))
    );

    if (answer != 'Y' && answer != 'N') {
        std::cerr << "Ошибка: режим должен быть Y или N.\n";
        return false;
    }

    epilepsyMode = (answer == 'Y');
    return true;
}

void ApplicationManager::printHelp() {
    std::cout
        << "Использование:\n"
        << "  matrix.exe\n"
        << "  matrix.exe <скорость> <длина> <Y/N>\n"
        << "  matrix.exe --help\n"
        << "  matrix.exe /?\n\n"
        << "Скорость: от 1 до 30 символов в секунду.\n"
        << "Длина: от 1 до 30 символов.\n"
        << "Y — включить режим эпилепсии, N — выключить.\n"
        << "Во время анимации нажмите Esc для выхода.\n";
}

int ApplicationManager::run(int argc, char* argv[]) {
    if (!parseArguments(argc, argv)) {
        if (argc == 2 &&
            (std::string(argv[1]) == "--help" ||
             std::string(argv[1]) == "/?")) {
            return 0;
        }
        return 1;
    }

    console.clearScreen();
    console.hideCursor();

    std::uniform_int_distribution<int> xDistribution(
        0, std::max(0, console.getWidth() - 1)
    );

    while (true) {
        int x = xDistribution(generator);

        Line line(x, length, speed, epilepsyMode, generator);

        if (!line.crawl(console)) {
            break;
        }

        if (_kbhit()) {
            int key = _getch();
            if (key == 27) break;
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(100)
        );
    }

    console.setColor(7);
    console.showCursor();
    console.clearScreen();
    std::cout << "Программа завершена.\n";

    return 0;
}
