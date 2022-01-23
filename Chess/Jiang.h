#pragma once
#include "Chess.h"
class Jiang :
    public Chess
{
public:
    Jiang(int camp);
    Jiang(int camp,int x,int y);
    virtual bool walkRule(int offset_x, int offset_y);
    virtual bool findRoad();
    bool chooseRoad(int offset_y);
    int isFaced();
    virtual bool isJiang();
    virtual bool isBlock(int x, int y) { return false; }
};

