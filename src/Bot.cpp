#include "Bot.h"
#include "PathFinder.h"

Bot::Bot(Controller *controller) : controller(controller) {};

int Bot::evaluationOfPosition() const {
    PathFinder pFinder(controller->getBoard().cells);
    return (pFinder.distanceToWin(*controller->getBoard().players[0].currentPosition, false)
           - pFinder.distanceToWin(*controller->getBoard().players[1].currentPosition, true)) * distanceCoef;
}

int Bot::minmax(int depth, bool player) {
    if (depth == maxDepth) {
        return evaluationOfPosition();
    }
    int result = (player ? -INT_MAX : +INT_MAX);
    // check moves
    for (auto dir : controller->getCurrentPosition(player).directions) {
        controller->makeMove(dir, player);
        int move = minmax(depth + 1, player ^ 1);
        if (move < result && !player || move > result && player) {
            result = move;
        }
        // restoring move
        controller->makeMove(Direction(-dir.x, -dir.y), player);
    }

    // check fences
    // horizontal

}
