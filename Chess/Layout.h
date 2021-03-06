#pragma once
#include <fstream>
#include <string>
#include "Chess.h"
#define LINE "！"
#define VLINE "| "
#define SPACE "  "
#define SLASH "/ "
#define BSLASH "\\ "
#define BSLASH "\\ "
#define NODE "+ "
#define PATH "./lib/chess.txt"

void color(int a);
void Layout(int mode);
void Board();
void Check();
string spSign(int x,int y);
int selectChess();
int selectChess(deque<int>);
deque<Chess*> InitChess();
deque<Chess*> CustomChess();

/*
    圻兵蕉中
	cout << "1 ==2 ==3 ==4 ==5 ==6 ==7 ==8 ==9 " <<endl;
 	cout << "概！瀧！?鵝?平！繍！平！?鵝?瀧！概" << endl;
	cout << "|   |   |   | \\ | / |   |   |   | " << endl;
	cout << "+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ " << endl;
	cout << "|   |   |   | / | \\ |   |   |   | " << endl;
	cout << "+ ！土！+ ！+ ！+ ！+ ！+ ！土！+ " << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "怱！+ ！怱！+ ！怱！+ ！怱！+ ！怱" << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "！！！！！！！！！！！！！！！！！" << endl;
	cout << "|      萱采              査順   | " << endl;
	cout << "！！！！！！！！！！！！！！！！！" << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "汚！+ ！汚！+ ！汚！+ ！汚！+ ！汚" << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "+ ！?h！+ ！+ ！+ ！+ ！+ ！?h！+ " << endl;
	cout << "|   |   |   | \\ | / |   |   |   | " << endl;
	cout << "+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ " << endl;
	cout << "|   |   |   | / | \\ |   |   |   | " << endl;
	cout << "??！?R！?燹?碧！芳！碧！?燹??R！??" << endl;
	cout << "湘==伊==鈍==鎗==励==膨==眉==屈==匯" <<endl;
*/
/*
	腎薙徒
	cout << "1 ==2 ==3 ==4 ==5 ==6 ==7 ==8 ==9 " <<endl;
	cout << "+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ " << endl;
	cout << "|   |   |   | \\ | / |   |   |   | " << endl;
	cout << "+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ " << endl;
	cout << "|   |   |   | / | \\ |   |   |   | " << endl;
	cout << "+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ " << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ " << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "！！！！！！！！！！！！！！！！！" << endl;
	cout << "|      萱采              査順   | " << endl;
	cout << "！！！！！！！！！！！！！！！！！" << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ " << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ " << endl;
	cout << "|   |   |   | \\ | / |   |   |   | " << endl;
	cout << "+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ " << endl;
	cout << "|   |   |   | / | \\ |   |   |   | " << endl;
	cout << "+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ ！+ " << endl;
	cout << "湘==伊==鈍==鎗==励==膨==眉==屈==匯" <<endl;
*/