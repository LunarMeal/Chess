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
    virtual bool walkRule(int offset_x, int offset_y);
    virtual bool findRoad();
    void reset(char c);
    void display();
    bool Boom(int offset_x, int offset_y);
};

