#include "Bot.h"
#include "PathFinder.h"
#include <exception>

Move::Move(MoveType type, Direction dir) : type(type), dir(dir) {
    if (type != MoveType::PAWN) {
        assert(false);
    }
}

Move::Move(MoveType type, Fence *first, Fence *second) : type(type), first(first), second(second) {
    if (type != MoveType::FENCE) {
        assert(false);
    }
}

Bot::Bot(Controller *controller) : controller(controller), playerMove(){};

int Bot::evaluationOfPosition(int dumbPlayer, int botPlayer) const {
    if (botPlayer == 0) {
        return +INT_MAX / 3;
    }
    if (dumbPlayer == 0) {
        return -INT_MAX / 3;
    }
    int result = (dumbPlayer - botPlayer) * distanceCoef +
                 (controller->getBoard().players[1].fenceCount + 1 -
                  controller->getBoard().players[0].fenceCount) *
                         fenceCoef +
                 (controller->getBoard().players[0].currentPosition->y - 9 +
                  controller->getBoard().players[1].currentPosition->y) *
                         manhattanDistCoef;
    return result;
}

int Bot::minmax(int depth, bool player, int alpha, int beta) {
    // check if field state is valid
    PathFinder pFinder(controller->getBoard().cells);
    int dumbPlayer = pFinder.distanceToWin(*controller->getBoard().players[0].currentPosition, false);
    int botPlayer = pFinder.distanceToWin(*controller->getBoard().players[1].currentPosition, true);
    if (dumbPlayer == INT_MAX || botPlayer == INT_MAX) {
        throw std::runtime_error("NO WAY FOR A PLAYER");
    }

    // if one player won
    if (dumbPlayer == 0) {
        return -INT_MAX;
    }
    if (botPlayer == 0) {
        return INT_MAX;
    }

    // if the end of recursion
    if (depth == maxDepth) {
        return evaluationOfPosition(dumbPlayer, botPlayer);
    }

    int result = (player ? -INT_MAX / 2 : +INT_MAX / 2);

    // make move
    auto launchNext = [&](Direction dir) {
        controller->makeMove(dir, player);
        int move = minmax(depth + 1, player ^ 1, alpha, beta);
        if (move < result && !player || move > result && player) {
            if (depth == 0) {
                playerMove = Move(MoveType::PAWN, dir);
            }
            result = move;
        }
        // restoring move
        controller->makeMove(Direction(-dir.x, -dir.y), player);
        return move;
    };

    int move = 0;

    auto checkAndMakeMove = [&](Direction dir) {
        Cell *cell = controller->getBoard().players[player].currentPosition;
        Cell &cellTemp = controller->getBoard().cells[cell->y + dir.y][cell->x + dir.x];
        if (sameCells(*controller->getBoard().players[player ^ 1].currentPosition, cellTemp)) {
            if (cellTemp.findDirection(dir) != -1) {
                move = launchNext(Direction(2 * dir.x, 2 * dir.y));
            } else {
                for (auto dirT : cellTemp.directions) {
                    if (!sameCells(controller->getBoard().cells[cellTemp.y + dirT.y][cellTemp.x + dirT.x], *cell)) {
                        move = launchNext(Direction(dirT.x + dir.x, dirT.y + dir.y));
                    }
                }
            }
        } else {
            move = launchNext(dir);
        }
    };

    // alpha beta pruning
    auto pruning = [&]() {
        if (player) {
            alpha = std::max(alpha, result);
            if (beta < result) {
                return true;
            }
        } else {
            beta = std::min(beta, result);
            if (alpha > result) {
                return true;
            }
        }
        return false;
    };

    // if zero fences available
    if (controller->getBoard().players[player].fenceCount == 0) {
        Direction dir = pFinder.nextMoveDirection(*controller->getBoard().players[player].currentPosition, player);
        checkAndMakeMove(dir);
        if (depth == 0) {
            playerMove = Move(MoveType::PAWN, dir);
        }
        return result;
    }

    for (auto dir : controller->getCurrentPosition(player).directions) {
        checkAndMakeMove(dir);

        if (pruning()) {
            return result;
        }
    }

    // check fences
    int y = controller->getCurrentPosition(player ^ 1).y;
    int x = controller->getCurrentPosition(player ^ 1).x;
    // horizontal
    for (int yd = 0; yd <= 1; ++yd) {
        for (int xd = 0; xd <= 1; ++xd) {
            move = checkFence(Orientation::HORIZONTAL, y - yd, x - 1 + xd, y - yd, x + xd, result, depth, player, alpha, beta);
            if (pruning()) {
                return result;
            }
        }
    }
    // vertical
    for (int xd = 0; xd <= 1; ++xd) {
        for (int yd = 0; yd <= 1; ++yd) {
            move = checkFence(Orientation::VERTICAL, y - 1 + yd, x - xd, y + yd, x - xd, result, depth, player, alpha, beta);
            if (pruning()) {
                return result;
            }
        }
    }
    y = controller->getCurrentPosition(player).y;
    x = controller->getCurrentPosition(player).x;
    for (int yd = 0; yd <= 1; ++yd) {
        for (int xd = 0; xd <= 1; ++xd) {
            move = checkFence(Orientation::HORIZONTAL, y - yd, x - 1 + xd, y - yd, x + xd, result, depth, player, alpha, beta);
            if (pruning()) {
                return result;
            }
        }
    }
    // vertical
    for (int xd = 0; xd <= 1; ++xd) {
        for (int yd = 0; yd <= 1; ++yd) {
            move = checkFence(Orientation::VERTICAL, y - 1 + yd, x - xd, y + yd, x - xd, result, depth, player, alpha, beta);
            if (pruning()) {
                return result;
            }
        }
    }

    return result;
}

