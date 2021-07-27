#pragma once

#include <QObject>
#include <vector>
#include "Types.h"
#include "GameField.h"

struct Player {
    bool id = 0;
    int fenceCount = 10;
    Cell *currentPosition;

    Player(bool id, Cell *c) : id(id), currentPosition(c) {};
};

class Controller : public QObject
{
Q_OBJECT

    GameField field;
    Board board;
    bool currentPlayer = 0;
    vector<Player> players;
    std::vector<Cell*> highlightedCells;
    std::vector<Fence*> highlightedFences;
    Fence* markedFence = nullptr;

public:
    explicit Controller(QObject *parent = nullptr);


private:
    void setConnections();
    void setGame();
    void cellClicked(Cell&);
    void fenceClicked(Fence &);
    void prepareMove();
    void clearMove();
    void nextMove();
    void setAvailable(Cell &);
    void setAvailable(Fence &);
    void markFence(Fence &);
    void unmarkFences();
    void unmarkCells();
    void setFence(Fence &, Fence &);
    void deleteMoves(Fence &);
    void changePlayer();

signals:

};
