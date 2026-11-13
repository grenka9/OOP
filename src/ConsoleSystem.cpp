#include "ConsoleSystem.h"

ConsoleSystem::ConsoleSystem() {
    output = GetStdHandle(STD_OUTPUT_HANDLE);
}

void ConsoleSystem::hideCursor() {
    CONSOLE_CURSOR_INFO info{};
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(output, &info);
}

void ConsoleSystem::showCursor() {
    CONSOLE_CURSOR_INFO info{};
    info.dwSize = 20;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(output, &info);
}

void ConsoleSystem::moveCursor(int x, int y) {
    COORD pos{
        static_cast<SHORT>(x),
        static_cast<SHORT>(y)
    };
    SetConsoleCursorPosition(output, pos);
}

void ConsoleSystem::setColor(int color) {
    SetConsoleTextAttribute(output, static_cast<WORD>(color));
}

void ConsoleSystem::clearScreen() {
    CONSOLE_SCREEN_BUFFER_INFO info{};
    GetConsoleScreenBufferInfo(output, &info);

    DWORD cells =
        static_cast<DWORD>(info.dwSize.X) *
        static_cast<DWORD>(info.dwSize.Y);

    DWORD written = 0;
    COORD start{0, 0};

    FillConsoleOutputCharacterA(output, ' ', cells, start, &written);
    FillConsoleOutputAttribute(output, 7, cells, start, &written);
    moveCursor(0, 0);
}

int ConsoleSystem::getWidth() {
    CONSOLE_SCREEN_BUFFER_INFO info{};
    GetConsoleScreenBufferInfo(output, &info);
    return info.srWindow.Right - info.srWindow.Left + 1;
}

int ConsoleSystem::getHeight() {
    CONSOLE_SCREEN_BUFFER_INFO info{};
    GetConsoleScreenBufferInfo(output, &info);
    return info.srWindow.Bottom - info.srWindow.Top + 1;
}
