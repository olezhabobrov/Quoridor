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

std::vector<Cell> GameField::setField() {
    std::vector<Cell> cells;
    ui->Board->setHorizontalSpacing(0);
    ui->Board->setVerticalSpacing(0);
    for (int h = 0; h < 17; h++) {
        for (int w = 0; w < 17; w++) {
            QPushButton *button = new QPushButton();
            int x = 0;
            int y = 0;
            if (h % 2 && w % 2) {;
//                button->setStyleSheet("background-color: red");
                button->setVisible(false);
            }
            if (h % 2 == 0) {
                y = 40;
            } else {
                y = 15;
            }
            if (w % 2 == 0) {
                x = 40;
            } else {
                x = 15;
            }
            if (h == 0 && w == 8) {
                button->setText("O");
            }
            if (h == 16 && w == 8) {
                button->setText("X");
            }
            button->setFixedSize(x, y);

            ui->Board->addWidget(button, h, w);
            cells.emplace_back(button, w, h);
        }
    }
    return cells;
}


void GameField::placeFence()
{

}

