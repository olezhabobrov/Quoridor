#pragma once
#include "Types.h"
#include <vector>

using std::vector;

class PathFinder {
    vector<vector<Cell>> cells;
    vector<vector<int>> distances;

    void bfs(const Cell &);

public:
    vector<vector<Cell>>& getField();
    bool pathsExist(const Cell&, const Cell&);
    PathFinder(const vector<vector<Cell>> &);


};
