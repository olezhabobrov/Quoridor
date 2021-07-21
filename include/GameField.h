#pragma once

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class GameField;
}
QT_END_NAMESPACE


class GameField : public QMainWindow
{
    Q_OBJECT

    Ui::GameField *ui;

public:
    explicit GameField(QWidget *parent = nullptr);

signals:

};
