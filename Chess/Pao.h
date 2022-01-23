#pragma once
#include "Chess.h"
class Pao :
    public Chess
{
private:
    Point mp_temp;
    char key;
public:
    Pao(int camp, int x);
    Pao(int camp, int x, int y);
    virtual bool walkRule(int offset_x, int offset_y);
    virtual bool findRoad();
    void reset(char c);
    void display();
    bool Boom(int offset_x, int offset_y);
    virtual bool isJiang() { return false; };
    virtual bool isBlock(int x, int y) { return false; }
};

