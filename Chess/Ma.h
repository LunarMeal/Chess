#pragma once
#include "Chess.h"
class Ma :
    public Chess
{
public:
    Ma(int camp, int x);
    Ma(int camp, int x, int y);
    virtual bool walkRule(int offset_x, int offset_y);
    virtual bool findRoad();
    bool chooseRoad();
    bool isBlock(int x, int y);
    virtual bool isJiang() { return false; };
};

