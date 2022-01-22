#pragma once
#include "Chess.h"
class Shi :
    public Chess
{
public:
    Shi(int camp, int x);
    virtual bool walkRule(int offset_x, int offset_y);
    virtual bool findRoad();
    bool chooseRoad();
};

