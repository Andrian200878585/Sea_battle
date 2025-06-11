#include "field.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

// Конструктор поля - инициализация пустыми клетками
Field::Field() {
    clear();
}

// Очистка поля - заполнение пустыми клетками
void Field::clear() {
    for (int i = 0; i < FIELD_SIZE; ++i)
        for (int j = 0; j < FIELD_SIZE; ++j)
            field[i][j] = EMPTY;
}

// Отображение поля в консоли
void Field::display(bool showShips) {
    using namespace std;
    
    cout << "   ";
    for (int i = 0; i < FIELD_SIZE; ++i)
        cout << setw(4) << i;
    cout << "\n";

    for (int i = 0; i < FIELD_SIZE; ++i) {
        cout << setw(2) << i << " ";
        for (int j = 0; j < FIELD_SIZE; ++j) {
            cout << "|";
            // Если не показывать корабли и клетка содержит корабль - показываем пустую
            if (!showShips && field[i][j] == SHIP)
                cout << setw(2) << EMPTY << " ";
            else
                cout << setw(2) << field[i][j] << " ";
        }
        cout << "|\n";

        cout << "   ";
        for (int j = 0; j < FIELD_SIZE; ++j)
            cout << "----";
        cout << "-\n";
    }
}

// Ручное размещение корабля
bool Field::placeShipManual(int size) {
    using namespace std;
    vector<pair<int, int>> positions; // Вектор для хранения координат палуб
    
    cout << "Расставьте корабль из " << size << " палуб:\n";
    for (int i = 0; i < size; ++i) {
        int x, y;
        cout << "Введите координаты " << i + 1 << "-й палубы (вертик. ; горизонт.): ";
        cin >> x >> y;

        if (!isValidPosition(x, y)) {
            cout << "Координаты вне поля!\n";
            return false;
        }
        if (field[x][y] != EMPTY) {
            cout << "!Эта клетка уже занята!\n";
            return false;
        }
        positions.push_back({x, y});
    }

    if (!isStraightAndConnected(positions)) {
        cout << "Корабль должен быть прямым и непрерывным\n";
        return false;
    }

    if (!areNeighboursEmpty(positions)) {
        cout << "Корабли должны находиться на расстоянии минимум 1 клетка\n";
        return false;
    }

    // Размещение корабля на поле
    for (auto p : positions)
        field[p.first][p.second] = SHIP;

    return true;
}

// Автоматическое размещение корабля
bool Field::placeShipAuto(int size) {
    int attempts = 0;
    // Делаем до 100 попыток разместить корабль
    while (attempts++ < 100) {
        int x = rand() % FIELD_SIZE;
        int y = rand() % FIELD_SIZE;
        bool horizontal = rand() % 2; // Случайная ориентация

        vector<pair<int, int>> positions;
        // Генерация всех клеток корабля
        for (int i = 0; i < size; ++i) {
            int nx = horizontal ? x : x + i;
            int ny = horizontal ? y + i : y;

            if (!isValidPosition(nx, ny)) break;
            if (field[nx][ny] != EMPTY) break;

            positions.push_back({nx, ny});
        }

        // Если все клетки валидны и свободны - размещаем
        if (positions.size() == size && isStraightAndConnected(positions) && areNeighboursEmpty(positions)) {
            for (auto p : positions)
                field[p.first][p.second] = SHIP;
            return true;
        }
    }
    return false;
}

// Проверка валидности координат
bool Field::isValidPosition(int x, int y) {
    return x >= 0 && x < FIELD_SIZE && y >= 0 && y < FIELD_SIZE;
}

// Проверка формы корабля
bool Field::isStraightAndConnected(const vector<pair<int, int>>& positions) {
    if (positions.size() <= 1) return true;

    // Определение ориентации по первым двум палубам
    bool horizontal = positions[0].first == positions[1].first;

    for (size_t i = 1; i < positions.size(); ++i) {
        if (horizontal) {
            if (positions[i].first != positions[0].first ||
                positions[i].second != positions[i-1].second + 1)
                return false;
        } else {
            if (positions[i].second != positions[0].second ||
                positions[i].first != positions[i-1].first + 1)
                return false;
        }
    }
    return true;
}

// Проверка соседних клеток
bool Field::areNeighboursEmpty(const vector<pair<int, int>>& positions) {
    for (auto pos : positions) {
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = pos.first + dx;
                int ny = pos.second + dy;
                if (isValidPosition(nx, ny)) {
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

// Выстрел по координатам
bool Field::shootAt(int x, int y) {
    if (!isValidPosition(x, y)) return false;

    if (field[x][y] == SHIP) {
        field[x][y] = HIT;
        return true;
    } else if (field[x][y] == EMPTY) {
        field[x][y] = MISS;
    }
    return false;
}

// Проверка уничтожения всех кораблей
bool Field::allShipsDestroyed() {
    for (int i = 0; i < FIELD_SIZE; ++i)
        for (int j = 0; j < FIELD_SIZE; ++j)
            if (field[i][j] == SHIP)
                return false;
    return true;
}
