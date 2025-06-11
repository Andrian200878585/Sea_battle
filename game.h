#ifndef GAME_H
#define GAME_H

#include "field.h"
#include "constants.h"
#include <vector>
#include <string>

// Класс, управляющий игровым процессом
class Game {
private:
    GameMode mode;          // Режим игры
    Difficulty difficulty;  // Уровень сложности
    Field player1Field;     // Поле первого игрока
    Field player2Field;     // Поле второго игрока/компьютера
    bool player1Turn;       // Чей сейчас ход
    std::vector<std::pair<int, int>> computerHits; // История попаданий компьютера

public:
    Game(GameMode m, Difficulty d);
    void setupFields();               // Настройка полей
    void setupPlayerField(Field& field); // Настройка поля игрока
    void setupComputerField();        // Настройка поля компьютера
    void play();                      // Основной игровой цикл
    void playerTurn(const std::string& playerName, Field& playerField, Field& opponentField); // Ход игрока
    void computerTurn();              // Ход компьютера
    void clearScreen();               // Очистка экрана
    void waitForEnter();              // Ожидание нажатия Enter
};

#endif // GAME_H
