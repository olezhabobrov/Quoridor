#include "TitleScreen.h"
#include "ui_TitleScreen.h"
#include "Controller.h"


TitleScreen::TitleScreen(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TitleScreen)
{
    ui->setupUi(this);
}

TitleScreen::~TitleScreen() {
    delete ui;
}

void TitleScreen::on_Button2Players_clicked()
{
    this->hide();
    Controller controller;
    this->show();
}

