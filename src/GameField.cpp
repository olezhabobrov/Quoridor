#include <cassert>
#include "GameField.h"
#include "ui_GameField.h"

GameField::GameField(QWidget *parent) : QDialog(parent), ui(new Ui::GameField)
{
    ui->setupUi(this);
    setConnections();
}

GameField::~GameField() {
    delete ui;
}

void GameField::setConnections() {
//    connect(ui->reset, &QPushButton::clicked, [=] { emit newGame(); });
    connect(ui->menu, &QPushButton::clicked, [=] { close(); });
}

Board GameField::setField() {
    Board board;
    std::vector<Cell> cellsRow;
    ui->Board->setHorizontalSpacing(0);
    ui->Board->setVerticalSpacing(0);
    for (int h = 0; h < 17; h++) {
        for (int w = 0; w < 17; w++) {
            QPushButton *button = new QPushButton();
            button->setStyleSheet("background-color: lightgrey");


            // board cell
            if (h % 2 == 0 && w % 2 == 0) {
                assert(h / 2 < 9 && w / 2 < 9);
                button->setFixedSize(40, 40);
                board.cells[h / 2][w / 2] = Cell(button, w / 2, h / 2);
            }

            // verical fence
            if (h % 2 == 0 && w % 2 == 1) {
                assert(h / 2 < 9 && w / 2 < 8);
                button->setFixedSize(15, 40);
                board.verticalFences[h / 2][w / 2] = Fence(button, Orientation::VERTICAL, w / 2, h / 2);
            }

            // horizontal fence
            if (h % 2 == 1 && w % 2 == 0) {
                assert(h / 2 < 8 && w / 2 < 9);
                button->setFixedSize(40, 15);
                board.horizontalFences[h / 2][w / 2] = Fence(button, Orientation::HORIZONTAL, w / 2, h / 2);
            }

            // between fence
            if (h % 2 == 1 && w % 2 == 1) {
                assert(h / 2 < 8 && w / 2 < 8);
                button->setFixedSize(15, 15);
                button->setVisible(false);
                board.betweenDots[h / 2][w / 2] = Fence(button, Orientation::NONE, w / 2, h / 2);
                //                button->setStyleSheet("background-color: red");
            }


            ui->Board->addWidget(button, h, w);
        }
    }
    board.cells[0][4].button->setText("X");
    board.cells[8][4].button->setText("O");

    return board;
}


void GameField::placeFence()
{

}

