#pragma once
#include "Chess.h"
class Che :
    public Chess
{
private:
    char key;
public:
    Che(int camp, int x);
    Che(int camp, int x, int y);
    virtual bool walkRule(int offset_x, int offset_y);
    virtual bool findRoad();
    void reset(char c);
    void display();
    virtual bool isJiang() { return false; };
    virtual bool isBlock(int x, int y){ return false; }
};

