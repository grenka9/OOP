#pragma once

class ConsoleSystem;

// Представляет отдельный символ с заданным цветом.
// Содержит методы для отображения и стирания символа в консоли.
class Symbol {
private:
    // Символ, который будет отображаться в консоли.
    char value;
    // Цвет отображения символа.
    int color;

public:
    // Создает символ с указанным значением и цветом.
    Symbol(char ch, int symbolColor);

    // Отображает символ в заданных координатах консоли.
    void draw(ConsoleSystem& console, int x, int y);
    // Стирает символ, заменяя его пробелом.
    void erase(ConsoleSystem& console, int x, int y);
};
