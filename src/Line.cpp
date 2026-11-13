#include "Line.h"
#include "ConsoleSystem.h"
#include "Symbol.h"

#include <conio.h>
#include <chrono>
#include <string>
#include <thread>
#include <random>

namespace {
    // Определяет, получает ли каждый символ линии собственный случайный цвет.
    constexpr bool COLOR_PER_SYMBOL = true;
}

int Line::randomColor() {
    std::uniform_int_distribution<int> dist(1, 15);
    return dist(generator);
}

char Line::randomSymbol() {
    static const std::string symbols =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "!@#$%^&*";

    std::uniform_int_distribution<std::size_t> dist(
        0, symbols.size() - 1
    );

    return symbols[dist(generator)];
}

Line::Line(int positionX, int lineLength, int lineSpeed,
           bool epilepsy, std::mt19937& rng)
    : x(positionX),
      length(lineLength),
      speed(lineSpeed),
      lineColor(10),
      epilepsyMode(epilepsy),
      generator(rng) {
    if (epilepsyMode && !COLOR_PER_SYMBOL) {
        lineColor = randomColor();
    }
}

bool Line::crawl(ConsoleSystem& console) {
    const int height = console.getHeight();
    const int delay = 1000 / speed;

    for (int y = height - 1;
         y >= -(length - 1);
         --y) {

        if (_kbhit()) {
            int key = _getch();
            if (key == 27) {
                return false;
            }
        }

        if (y >= 0 && y < height) {
            int color = 10;

            if (epilepsyMode) {
                color = COLOR_PER_SYMBOL
                    ? randomColor()
                    : lineColor;
            }

            Symbol symbol(randomSymbol(), color);
            symbol.draw(console, x, y);
        }

        int tailY = y + length;
        if (tailY >= 0 && tailY < height) {
            Symbol blank(' ', 7);
            blank.erase(console, x, tailY);
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(delay)
        );
    }

    
    for (int clearY = 0; clearY < length; ++clearY) {
        Symbol blank(' ', 7);
        blank.erase(console, x, clearY);
    }

    return true;
}
