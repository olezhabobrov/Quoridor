#include <exception>
#include "Bot.h"
#include "PathFinder.h"

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

Bot::Bot(Controller *controller) : controller(controller), playerMove() {};

int Bot::evaluationOfPosition(int dumbPlayer, int botPlayer) const {
    if (botPlayer == 0) {
        return +INT_MAX / 3;
    }
    if (dumbPlayer == 0) {
        return -INT_MAX / 3;
    }
    int result = (dumbPlayer - botPlayer) * distanceCoef + (controller->getBoard().players[1].fenceCount -
            controller->getBoard().players[0].fenceCount) * fenceCoef;
    return result;
}

int Bot::minmax(int depth, bool player) {
    // check if field state is valid
    PathFinder pFinder(controller->getBoard().cells);
    int dumbPlayer = pFinder.distanceToWin(*controller->getBoard().players[0].currentPosition, false);
    int botPlayer = pFinder.distanceToWin(*controller->getBoard().players[1].currentPosition, true);
    if (dumbPlayer == INT_MAX || botPlayer == INT_MAX) {
        throw std::runtime_error("");
    }

    if (depth == maxDepth) {
        return evaluationOfPosition(dumbPlayer, botPlayer);
    }
    int result = (player ? -INT_MAX / 2 : +INT_MAX / 2);
    // check moves
    auto launchNext = [&](Direction dir){
        controller->makeMove(dir, player);
        int move = minmax(depth + 1, player ^ 1);
        if (move < result && !player || move > result && player) {
            if (depth == 0){
                playerMove = Move(MoveType::PAWN, dir);
            }
            result = move;
        }
        // restoring move
        controller->makeMove(Direction(-dir.x, -dir.y), player);
    };

    for (auto dir : controller->getCurrentPosition(player).directions) {
        Cell *cell = controller->getBoard().players[player].currentPosition;
        Cell &cellTemp = controller->getBoard().cells[cell->y + dir.y][cell->x + dir.x];
        if (sameCells(*controller->getBoard().players[player ^ 1].currentPosition, cellTemp)){
            if (cellTemp.findDirection(dir) != -1) {
                launchNext(Direction(2 * dir.x, 2 * dir.y));
            } else {
                for (auto dirT : cellTemp.directions) {
                    if (!sameCells(controller->getBoard().cells[cellTemp.y + dirT.y][cellTemp.x + dirT.x], *cell)) {
                        launchNext(Direction(dirT.x + dir.x, dirT.y + dir.x));
                    }
                }
            }
        } else{
            launchNext(dir);
        }

    }

    // check fences
    int y = controller->getCurrentPosition(player ^ 1).y;
    int x = controller->getCurrentPosition(player ^ 1).x;
    // horizontal
    checkFence(Orientation::HORIZONTAL, y - 1, x, y - 1, x + 1, result, depth, player);
    checkFence(Orientation::HORIZONTAL, y - 1, x - 1, y - 1, x, result, depth, player);
    checkFence(Orientation::HORIZONTAL, y, x, y, x + 1, result, depth, player);
    checkFence(Orientation::HORIZONTAL, y, x - 1, y, x, result, depth, player);

    // vertical
    checkFence(Orientation::VERTICAL, y - 1, x - 1, y, x - 1, result, depth, player);
    checkFence(Orientation::VERTICAL, y, x - 1, y + 1, x - 1, result, depth, player);
    checkFence(Orientation::VERTICAL, y - 1, x, y, x, result, depth, player);
    checkFence(Orientation::VERTICAL, y, x, y + 1, x, result, depth, player);
    return result;

}

void Bot::play() {
    minmax();
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

void Bot::checkFence(Orientation orient,int y1, int x1, int y2, int x2, int & result, int depth, bool player) {
    if (orient == Orientation::HORIZONTAL) {
        if (y1 < 0 || y1 > 7 || x1 < 0 || x2 > 8) {
            return;
        }
        Fence& first = controller->getBoard().horizontalFences[y1][x1];
        Fence& second = controller->getBoard().horizontalFences[y2][x2];
        Fence& middle = controller->getBoard().betweenDots[(y1 + y2) / 2][(x1 + x2) / 2];
        if (!first.marked && !second.marked && !middle.marked) {
            if (controller->getBoard().players[player].fenceCount-- > 0){
                controller->setFence(first, second, false);
                try {
                    int move = minmax(depth + 1, player ^ 1);
                    if (move < result && !player || move > result && player) {
                        if (depth == 0){
                            playerMove = Move(MoveType::FENCE, &first, &second);
                        }
                        result = move;
                    }
                }  catch (std::runtime_error &) {}
                // remove fences
                controller->removeFence(first, second);
            }
            controller->getBoard().players[player].fenceCount++;
        }
    }
    if (orient == Orientation::VERTICAL) {
        if (y1 < 0 || y2 > 8 || x1 < 0 || x2 > 7) {
            return;
        }
        Fence& first = controller->getBoard().verticalFences[y1][x1];
        Fence& second = controller->getBoard().verticalFences[y2][x2];
        Fence& middle = controller->getBoard().betweenDots[(y1 + y2) / 2][(x1 + x2) / 2];
        if (!first.marked && !second.marked && !middle.marked) {
            if (controller->getBoard().players[player].fenceCount-- > 0){
                controller->setFence(first, second, false);
                try{
                    int move = minmax(depth + 1, player ^ 1);
                    if (move < result && !player || move > result && player) {
                        if (depth == 0){
                            playerMove = Move(MoveType::FENCE, &first, &second);
                        }
                        result = move;
                    }
                } catch(std::runtime_error&) {}
                // remove fences
                controller->removeFence(first, second);
            }
            controller->getBoard().players[player].fenceCount++;
        }
    }
}

