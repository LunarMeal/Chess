#pragma once
#include "Chess.h"
class Jiang :
    public Chess
{
public:
    Jiang(int camp);
    virtual bool walkRule(int offset_x, int offset_y);
    virtual bool findRoad();
    bool chooseRoad(int offset_y);
    int isFaced();
};

