#include "Controller.h"
#include "Bot.h"
#include "PathFinder.h"
#include "VictoryScreen.h"
#include <exception>
#include <iostream>
#include <queue>

Controller::Controller(QObject *parent, bool bot) : QObject(parent), field(), board(field.setField()),
                                                    botConnected(bot) {
    setConnections();
    setGame();

    field.exec();
}

Board &Controller::getBoard() {
    return board;
}

Cell &Controller::getCurrentPosition(bool player) {
    return *board.players[player].currentPosition;
}

void Controller::makeMove(Direction dir, bool player) {
    int new_y = board.players[player]
                        .currentPosition->y +
                dir.y;
    int new_x = board.players[player]
                        .currentPosition->x +
                dir.x;
    if (new_x < 0 || new_x > 8 || new_y < 0 || new_x > 8) {
        throw std::runtime_error("OUT OF BOUNDS");
    }
    board.players[player].currentPosition =
            &board.cells[new_y][new_x];
}

void Controller::setConnections() {
    // set button connections
    for (auto &cellRow : board.cells) {
        for (auto &cell : cellRow) {
            connect(cell.button, &QPushButton::clicked, [&]() {
                cellClicked(cell);
            });
        }
    }

    // set fence connections
    for (auto &fenceRow : board.horizontalFences) {
        for (auto &fence : fenceRow) {
            connect(fence.button, &QPushButton::clicked, [&]() {
                fenceClicked(fence);
            });
        }
    }
    for (auto &fenceRow : board.verticalFences) {
        for (auto &fence : fenceRow) {
            connect(fence.button, &QPushButton::clicked, [&]() {
                fenceClicked(fence);
            });
        }
    }
}

void Controller::cellClicked(Cell &cell) {
    if (cell.available) {
        board.players[board.currentPlayer].currentPosition->button->setText("");
        clearMove();
        board.players[board.currentPlayer].currentPosition = &cell;
        cell.setPlayerMark(board.currentPlayer);
        nextMove();
    }
}

void Controller::placeCell(Cell &cell) {
    setAvailable(cell);
    cellClicked(cell);
}

void Controller::fenceClicked(Fence &fence) {
    if (board.players[board.currentPlayer].fenceCount > 0) {
        // if we place second fence
        if (markedFence) {
            if (&fence == markedFence) {
                unmarkFences();
                return;
            }

            if (fence.available) {
                Fence &initialFence = *markedFence;
                unmarkFences();
                setFence(initialFence, fence);

                clearMove();
                nextMove();
            }
        }
        // if we place first fence
        else {
            if (!fence.marked) {
                markFence(fence);
            }
        }
    }
}

void Controller::markFence(Fence &fence) {
    markedFence = &fence;
    fence.button->setStyleSheet("background-color: green");
    if (fence.orient == Orientation::HORIZONTAL) {
        if (fence.x > 0 && !board.betweenDots[fence.y][fence.x - 1].marked &&
            checkFence(fence, board.horizontalFences[fence.y][fence.x - 1])) {
            setAvailable(board.horizontalFences[fence.y][fence.x - 1]);
        }
        if (fence.x < board.horizontalFences[fence.y].size() - 1 &&
            !board.betweenDots[fence.y][fence.x].marked &&
            checkFence(fence, board.horizontalFences[fence.y][fence.x + 1])) {
            setAvailable(board.horizontalFences[fence.y][fence.x + 1]);
        }
    }
    if (fence.orient == Orientation::VERTICAL) {
        if (fence.y > 0 && !board.betweenDots[fence.y - 1][fence.x].marked &&
            checkFence(fence, board.verticalFences[fence.y - 1][fence.x])) {
            setAvailable(board.verticalFences[fence.y - 1][fence.x]);
        }
        if (fence.y < board.verticalFences.size() - 1 &&
            !board.betweenDots[fence.y][fence.x].marked &&
            checkFence(board.verticalFences[fence.y + 1][fence.x], fence)) {
            setAvailable(board.verticalFences[fence.y + 1][fence.x]);
        }
    }
}

void Controller::nextMove() {
    if (board.players[0].currentPosition->y == 0 || board.players[1].currentPosition->y == 8) {
        VictoryScreen victory(&field, (board.players[0].currentPosition->y == 0 ? false : true));
        victory.exec();
        field.close();
        return;
    }
    changePlayer();
    //  TODO: check if bot connected
    if (board.currentPlayer && botConnected) {
        Bot bot(this);
        bot.play();
    } else {
        prepareMove();
    }
}

