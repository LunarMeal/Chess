#pragma once
#include "Chess.h"
class Che :
    public Chess
{
private:
    Point mp_temp;
    char key;
public:
    Che(int camp, int x);
    virtual bool walkRule(int offset_x, int offset_y);
    virtual bool findRoad();
    void reset(char c);
    void display();
};

