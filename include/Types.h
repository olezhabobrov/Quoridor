#pragma once

#include <QPushButton>

struct Cell {
    QPushButton *button = nullptr;
    int x = -1;
    int y = -1;

    Cell(QPushButton *b, int x, int y) : button(b), x(x), y(y){};
};
