#include "Symbol.h"
#include "ConsoleSystem.h"
#include <iostream>

Symbol::Symbol(char ch, int symbolColor)
    : value(ch), color(symbolColor) {
}

void Symbol::draw(ConsoleSystem& console, int x, int y) {
    console.moveCursor(x, y);
    console.setColor(color);
    std::cout << value << std::flush;
}

void Symbol::erase(ConsoleSystem& console, int x, int y) {
    console.moveCursor(x, y);
    std::cout << ' ' << std::flush;
}
