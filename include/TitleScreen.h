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

    void setConnections();

public:
    TitleScreen(QWidget *parent = nullptr);
    ~TitleScreen();

private slots:
    void start_2players_game();
    void start_1player_game();
};
