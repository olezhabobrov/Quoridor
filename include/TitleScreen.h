#pragma once

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QPushButton *button;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

};
