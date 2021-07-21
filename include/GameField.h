#pragma once

#include <QDialog>
#include <memory>

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

    ~GameField();

signals:

};
