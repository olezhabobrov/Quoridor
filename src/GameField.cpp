#include "GameField.h"
#include "ui_GameField.h"

GameField::GameField(QWidget *parent) : QMainWindow(parent), ui(new Ui::GameField)
{
    ui->setupUi(this);
}
