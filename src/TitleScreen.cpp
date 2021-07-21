#include "TitleScreen.h"
#include "ui_TitleScreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    button = new QPushButton(this);
    button->setText("Hello");
}


