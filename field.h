#ifndef FIELD_H
#define FIELD_H

#include "constants.h"
#include "ship.h"
#include <vector>
#include <utility>

// Класс, представляющий игровое поле
class Field {
public:
    char field[FIELD_SIZE][FIELD_SIZE]; // Двумерный массив клеток поля

    Field();
    void clear(); // Очистка поля
    void display(bool showShips = true); // Отображение поля
    bool placeShipManual(int size); // Ручное размещение корабля
    bool placeShipAuto(int size); // Автоматическое размещение корабля
    bool isValidPosition(int x, int y); // Проверка валидности координат
    bool isStraightAndConnected(const std::vector<std::pair<int, int>>& positions); // Проверка формы корабля
    bool areNeighboursEmpty(const std::vector<std::pair<int, int>>& positions); // Проверка соседних клеток
    bool shootAt(int x, int y); // Выстрел по координатам
    bool allShipsDestroyed(); // Проверка уничтожения всех кораблей
};

#endif
