#include "field.h"
#include "constants.h"
#include <iostream>
#include <cstdlib>

Field::Field() {
    clear(); // Инициализация поля пустыми клетками
}

void Field::clear() {
    for (int i = 0; i < FIELD_SIZE; ++i)
        for (int j = 0; j < FIELD_SIZE; ++j)
            field[i][j] = EMPTY;
}

void Field::display(bool showShips) {
    std::cout << "   ";
    for (int i = 0; i < FIELD_SIZE; ++i)
        std::cout << std::setw(4) << i;
    std::cout << "\n";

    // Вывод каждой строки поля
    for (int i = 0; i < FIELD_SIZE; ++i) {
        std::cout << std::setw(2) << i << " ";
        for (int j = 0; j < FIELD_SIZE; ++j) {
            std::cout << "|";
            // Если не показывать корабли и клетка содержит корабль - показывать пустую
            if (!showShips && field[i][j] == SHIP)
                std::cout << std::setw(2) << EMPTY << " ";
            else
                std::cout << std::setw(2) << field[i][j] << " ";
        }
        std::cout << "|\n";

        std::cout << "   ";
        for (int j = 0; j < FIELD_SIZE; ++j)
            std::cout << "----";
        std::cout << "-\n";
    }
}

bool Field::placeShipManual(int size) {
    std::vector<std::pair<int, int>> positions; // Вектор для хранения координат палуб
    std::cout << "Расставьте корабль из " << size << " палуб:\n";
    for (int i = 0; i < size; ++i) {
        int x, y;
        std::cout << "Введите координаты " << i + 1 << "-й палубы (вертик. ; горизонт.): ";
        std::cin >> x >> y;

        if (!isValidPosition(x, y)) {
            std::cout << "Координаты вне поля!\n";
            return false;
        }
        if (field[x][y] != EMPTY) {
            std::cout << "!Эта клетка уже занята!\n";
            return false;
        }
        positions.push_back({ x, y });
    }

    if (!isStraightAndConnected(positions)) {
        std::cout << "Корабль должен быть прямым и непрерывным\n";
        return false;
    }

    if (!areNeighboursEmpty(positions)) {
        std::cout << "Корабли должны находиться на расстоянии минимум 1 клетка\n";
        return false;
    }

    // Размещение корабля на поле
    for (auto p : positions)
        field[p.first][p.second] = SHIP;

    return true;
}

bool Field::placeShipAuto(int size) {
    int attempts = 0;
    // Делаем до 100 попыток разместить корабль
    while (attempts++ < 100) {
        int x = rand() % FIELD_SIZE;
        int y = rand() % FIELD_SIZE;
        bool horizontal = rand() % 2; // Случайная ориентация (горизонтальная/вертикальная)

        std::vector<std::pair<int, int>> positions;
        // Генерация всех клеток корабля
        for (int i = 0; i < size; ++i) {
            int nx = horizontal ? x : x + i;
            int ny = horizontal ? y + i : y;

            if (!isValidPosition(nx, ny)) break;
            if (field[nx][ny] != EMPTY) break;

            positions.push_back({ nx, ny });
        }

        // Если все клетки корабля валидны и свободны то размещаем
        if (positions.size() == size && isStraightAndConnected(positions) && areNeighboursEmpty(positions)) {
            for (auto p : positions)
                field[p.first][p.second] = SHIP;
            return true;
        }
    }
    return false;
}

bool Field::isValidPosition(int x, int y) {
    return x >= 0 && x < FIELD_SIZE && y >= 0 && y < FIELD_SIZE;
}

bool Field::isStraightAndConnected(const std::vector<std::pair<int, int>>& positions) {
    if (positions.size() <= 1) return true; // Корабль из 1 палубы всегда валиден

    // Определение ориентации корабля (по первым двум палубам)
    bool horizontal = positions[0].first == positions[1].first;

    // Проверка всех последующих палуб
    for (size_t i = 1; i < positions.size(); ++i) {
        if (horizontal) {
            // Для горизонтального корабля x должен быть одинаковым, а y увеличиваться на 1
            if (positions[i].first != positions[0].first ||
                positions[i].second != positions[i - 1].second + 1)
                return false;
        }
        else {
            // Для вертикального корабля y должен быть одинаковым, а x увеличиваться на 1
            if (positions[i].second != positions[0].second ||
                positions[i].first != positions[i - 1].first + 1)
                return false;
        }
    }
    return true;
}

bool Field::areNeighboursEmpty(const std::vector<std::pair<int, int>>& positions) {
    for (auto pos : positions) {
        // Проверка всех 8 соседних клеток
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = pos.first + dx;
                int ny = pos.second + dy;
                if (isValidPosition(nx, ny)) {
                    // Если в соседней клетке корабль, и это не часть текущего корабля - ошибка
                    if (field[nx][ny] == SHIP) {
                        bool isPartOfShip = false;
                        for (auto p : positions) {
                            if (p.first == nx && p.second == ny) {
                                isPartOfShip = true;
                                break;
                            }
                        }
                        if (!isPartOfShip) return false;
                    }
                }
            }
        }
    }
    return true;
}

bool Field::shootAt(int x, int y) {
    if (!isValidPosition(x, y)) return false;

    if (field[x][y] == SHIP) { // Попадание в корабль
        field[x][y] = HIT;
        return true;
    }
    else if (field[x][y] == EMPTY) { // Промах
        field[x][y] = MISS;
    }
    return false;
}

bool Field::allShipsDestroyed() {
    for (int i = 0; i < FIELD_SIZE; ++i)
        for (int j = 0; j < FIELD_SIZE; ++j)
            if (field[i][j] == SHIP) // Если найден хотя бы один непораженный корабль
                return false;
    return true;
}
