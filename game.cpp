#include "game.h"
#include <iostream>
#include <conio.h>
#include <limits>
#include <windows.h>
#include <cstdlib>
#include <ctime>

// Убираем конфликтующий макрос max из Windows.h
#undef max

using namespace std;

// Конструктор игры
Game::Game(GameMode m, Difficulty d) : mode(m), difficulty(d), player1Turn(true) {} //mode(m)	m (аргумент)	Устанавливает режим игры (PvP или PvC).
//difficulty(d)	d(аргумент)	Устанавливает сложность компьютера(Random или Smart).
//player1Turn(true)	true	Указывает, что первый ход принадлежит игроку 1.


void Game::setupFields() {
    cout << "\nНастройка поля для Игрока 1:\n";
    setupPlayerField(player1Field);

    if (mode == GameMode::PvP) {
        clearScreen();
        cout << "Настройка поля для Игрока 2:\n";
        setupPlayerField(player2Field);
    }
    else {
        setupComputerField();
    }
}

void Game::setupPlayerField(Field& field) {
    cout << "Как вы хотите расставить корабли?\n(1 - автоматически, 2 - вручную): ";
    int choice;
    cin >> choice;

    vector<int> shipSizes = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

    if (choice == 1) {
        // Автоматическая расстановка
        for (int size : shipSizes) {
            while (!field.placeShipAuto(size)) {}
        }
    }
    else {
        // Ручная расстановка
        for (int size : shipSizes) {
            bool placed = false;
            while (!placed) {
                field.display();
                placed = field.placeShipManual(size);
            }
        }
    }
}

// Настройка поля компьютера
void Game::setupComputerField() {
    vector<int> shipSizes = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    for (int size : shipSizes) {
        while (!player2Field.placeShipAuto(size)) {}
    }
}

// Основной игровой цикл
void Game::play() {
    while (true) {
        clearScreen();
        if (player1Turn) {
            playerTurn("Игрок 1", player1Field, player2Field);
            if (player2Field.allShipsDestroyed()) {
                cout << "Игрок 1 победил!\n";
                break;
            }
        }
        else {
            if (mode == GameMode::PvP) {
                playerTurn("Игрок 2", player2Field, player1Field);
                if (player1Field.allShipsDestroyed()) {
                    cout << "Игрок 2 победил!\n";
                    break;
                }
            }
            else {
                computerTurn();
                if (player1Field.allShipsDestroyed()) {
                    cout << "Компьютер победил!\n";
                    break;
                }
            }
        }
        player1Turn = !player1Turn;
        waitForEnter();
    }
}

// Ход игрока
void Game::playerTurn(const string& playerName, Field& playerField, Field& opponentField) {
    cout << playerName << ", ваш ход:\n";
    cout << "Ваше поле:\n";
    playerField.display();
    cout << "\nПоле противника:\n";
    opponentField.display(false); // Не показывать корабли противника

    int x, y;
    do {
        cout << "Введите координаты выстрела (вертик. ; горизонт.): ";
        cin >> x >> y;
    } while (!opponentField.isValidPosition(x, y) ||
        opponentField.field[x][y] == HIT ||
        opponentField.field[x][y] == MISS);

    bool hit = opponentField.shootAt(x, y);
    cout << (hit ? "Попадание!" : "Промах!") << endl;
}

// Ход компьютера
void Game::computerTurn() {
    cout << "Ход компьютера...\n";
    int x, y;

    if (difficulty == Difficulty::Random || computerHits.empty()) {
        // Случайные ходы
        do {
            x = rand() % FIELD_SIZE;
            y = rand() % FIELD_SIZE;
        } while (player1Field.field[x][y] == HIT || player1Field.field[x][y] == MISS);
    }
    else {
        // Умная стратегия
        pair<int, int> lastHit = computerHits.back();
        vector<pair<int, int>> possibleTargets;

        // Проверка соседних клеток
        int dirs[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        for (auto& dir : dirs) {
            int nx = lastHit.first + dir[0];
            int ny = lastHit.second + dir[1];
            if (player1Field.isValidPosition(nx, ny) &&
                player1Field.field[nx][ny] != HIT &&
                player1Field.field[nx][ny] != MISS) {
                possibleTargets.push_back({ nx, ny });
            }
        }

        if (!possibleTargets.empty()) {
            auto target = possibleTargets[rand() % possibleTargets.size()];
            x = target.first;
            y = target.second;
        }
        else {
            computerHits.clear();
            computerTurn();
            return;
        }
    }

    cout << "Компьютер стреляет в (" << x << ", " << y << ")\n";
    bool hit = player1Field.shootAt(x, y);
    cout << (hit ? "Попадание!" : "Промах!") << endl;

    if (hit) {
        computerHits.push_back({ x, y });
    }
}

// Очистка экрана
void Game::clearScreen() {
    system("cls");
}

void Game::waitForEnter() {
    if (mode == GameMode::PvP) {
        cout << "\nНажмите Enter, чтобы передать ход следующему игроку";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}
