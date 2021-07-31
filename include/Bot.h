#pragma once
#include "Types.h"
#include "Controller.h"


class Controller;
class Bot {
    Controller *controller = nullptr;
    const int maxDepth = 6;
    const int distanceCoef = 1;

public:
    void play();

    int minmax(int = 0, bool = true);

    int evaluationOfPosition() const;

    Bot(Controller*);
};
