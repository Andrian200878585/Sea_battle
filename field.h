#pragma once
#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>
#include "constants.h"

class Field {
public:// Определяет уровень видимости членов класса для других частей программы
    char field[FIELD_SIZE][FIELD_SIZE]; // Двумерный массив для хранения состояния клеток

    Field();
    void clear();
    void display(bool showShips = true);// Выводит текущее состояние поля в консоль
    // Параметр showShips определяет, показывать ли корабли (true) или скрывать их (false)

    bool placeShipManual(int size);
    bool placeShipAuto(int size);          // Возвращают true, если размещение прошло успешно
    bool isValidPosition(int x, int y);// Проверяет, находятся ли координаты в пределах игрового поля
    bool isStraightAndConnected(const std::vector<std::pair<int, int>>& positions);// Проверяет, образуют ли заданные позиции прямой и непрерывный корабль
    // positions - вектор координат палуб корабля
    bool areNeighboursEmpty(const std::vector<std::pair<int, int>>& positions); // Используется для соблюдения правила, что корабли не должны касаться друг друга
    bool shootAt(int x, int y);// Возвращает true, если было попадание в корабль
    bool allShipsDestroyed();// Возвращает true, если не осталось ни одной неподбитой палубы
};
