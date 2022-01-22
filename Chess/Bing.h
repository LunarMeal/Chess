#pragma once
#include "Chess.h"
class Bing :
    public Chess
{
public:
    Bing(int camp,int x);
    virtual bool walkRule(int offset_x, int offset_y);
    virtual bool findRoad();
    bool chooseRoad();
};

