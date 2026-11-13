#include "ApplicationManager.h"

#include <windows.h>
#include <clocale>

// Главная функция программы.
// Настраивает кодировку консоли, создает менеджер приложения и запускает программу.
int main(int argc, char* argv[]) {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    std::setlocale(LC_ALL, ".UTF-8");

    ApplicationManager app;
    return app.run(argc, argv);
}
