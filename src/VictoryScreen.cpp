#include "VictoryScreen.h"
#include "ui_VictoryScreen.h"


VictoryScreen::VictoryScreen(QWidget *parent, bool winner) : QDialog(parent), ui(new Ui::VictoryScreen) {
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, [=]() { close(); });
    if (winner) {
        ui->label->setText("Player X won!");
    } else {
        ui->label->setText("Player O won!");
    }
    ui->label->setStyleSheet("font-size: 24px");
}

VictoryScreen::~VictoryScreen() {
    delete ui;
}
