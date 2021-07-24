#pragma once

#include <QObject>
#include <vector>
#include "Types.h"
#include "GameField.h"

struct Player {
    bool id = 0;
    Cell currentPosition;

    Player(bool id, const Cell &c) : id(id), currentPosition(c) {};
};

class Controller : public QObject
{
Q_OBJECT

    GameField field;
    Board board;
    bool currentPlayer = 0;
    vector<Player> players;

public:
    explicit Controller(QObject *parent = nullptr);


private:
    void setConnections();
    void setGame();
    void cellClicked(Cell&);
    void prepareMove();

signals:

};
