#include <cassert>
#include "GameField.h"
#include "ui_GameField.h"

GameField::GameField(QWidget *parent) : QDialog(parent), ui(new Ui::GameField)
{
    ui->setupUi(this);
    setStyle();
    setConnections();
}

GameField::~GameField() {
    delete ui;
}

void GameField::setStyle() {
    ui->menu->setStyleSheet("font-size: 20px;"
                            "font-weight: bold;");
}

void GameField::setConnections() {
    connect(ui->menu, &QPushButton::clicked, [=] { close(); });
}

void GameField::setPlayerMove(bool player) {
    if (!player){
        ui->PlayerOBox->setStyleSheet(QStringLiteral("QGroupBox{"
                                                 "font-size: 16px;"
                                                 "font-weight: bold;"
                                                 "border:5px solid lightgreen;"
                                                 "border-radius:5px;"
                                                 "margin-top: 1ex;}"
                                                 "QGroupBox::title{"
                                                 "subcontrol-origin: margin;"
                                                 "subcontrol-position:top center;"
                                                 "padding:0 3px;}"));
        ui->PlayerXBox->setStyleSheet(QStringLiteral("QGroupBox{"
                                                 "font-size: 16px;"
                                                 "font-weight: bold;"
                                                 "border:5px solid lightgray;"
                                                 "border-radius:5px;"
                                                 "margin-top: 1ex;}"
                                                 "QGroupBox::title{"
                                                 "subcontrol-origin: margin;"
                                                 "subcontrol-position:top center;"
                                                 "padding:0 3px;}"));
    } else {
        ui->PlayerXBox->setStyleSheet(QStringLiteral("QGroupBox{"
                                                     "font-size: 16px;"
                                                     "font-weight: bold;"
                                                     "border:5px solid lightgreen;"
                                                     "border-radius:5px;"
                                                     "margin-top: 1ex;}"
                                                     "QGroupBox::title{"
                                                     "subcontrol-origin: margin;"
                                                     "subcontrol-position:top center;"
                                                     "padding:0 3px;}"));
        ui->PlayerOBox->setStyleSheet(QStringLiteral("QGroupBox{"
                                                     "font-size: 16px;"
                                                     "font-weight: bold;"
                                                     "border:5px solid lightgray;"
                                                     "border-radius:5px;"
                                                     "margin-top: 1ex;}"
                                                     "QGroupBox::title{"
                                                     "subcontrol-origin: margin;"
                                                     "subcontrol-position:top center;"
                                                     "padding:0 3px;}"));
    }
}

void GameField::setGame() {
    setPlayerMove(false);
    ui->fenceLabelO->setStyleSheet("font-size: 20px; font-weight: bold");
    ui->fenceLabelX->setStyleSheet("font-size: 20px; font-weight: bold");
    ui->fenceCounterO->display(10);
    ui->fenceCounterX->display(10);

}

void GameField::updateFenceCounter(bool player, int counter) {
    if (!player) {
        ui->fenceCounterO->display(counter);
    } else {
        ui->fenceCounterX->display(counter);
    }
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
            }


            ui->Board->addWidget(button, h, w);
        }
    }
    board.cells[0][4].button->setText("X");
    board.cells[0][4].setPlayerMark(true);
    board.cells[8][4].button->setText("O");
    board.cells[8][4].setPlayerMark(false);
    return board;
}



