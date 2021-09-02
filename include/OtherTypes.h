#pragma once

#include <QPushButton>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

using std::vector;

struct Direction {
    int x = 0;
    int y = 0;

    Direction(int x, int y) : x(x), y(y){};
};

struct Cell {
    QPushButton *button = nullptr;
    int x = -1;
    int y = -1;
    bool available = false;

    vector<Direction> directions = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};

    Cell(QPushButton *b, int x, int y);

    int findDirection(Direction direct);

    void deleteDirection(Direction direct);

    void setAvailable();

    void setUnavailable();

    void setPlayerMark(bool player);

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
    bool available = false;
    bool marked = false;

    void setMarked(bool show);

    Fence(QPushButton *b, Orientation o, int x, int y);

    Fence() = default;
};

struct Player {
    bool id = 0;
    int fenceCount = 10;
    Cell *currentPosition;

    Player(bool id, Cell *c) : id(id), currentPosition(c){};
};

struct Board {
    bool currentPlayer = 0;
    vector<Player> players;
    vector<vector<Cell>> cells;
    vector<vector<Fence>> verticalFences;
    vector<vector<Fence>> horizontalFences;
    vector<vector<Fence>> betweenDots;

    Board();
};
