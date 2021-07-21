#include "GameField.h"
#include "ui_GameField.h"

GameField::GameField(QWidget *parent) : QDialog(parent), ui(new Ui::GameField)
{
    ui->setupUi(this);

}

GameField::~GameField() {
    delete ui;
}
