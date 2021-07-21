#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class TitleScreen;
}
QT_END_NAMESPACE


class TitleScreen final : public QMainWindow
{
    Q_OBJECT

    Ui::TitleScreen *ui;

public:
    TitleScreen(QWidget *parent = nullptr);

private slots:
    void on_Button2Players_clicked();
};
