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

int Bot::evaluationOfPosition() const {
    PathFinder pFinder(controller->getBoard().cells);
    int dumbPlayer = pFinder.distanceToWin(*controller->getBoard().players[0].currentPosition, false);
    int botPlayer = pFinder.distanceToWin(*controller->getBoard().players[1].currentPosition, true);
    if (botPlayer == 0) {
        return +INT_MAX / 2;
    }
    if (dumbPlayer == 0) {
        return -INT_MAX / 2;
    }
    int result = (dumbPlayer - botPlayer) * distanceCoef + (controller->getBoard().players[1].fenceCount -
            controller->getBoard().players[0].fenceCount) * fenceCoef;
//    printf("player=%d   x=%d    y=%d\n", 1, controller->getBoard().players[1].currentPosition->x,
//            controller->getBoard().players[1].currentPosition->y);
//    printf("player=%d   x=%d    y=%d\n", 0, controller->getBoard().players[0].currentPosition->x,
//            controller->getBoard().players[0].currentPosition->y);
//    printf("result=%d\n", result);
    return result;
}

int Bot::minmax(int depth, bool player) {
    if (depth == maxDepth) {
        return evaluationOfPosition();
    }
    int result = (player ? -INT_MAX : +INT_MAX);
    printf("===========================\n");
    printf("player=%d\n", (int)player);
    // check moves
    for (auto dir : controller->getCurrentPosition(player).directions) {
        controller->makeMove(dir, player);
        int move = minmax(depth + 1, player ^ 1);
        printf("result=%d\n", move);
        if (move < result && !player || move > result && player) {
            if (depth == 0){
                playerMove = Move(MoveType::PAWN, dir);
            }
            result = move;
        }
        // restoring move
        controller->makeMove(Direction(-dir.x, -dir.y), player);
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
    printf("===========================\n");
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
        if (controller->checkFence(first, second)) {
            if (controller->getBoard().players[player].fenceCount-- > 0){
                controller->setFence(first, second, false);
                int move = minmax(depth + 1, player ^ 1);
                if (move < result && !player || move > result && player) {
                    if (depth == 0){
                        playerMove = Move(MoveType::FENCE, &first, &second);
                    }
                    result = move;
                }
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
        if (controller->checkFence(first, second)) {
            if (controller->getBoard().players[player].fenceCount-- > 0){
                controller->setFence(first, second, false);
                int move = minmax(depth + 1, player ^ 1);
                printf("result=%d\n", move);
                if (move < result && !player || move > result && player) {
                    if (depth == 0){
                        playerMove = Move(MoveType::FENCE, &first, &second);
                    }
                    result = move;
                }
                // remove fences
                controller->removeFence(first, second);
            }
            controller->getBoard().players[player].fenceCount++;
        }
    }
}

