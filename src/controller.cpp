#include "Controller.h"
#include <iostream>

Controller::Controller(QObject *parent) : QObject(parent), field(), board(field.setField())
{
    setConnections();

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
