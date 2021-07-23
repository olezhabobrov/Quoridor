#pragma once

#include <QDialog>
#include <vector>
#include "Types.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class GameField;
}
QT_END_NAMESPACE


class GameField : public QDialog
{
    Q_OBJECT

    Ui::GameField *ui;

public:
    explicit GameField(QWidget *parent = nullptr);
    std::vector<Cell> setField();

    ~GameField();

private:
    void setConnections();


signals:

private slots:
    void placeFence();
};
