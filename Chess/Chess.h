#pragma once
#define NOMINMAX
#include "Point.h"
#include "conio.h"
#include <deque>
#include <vector>
#include <stack>
#include <Windows.h>
#include <iostream>
#include <cmath>
using namespace std;
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
class Chess
{
protected:
	Point m_p;
	Point mp_temp;
public:
	static deque<Chess*> d;
	static int bound;
	static int tail;
	static deque<int> getRchess();
	static deque<int> getBchess();
	static int isHasChess(int x, int y);
	string m_Name;
	int m_Camp;
	bool isDead;
	bool isMoving;
	Chess();
	~Chess();
	Point getPos()const;
	void setPos(int x,int y);
	string xNumToChar();
	string xNumToChar(unsigned int num);
	string yNumToChar(unsigned int num);
	virtual bool walkRule(int offset_x, int offset_y)=0;
	virtual bool findRoad()=0;
	virtual bool isBlock(int x, int y) = 0;
	bool move(int offset_x, int offset_y);
	virtual bool isJiang() = 0;
	void beEaten();
};

