#pragma once
#include "OtherTypes.h"
#include <vector>

using std::vector;

class PathFinder {
    vector<vector<Cell>> cells;
    vector<vector<int>> distances;
    vector<vector<Cell>> previousCells;
    Cell victoryCell;

    void bfs(const Cell &);

public:
    vector<vector<Cell>> &getField();
    bool pathsExist(const Cell &, const Cell &);
    int distanceToWin(const Cell &, bool);
    PathFinder(const vector<vector<Cell>> &);
    Direction nextMoveDirection(const Cell &, bool);
};
