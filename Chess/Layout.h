#pragma once
#include <deque>
#include "Chess.h"
#define LINE "—"
#define VLINE "| "
#define SPACE "  "
#define SLASH "/ "
#define BSLASH "\\ "
#define BSLASH "\\ "
#define NODE "+ "

void color(int a);
void Layout();
void Board();
void Check();
string spSign(int x,int y);
int selectChess();
int selectChess(deque<int>);
deque<Chess*> InitChess();

/*
    原始局面
	cout << "1 ==2 ==3 ==4 ==5 ==6 ==7 ==8 ==9 " <<endl;
 	cout << "车—马—象—士—将—士—象—马—车" << endl;
	cout << "|   |   |   | \\ | / |   |   |   | " << endl;
	cout << "+ —+ —+ —+ —+ —+ —+ —+ —+ " << endl;
	cout << "|   |   |   | / | \\ |   |   |   | " << endl;
	cout << "+ —炮—+ —+ —+ —+ —+ —炮—+ " << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "卒—+ —卒—+ —卒—+ —卒—+ —卒" << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "—————————————————" << endl;
	cout << "|      楚河              汉界   | " << endl;
	cout << "—————————————————" << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "兵—+ —兵—+ —兵—+ —兵—+ —兵" << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "+ —砲—+ —+ —+ —+ —+ —砲—+ " << endl;
	cout << "|   |   |   | \\ | / |   |   |   | " << endl;
	cout << "+ —+ —+ —+ —+ —+ —+ —+ —+ " << endl;
	cout << "|   |   |   | / | \\ |   |   |   | " << endl;
	cout << "車—馬—相—仕—帅—仕—相—馬—車" << endl;
	cout << "九==八==七==六==五==四==三==二==一" <<endl;
*/
/*
	空棋盘
	cout << "1 ==2 ==3 ==4 ==5 ==6 ==7 ==8 ==9 " <<endl;
	cout << "+ —+ —+ —+ —+ —+ —+ —+ —+ " << endl;
	cout << "|   |   |   | \\ | / |   |   |   | " << endl;
	cout << "+ —+ —+ —+ —+ —+ —+ —+ —+ " << endl;
	cout << "|   |   |   | / | \\ |   |   |   | " << endl;
	cout << "+ —+ —+ —+ —+ —+ —+ —+ —+ " << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "+ —+ —+ —+ —+ —+ —+ —+ —+ " << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "—————————————————" << endl;
	cout << "|      楚河              汉界   | " << endl;
	cout << "—————————————————" << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "+ —+ —+ —+ —+ —+ —+ —+ —+ " << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "+ —+ —+ —+ —+ —+ —+ —+ —+ " << endl;
	cout << "|   |   |   | \\ | / |   |   |   | " << endl;
	cout << "+ —+ —+ —+ —+ —+ —+ —+ —+ " << endl;
	cout << "|   |   |   | / | \\ |   |   |   | " << endl;
	cout << "+ —+ —+ —+ —+ —+ —+ —+ —+ " << endl;
	cout << "九==八==七==六==五==四==三==二==一" <<endl;
*/