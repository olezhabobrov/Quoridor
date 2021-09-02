#pragma once
#include "Controller.h"
#include "OtherTypes.h"

enum MoveType {
    NOMOVE,
    PAWN,
    FENCE,
};

struct Move {
    MoveType type = MoveType::NOMOVE;
    Direction dir = Direction(0, 0);
    Fence *first = nullptr;
    Fence *second = nullptr;

    Move() = default;
    Move(MoveType, Direction);
    Move(MoveType, Fence *, Fence *);
};

class Controller;
class Bot {
    Controller *controller = nullptr;
    const int maxDepth = 3;
    const int distanceCoef = 10;
    const int fenceCoef = 5;
    const int manhattanDistCoef = 1;

    Move playerMove;

public:
    void play();
    Bot(Controller *);

private:
    int minmax(int = 0, bool = true, int = -INT_MAX, int = INT_MAX);
    int evaluationOfPosition(int, int) const;
    int checkFence(Orientation, int, int, int, int, int &, int, bool, int, int);
};
