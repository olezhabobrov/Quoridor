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
    explicit Controller(QObject * = nullptr, bool = false);
    void nextMove();
    bool checkFence(const Fence &, const Fence &);
    Board& getBoard();
    Cell& getCurrentPosition(bool);
    void makeMove(Direction, bool);
    void deleteMoves(const Fence &, vector<vector<Cell>>&);
    void restoreMoves(const Fence &, vector<vector<Cell>>&);

private:
    void setConnections();
    void setGame();
    void cellClicked(Cell&);
    void fenceClicked(Fence &);
    void prepareMove();
    void clearMove();
    void setAvailable(Cell &);
    void setAvailable(Fence &);
    void markFence(Fence &);
    void unmarkFences();
    void unmarkCells();
    void setFence(Fence &, Fence &);
    void changePlayer();


signals:

};
