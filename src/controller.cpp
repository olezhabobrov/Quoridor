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
    if (cell.available) {
        players[currentPlayer].currentPosition.button->setText("");
        clearMove();
        players[currentPlayer].currentPosition = cell;
        cell.button->setText((!currentPlayer ? "O" : "X"));
        nextMove();
    }
}

void Controller::nextMove() {
    currentPlayer ^= 1;
    prepareMove();
}

void Controller::setGame() {
    players.clear();
    players.emplace_back(0, board.cells[8][4]);
    players.emplace_back(1, board.cells[0][4]);
    prepareMove();
}

namespace {
bool sameCells(const Cell &first, const Cell &second) {
    return first.x == second.x && first.y == second.y;
}
}

void Controller::prepareMove() {
    Cell &cell = players[currentPlayer].currentPosition;
    for (auto dir : cell.directions) {
        Cell &cellTemp = board.cells[cell.y + dir.y][cell.x + dir.x];
        if (sameCells(players[currentPlayer ^ 1].currentPosition, cellTemp)){
            if (cellTemp.findDirection(dir) != -1) {
                setAvailable(board.cells[cellTemp.y + dir.y][cellTemp.x + dir.x]);
            } else {
                for (auto dirT : cellTemp.directions) {
                    if (!sameCells(board.cells[cellTemp.y + dirT.y][cellTemp.x + dirT.x], cell)) {
                        setAvailable(board.cells[cellTemp.y + dirT.y][cellTemp.x + dirT.x]);
                    }
                }
            }
        } else{
            setAvailable(cellTemp);
        }
    }
}

void Controller::clearMove() {
    Cell &cell = players[currentPlayer].currentPosition;
    for (Cell &cell : highlightedCells) {
        cell.setUnavailable();
    }
    highlightedCells.clear();
}

void Controller::setAvailable(Cell &cell) {
    highlightedCells.push_back(cell);
    cell.setAvailable();
}


