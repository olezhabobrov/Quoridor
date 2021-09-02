#pragma once

#include "GameField.h"
#include "OtherTypes.h"
#include <QObject>
#include <vector>

class Controller : public QObject {
    Q_OBJECT

    GameField field;
    Board board;
    vector<Cell *> highlightedCells;
    vector<Fence *> highlightedFences;
    Fence *markedFence = nullptr;
    bool botConnected = false;

public:
    explicit Controller(QObject * = nullptr, bool = false);
    void nextMove();
    bool checkFence(const Fence &, const Fence &);
    Board &getBoard();
    Cell &getCurrentPosition(bool);
    void makeMove(Direction, bool);
    void deleteMoves(const Fence &, vector<vector<Cell>> &);
    void restoreMoves(const Fence &, vector<vector<Cell>> &);
    void setFence(Fence &, Fence &, bool = true);
    void removeFence(Fence &, Fence &);
    void placeCell(Cell &);

private:
    void setConnections();
    void setGame();
    void cellClicked(Cell &);
    void fenceClicked(Fence &);
    void prepareMove();
    void clearMove();
    void setAvailable(Cell &);
    void setAvailable(Fence &);
    void markFence(Fence &);
    void unmarkFences();
    void unmarkCells();
    void changePlayer();
    void addMoves(const Fence &, vector<vector<Cell>> &);

signals:
};

bool sameCells(const Cell &, const Cell &);
