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
    vector<Cell*> highlightedCells;
    vector<Fence*> highlightedFences;
    Fence* markedFence = nullptr;
    bool botConnected = false;

public:
    explicit Controller(QObject *parent = nullptr, bool = false);


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
    void deleteMoves(const Fence &, vector<vector<Cell>>&);
    void changePlayer();
    bool checkFence(const Fence &, const Fence &);


signals:

};
