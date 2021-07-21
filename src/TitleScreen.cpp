#include "TitleScreen.h"
#include "ui_TitleScreen.h"


TitleScreen::TitleScreen(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TitleScreen)
{
    ui->setupUi(this);
}

void TitleScreen::on_Button2Players_clicked()
{
    this->hide();
}

