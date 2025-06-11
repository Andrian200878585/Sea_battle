#include "game.h"
#include "constants.h"
#include <iostream>
#include <windows.h>

using namespace std;

// Функция отображения главного меню
void showMenu() {
    cout << "-------------------------------------------------------\n";
    cout << "\tМОРСКОЙ БОЙ\n";
    cout << "-------------------------------------------------------\n";
    cout << "\t   МЕНЮ\n";
    cout << "1. Игрок против игрока\n";
    cout << "2. Игрок против компьютера (легкий уровень)\n";
    cout << "3. Игрок против компьютера (сложный уровень)\n";
    cout << "4. Выход\n";
    cout << "Выберите режим игры: ";
}

int main() {
    // Установка русской кодировки
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0)); // Инициализация генератора случайных чисел

    while (true) {
        showMenu();
        int choice;
        cin >> choice;

        if (choice == 4) break;

        GameMode mode;
        Difficulty difficulty;

        // Выбор режима игры
        switch (choice) {
            case 1:
                mode = GameMode::PvP;
                difficulty = Difficulty::Random;
                break;
            case 2:
                mode = GameMode::PvC;
                difficulty = Difficulty::Random;
                break;
            case 3:
                mode = GameMode::PvC;
                difficulty = Difficulty::Smart;
                break;
            default:
                cout << "Неверный выбор!\n";
                continue;
        }

        // Создание и запуск игры
        Game game(mode, difficulty);
        game.setupFields();
        game.play();

        // Предложение сыграть еще
        cout << "\nХотите сыграть еще?\n(1 - Да, 0 - Нет): ";
        cin >> choice;
        if (choice != 1) break;
    }

    return 0;
}
