#pragma once

#include <QPushButton>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>

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

    Cell(QPushButton *b, int x, int y) : button(b), x(x), y(y){
        if (x == 0) {
            deleteDirection(Direction(-1, 0));
        }
        if (x == 8) {
            deleteDirection(Direction(1, 0));
        }
        if (y == 0) {
            deleteDirection(Direction(0, -1));
        }
        if (y == 8) {
            deleteDirection(Direction(0, 1));
        }
    };

    int findDirection(Direction direct) {
        for (std::size_t i = 0; i < directions.size(); ++i) {
            if (direct.x == directions[i].x && direct.y == directions[i].y) {
                return i;
            }
        }
        return -1;
    }

    void deleteDirection(Direction direct) {
        int pos = findDirection(direct);
        if (pos != -1) {
            directions.erase(directions.begin() + pos);
        }
    }

    void setAvailable() {
        available = true;
        button->setStyleSheet("background-color: green");
    }

    void setUnavailable() {
        available = false;
        button->setStyleSheet("background-color: lightgrey");
    }

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

    void setMarked() {
        marked = true;
        button->setVisible(true);
        button->setStyleSheet("background-color: blue");
    }

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
