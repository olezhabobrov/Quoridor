#pragma once
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
    class VictoryScreen;
}
QT_END_NAMESPACE

struct VictoryScreen : public QDialog {

Q_OBJECT

    Ui::VictoryScreen *ui;

public:
    VictoryScreen(QWidget *, bool);
    ~VictoryScreen();

};
