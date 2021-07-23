#include "GameField.h"
#include "ui_GameField.h"

GameField::GameField(QWidget *parent) : QDialog(parent), ui(new Ui::GameField)
{
    ui->setupUi(this);
    setConnections();
    setField();
}

GameField::~GameField() {
    delete ui;
}

void GameField::setConnections() {
//    connect(ui->reset, &QPushButton::clicked, [=] { emit newGame(); });
    connect(ui->menu, &QPushButton::clicked, [=] { close(); });
}

void GameField::setField() {
    ui->Board->setHorizontalSpacing(0);
    ui->Board->setVerticalSpacing(0);
    for (int h = 0; h < 9; h++) {
        for (int w = 0; w < 9; w++) {
            QPushButton *button = new QPushButton();
            button->setFixedSize(40, 40);
            ui->Board->addWidget(button, h, w);
        }
    }

}


void GameField::placeFence()
{

}

