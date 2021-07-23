#pragma once

#include <QObject>
#include <vector>
#include "Types.h"
#include "GameField.h"

class Controller : public QObject
{
Q_OBJECT

    GameField field;
    Board board;

public:
    explicit Controller(QObject *parent = nullptr);


private:
    void setConnections();
    void cellClicked(Cell&);

signals:

};
