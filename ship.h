#pragma once
#include <vector>
#include <utility> // для std::pair (шаблон класса в стандартной библиотеке C++, который представляет пару значений. 
//Два элемента пары могут быть разных типов.)

struct Ship {
    int size; // Количество палуб
    std::vector<std::pair<int, int>> coordinates; // Координаты всех палуб корабля
};
