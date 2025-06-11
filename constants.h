#ifndef CONSTANTS_H
#define CONSTANTS_H

// Размер игрового поля
const int FIELD_SIZE = 10;

// Символы для отображения состояния клеток
const char EMPTY = ' ';    // Пустая клетка
const char SHIP = 's';     // Корабль
const char HIT = 'x';      // Попадание
const char MISS = 'o';     // Промах

// Уровень сложности компьютера
enum class Difficulty {
    Random,  // Случайные ходы
    Smart    // "Умные" ходы с запоминанием попаданий
};

// Режим игры
enum class GameMode {
    PvP,  // Игрок против игрока
    PvC   // Игрок против компьютера
};

#endif