void Controller::setGame() {
    board.players.clear();
    board.players.emplace_back(0, &board.cells[8][4]);
    board.players.emplace_back(1, &board.cells[0][4]);
    field.setGame();
    prepareMove();
}

bool sameCells(const Cell &first, const Cell &second) {
    return first.x == second.x && first.y == second.y;
}

namespace {
    void printCell(Cell &cell) {
        printf("x=%d  y=%d\n", cell.x, cell.y);
    }
}// namespace

void Controller::prepareMove() {

    Cell *cell = board.players[board.currentPlayer].currentPosition;
    for (auto dir : cell->directions) {
        Cell &cellTemp = board.cells[cell->y + dir.y][cell->x + dir.x];
        if (sameCells(*board.players[board.currentPlayer ^ 1].currentPosition, cellTemp)) {
            if (cellTemp.findDirection(dir) != -1) {
                setAvailable(board.cells[cellTemp.y + dir.y][cellTemp.x + dir.x]);
            } else {
                for (auto dirT : cellTemp.directions) {
                    if (!sameCells(board.cells[cellTemp.y + dirT.y][cellTemp.x + dirT.x], *cell)) {
                        setAvailable(board.cells[cellTemp.y + dirT.y][cellTemp.x + dirT.x]);
                    }
                }
            }
        } else {
            setAvailable(cellTemp);
        }
    }
}

void Controller::clearMove() {
    unmarkCells();
    unmarkFences();
}


void Controller::setAvailable(Cell &cell) {
    highlightedCells.push_back(&cell);
    cell.setAvailable();
}

void Controller::setAvailable(Fence &fence) {
    if (!fence.marked) {
        highlightedFences.push_back(&fence);
        fence.button->setStyleSheet("background-color: lightgreen");
        fence.available = true;
    }
}

void Controller::unmarkCells() {
    for (Cell *cell : highlightedCells) {
        cell->setUnavailable();
    }
    highlightedCells.clear();
}

void Controller::unmarkFences() {
    if (markedFence) {
        markedFence->button->setStyleSheet("background-color: lightgrey");
        markedFence = nullptr;
    }
    for (auto &fence : highlightedFences) {
        fence->button->setStyleSheet("background-color: lightgrey");
        fence->available = false;
    }
    highlightedFences.clear();
}

void Controller::setFence(Fence &first, Fence &second, bool show) {

    first.setMarked(show);
    deleteMoves(first, board.cells);
    second.setMarked(show);
    deleteMoves(second, board.cells);
    board.betweenDots[(first.y + second.y) / 2][(first.x + second.x) / 2].setMarked(show);
    if (show) {
        field.updateFenceCounter(board.currentPlayer, --board.players[board.currentPlayer].fenceCount);
    }
}

void Controller::removeFence(Fence &first, Fence &second) {
    first.marked = false;
    addMoves(first, board.cells);
    second.marked = false;
    addMoves(second, board.cells);
    board.betweenDots[(first.y + second.y) / 2][(first.x + second.x) / 2].marked = false;
}

void Controller::deleteMoves(const Fence &fence, vector<vector<Cell>> &cells) {
    if (fence.orient == Orientation::HORIZONTAL) {
        cells[fence.y][fence.x].deleteDirection(Direction(0, 1));
        cells[fence.y + 1][fence.x].deleteDirection(Direction(0, -1));
    }
    if (fence.orient == Orientation::VERTICAL) {
        cells[fence.y][fence.x].deleteDirection(Direction(1, 0));
        cells[fence.y][fence.x + 1].deleteDirection(Direction(-1, 0));
    }
}

void Controller::addMoves(const Fence &fence, vector<vector<Cell>> &cells) {
    if (fence.orient == Orientation::HORIZONTAL) {
        cells[fence.y][fence.x].directions.push_back(Direction(0, 1));
        cells[fence.y + 1][fence.x].directions.push_back(Direction(0, -1));
    }
    if (fence.orient == Orientation::VERTICAL) {
        cells[fence.y][fence.x].directions.push_back(Direction(1, 0));
        cells[fence.y][fence.x + 1].directions.push_back(Direction(-1, 0));
    }
}

void Controller::changePlayer() {
    board.currentPlayer ^= 1;
    field.setPlayerMove(board.currentPlayer);
}

bool Controller::checkFence(const Fence &first, const Fence &second) {
    if (first.marked || second.marked) {
        return false;
    }
    PathFinder pFinder(board.cells);
    deleteMoves(first, pFinder.getField());
    deleteMoves(second, pFinder.getField());
    return pFinder.pathsExist(*board.players[0].currentPosition, *board.players[1].currentPosition);
}
