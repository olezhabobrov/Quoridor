#include "OtherTypes.h"

Cell::Cell(QPushButton *b, int x, int y) : button(b), x(x), y(y){
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

int Cell::findDirection(Direction direct) {
    for (std::size_t i = 0; i < directions.size(); ++i) {
        if (direct.x == directions[i].x && direct.y == directions[i].y) {
            return i;
        }
    }
    return -1;
}

void Cell::deleteDirection(Direction direct) {
    int pos = findDirection(direct);
    if (pos != -1) {
        directions.erase(directions.begin() + pos);
    }
}

void Cell::setAvailable() {
    available = true;
    button->setStyleSheet("background-color: green");
}

void Cell::setUnavailable() {
    available = false;
    button->setStyleSheet("background-color: lightgrey");
}

void Cell::setPlayerMark(bool player) {
    if (player) {
        button->setStyleSheet("font-size: 25px;"
                              "font: bold;"
                              "background-color: lightgrey");
        button->setText("X");
    } else {
        button->setStyleSheet("color: red;"
                              "font-size: 25px;"
                              "font: bold;"
                              "background-color: lightgrey");
        button->setText("O");
    }
}

void Fence::setMarked(bool show) {
    marked = true;
    if (show){
        button->setVisible(true);
        button->setStyleSheet("background-color: blue");
    }
}

Fence::Fence(QPushButton *b, Orientation o, int x, int y) : button(b), orient(o), x(x), y(y){};

Board::Board() : cells(9, vector<Cell> (9)),
          verticalFences(9, vector<Fence>(8)),
          horizontalFences(8, vector<Fence> (9)),
          betweenDots(8, vector<Fence> (8)){};