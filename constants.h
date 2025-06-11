#ifndef CONSTANTS_H
#define CONSTANTS_H


const int FIELD_SIZE = 10; // Размер игрового поля
const char EMPTY = ' ';    // Пустая клетка
const char SHIP = 's';     // Корабль
const char HIT = 'x';      // Попадание
const char MISS = 'o';     // Промах

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
