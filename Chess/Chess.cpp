#include "Chess.h"
extern stack<int> deathChess;
Chess::Chess():m_p(),isDead(false),isMoving(false){}
Chess::~Chess(){}
Point Chess::getPos()const {
	return m_p;
}
void Chess::setPos(int x,int y){
	m_p.m_x = x;
	m_p.m_y = y;
	mp_temp.m_x = x;
	mp_temp.m_y = y;
}
int Chess::isHasChess(int x, int y) {
	Point p(x, y);
	for (int i = 0; i < d.size(); i++) {
		if (d[i]->getPos() == p)
			if (!(d[i]->isDead))
				return i;
	}
	return -1;
}
string Chess::xNumToChar() {
	switch (m_p.m_x)
	{
	case 1:
		return "��";
	case 2:
		return "��";
	case 3:
		return "��";
	case 4:
		return "��";
	case 5:
		return "��";
	case 6:
		return "��";
	case 7:
		return "��";
	case 8:
		return "��";
	case 9:
		return "һ";
	default:
		break;
	}
}
string Chess::xNumToChar(unsigned int num) {
	switch (num)
	{
	case 1:
		return "��";
	case 2:
		return "��";
	case 3:
		return "��";
	case 4:
		return "��";
	case 5:
		return "��";
	case 6:
		return "��";
	case 7:
		return "��";
	case 8:
		return "��";
	case 9:
		return "һ";
	default:
		break;
	}
}
string Chess::yNumToChar(unsigned int num) {
	switch (num)
	{
	case 1:
		return "һ";
	case 2:
		return "��";
	case 3:
		return "��";
	case 4:
		return "��";
	case 5:
		return "��";
	case 6:
		return "��";
	case 7:
		return "��";
	case 8:
		return "��";
	case 9:
		return "��";
	default:
		break;
	}
}
deque<int> Chess::getRchess() {
	deque<int> Rchess;
	for (int i = 0; i < bound; i++) {
		if (!(d[i]->isDead)) {
			Rchess.push_back(i);
		}
	}
	return Rchess;
}
deque<int> Chess::getBchess() {
	deque<int> Bchess;
	for (int i = tail; i > bound-1; i--) {
		if (!(d[i]->isDead)) {
			Bchess.push_back(i);
		}
	}
	return Bchess;
}
bool Chess::move(int offset_x, int offset_y) {
	Point next(m_p.m_x + offset_x, m_p.m_y + offset_y);
	int index = isHasChess(next.m_x, next.m_y);
	m_p.m_x += offset_x;
	m_p.m_y += offset_y;
	if (m_Camp == 1) {
		if (index != -1) {
			//��һ��������
			if (d[index]->m_Camp == 0) {
				//�з������赲
				d[index]->beEaten();
				deathChess.push(index);
				return true;
			}
		}
	}
	if (m_Camp == 0) {
		if (index != -1) {
			//��һ��������
			if (d[index]->m_Camp == 1) {
				//�з������赲
				d[index]->beEaten();
				deathChess.push(index);
				return true;
			}
		}
	}
	return false;
}
void Chess::beEaten() {
	if (m_Camp == 1) {
		cout << "�췽��" << m_Name << "���Ե���" << endl;
	}
	if (m_Camp == 0) {
		cout << "�ڷ���" << m_Name << "���Ե���" << endl;
	}
	isDead = true;
}