#pragma once
#include "Chess.h"
class Bing :
    public Chess
{
public:
    Bing(int camp,int x);
    Bing(int camp, int x, int y);
    virtual bool walkRule(int offset_x, int offset_y);
    virtual bool findRoad();
    bool chooseRoad();
    virtual bool isJiang() { return false; };
    virtual bool isBlock(int x, int y) { return false; }
};

