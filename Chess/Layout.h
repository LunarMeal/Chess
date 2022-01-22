#pragma once
#include <deque>
#include "Chess.h"
#define LINE "��"
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
    ԭʼ����
	cout << "1 ==2 ==3 ==4 ==5 ==6 ==7 ==8 ==9 " <<endl;
 	cout << "��������ʿ������ʿ��������" << endl;
	cout << "|   |   |   | \\ | / |   |   |   | " << endl;
	cout << "+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ " << endl;
	cout << "|   |   |   | / | \\ |   |   |   | " << endl;
	cout << "+ ���ڡ�+ ��+ ��+ ��+ ��+ ���ڡ�+ " << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "�䡪+ ���䡪+ ���䡪+ ���䡪+ ����" << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "����������������������������������" << endl;
	cout << "|      ����              ����   | " << endl;
	cout << "����������������������������������" << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "����+ ������+ ������+ ������+ ����" << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "+ ���h��+ ��+ ��+ ��+ ��+ ���h��+ " << endl;
	cout << "|   |   |   | \\ | / |   |   |   | " << endl;
	cout << "+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ " << endl;
	cout << "|   |   |   | / | \\ |   |   |   | " << endl;
	cout << "܇���R���ࡪ�ˡ�˧���ˡ��ࡪ�R��܇" << endl;
	cout << "��==��==��==��==��==��==��==��==һ" <<endl;
*/
/*
	������
	cout << "1 ==2 ==3 ==4 ==5 ==6 ==7 ==8 ==9 " <<endl;
	cout << "+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ " << endl;
	cout << "|   |   |   | \\ | / |   |   |   | " << endl;
	cout << "+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ " << endl;
	cout << "|   |   |   | / | \\ |   |   |   | " << endl;
	cout << "+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ " << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ " << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "����������������������������������" << endl;
	cout << "|      ����              ����   | " << endl;
	cout << "����������������������������������" << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ " << endl;
	cout << "|   |   |   |   |   |   |   |   | " << endl;
	cout << "+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ " << endl;
	cout << "|   |   |   | \\ | / |   |   |   | " << endl;
	cout << "+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ " << endl;
	cout << "|   |   |   | / | \\ |   |   |   | " << endl;
	cout << "+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ ��+ " << endl;
	cout << "��==��==��==��==��==��==��==��==һ" <<endl;
*/