void Bot::play() {
    int res = minmax();
    assert(playerMove.type != NOMOVE);
    if (playerMove.type == PAWN) {
        Cell &prev = *controller->getBoard().players[1].currentPosition;
        Cell &cell = controller->getBoard().cells[prev.y + playerMove.dir.y][prev.x + playerMove.dir.x];
        cell.available = true;
        controller->placeCell(cell);
        return;
    }
    if (playerMove.type == FENCE) {
        controller->setFence(*playerMove.first, *playerMove.second);
        controller->nextMove();
    }
}

int Bot::checkFence(Orientation orient, int y1, int x1, int y2, int x2, int &result, int depth, bool player, int alpha, int beta) {
    int move = 0;
    if (orient == Orientation::HORIZONTAL) {
        if (y1 < 0 || y1 > 7 || x1 < 0 || x2 > 8) {
            return (player ? -INT_MAX : INT_MAX);
        }
        Fence &first = controller->getBoard().horizontalFences[y1][x1];
        Fence &second = controller->getBoard().horizontalFences[y2][x2];
        Fence &middle = controller->getBoard().betweenDots[(y1 + y2) / 2][(x1 + x2) / 2];
        if (!first.marked && !second.marked && !middle.marked) {
            if (controller->getBoard().players[player].fenceCount-- > 0) {
                controller->setFence(first, second, false);
                try {
                    move = minmax(depth + 1, player ^ 1, alpha, beta);
                    if (move < result && !player || move > result && player) {
                        if (depth == 0) {
                            playerMove = Move(MoveType::FENCE, &first, &second);
                        }
                        result = move;
                    }
                } catch (std::runtime_error &) {}
                // remove fences
                controller->removeFence(first, second);
            }
            controller->getBoard().players[player].fenceCount++;
        }
    }
    if (orient == Orientation::VERTICAL) {
        if (y1 < 0 || y2 > 8 || x1 < 0 || x2 > 7) {
            return (player ? -INT_MAX : INT_MAX);
        }
        Fence &first = controller->getBoard().verticalFences[y1][x1];
        Fence &second = controller->getBoard().verticalFences[y2][x2];
        Fence &middle = controller->getBoard().betweenDots[(y1 + y2) / 2][(x1 + x2) / 2];
        if (!first.marked && !second.marked && !middle.marked) {
            if (controller->getBoard().players[player].fenceCount-- > 0) {
                controller->setFence(first, second, false);
                try {
                    move = minmax(depth + 1, player ^ 1, alpha, beta);
                    if (move < result && !player || move > result && player) {
                        if (depth == 0) {
                            playerMove = Move(MoveType::FENCE, &first, &second);
                        }
                        result = move;
                    }
                } catch (std::runtime_error &) {}
                // remove fences
                controller->removeFence(first, second);
            }
            controller->getBoard().players[player].fenceCount++;
        }
    }
    return move;
}
