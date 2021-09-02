#include "PathFinder.h"
#include "Controller.h"
#include <queue>

PathFinder::PathFinder(const vector<vector<Cell>> &cells) : cells(cells){};

void PathFinder::bfs(const Cell &cell) {
    distances.assign(9, std::vector<int>(9, INT_MAX));
    previousCells.assign(9, std::vector<Cell>(9));

    std::queue<Cell> q;
    q.push(cell);
    distances[cell.y][cell.x] = 0;
    previousCells[cell.y][cell.x] = cells[cell.y][cell.x];
    while (!q.empty()) {
        Cell c = q.front();
        q.pop();
        for (auto dir : c.directions) {
            if (distances[c.y + dir.y][c.x + dir.x] == INT_MAX) {
                distances[c.y + dir.y][c.x + dir.x] = distances[c.y][c.x] + 1;
                previousCells[c.y + dir.y][c.x + dir.x] = c;
                q.push(cells[c.y + dir.y][c.x + dir.x]);
            }
        }
    }
}

bool PathFinder::pathsExist(const Cell &first, const Cell &second) {
    bfs(cells[first.y][first.x]);
    for (int i = 0; i < 10; ++i) {
        if (i == 9) {
            return false;
        }
        if (distances[0][i] != INT_MAX) {
            break;
        }
    }
    bfs(cells[second.y][second.x]);
    for (int i = 0; i < 10; ++i) {
        if (i == 9) {
            return false;
        }
        if (distances[8][i] != INT_MAX) {
            break;
        }
    }
    return true;
}

vector<vector<Cell>> &PathFinder::getField() {
    return cells;
}

int PathFinder::distanceToWin(const Cell &cell, bool player) {
    bfs(cell);
    int distance = INT_MAX;
    if (player) {
        for (int i = 0; i < 9; ++i) {
            if (distances[8][i] < distance) {
                distance = distances[8][i];
                victoryCell = cells[8][i];
            }
        }
    } else {
        for (int i = 0; i < 9; ++i) {
            if (distances[0][i] < distance) {
                distance = distances[0][i];
                victoryCell = cells[0][i];
            }
        }
    }
    return distance;
};

Direction PathFinder::nextMoveDirection(const Cell &cell, bool player) {
    distanceToWin(cell, player);
    Cell currentCell = victoryCell;
    Cell previousCell = previousCells[currentCell.y][currentCell.x];

    while (!sameCells(cell, previousCell)) {
        currentCell = previousCell;
        previousCell = previousCells[currentCell.y][currentCell.x];
    }

    return Direction(currentCell.x - cell.x, currentCell.y - cell.y);
}
