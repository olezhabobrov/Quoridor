#pragma once

#include <QPushButton>
#include <vector>

using std::vector;

struct Cell {
    QPushButton *button = nullptr;
    int x = -1;
    int y = -1;

    Cell(QPushButton *b, int x, int y) : button(b), x(x), y(y){};

    Cell() = default;
};

enum Orientation {
    VERTICAL,
    HORIZONTAL,
    NONE,
};

struct Fence {
    QPushButton *button = nullptr;
    Orientation orient = Orientation::NONE;
    int x = -1;
    int y = -1;

    Fence(QPushButton *b, Orientation o, int x, int y) : button(b), orient(o), x(x), y(y){};

    Fence() = default;
};

struct Board {
    vector<vector<Cell>> cells;
    vector<vector<Fence>> verticalFences;
    vector<vector<Fence>> horizontalFences;
    vector<vector<Fence>> betweenDots;

    Board() : cells(9, vector<Cell> (9)),
        verticalFences(9, vector<Fence>(8)),
        horizontalFences(8, vector<Fence> (9)),
        betweenDots(8, vector<Fence> (8)){};
};
