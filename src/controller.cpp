#include "Controller.h"
#include <iostream>

Controller::Controller(QObject *parent) : QObject(parent), field(), cells(field.setField())
{
    setConnections();

    field.exec();

}

void Controller::setConnections() {
    for (Cell& cell: cells) {
        connect(cell.button, &QPushButton::clicked, [&](){
            cellClicked(cell);
        });
    }
}

void Controller::cellClicked(Cell &cell) {
    std::cout << "x=" << cell.x << "    y=" << cell.y << std::endl;
}
