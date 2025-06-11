#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <utility> // для std::pair

struct Ship {
    int size; // Размер корабля (количество палуб)
    std::vector<std::pair<int, int>> coordinates; // Координаты всех палуб корабля
};

#endif
