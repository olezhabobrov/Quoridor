#include "Controller.h"
#include <iostream>

Controller::Controller(QObject *parent) : QObject(parent), field(), board(field.setField())
{
    setConnections();
    setGame();

    field.exec();

}

void Controller::setConnections() {
    for (auto& cellRow: board.cells) {
        for (auto& cell : cellRow){
            connect(cell.button, &QPushButton::clicked, [&](){
                cellClicked(cell);
            });
        }
    }
}

void Controller::cellClicked(Cell &cell) {
    std::cout << "x=" << cell.x << "    y=" << cell.y << std::endl;
}

void Controller::setGame() {
    players.clear();
    players.emplace_back(0, board.cells[8][4]);
    players.emplace_back(1, board.cells[0][4]);
    prepareMove();
}

void Controller::prepareMove() {
    Cell &cell = players[currentPlayer].currentPosition;
    for (auto dir : cell.directions) {
        board.cells[cell.y + dir.y][cell.x + dir.x].setAvailable();
    }
}
