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
		return "九";
	case 2:
		return "八";
	case 3:
		return "七";
	case 4:
		return "六";
	case 5:
		return "五";
	case 6:
		return "四";
	case 7:
		return "三";
	case 8:
		return "二";
	case 9:
		return "一";
	default:
		break;
	}
}
string Chess::xNumToChar(unsigned int num) {
	switch (num)
	{
	case 1:
		return "九";
	case 2:
		return "八";
	case 3:
		return "七";
	case 4:
		return "六";
	case 5:
		return "五";
	case 6:
		return "四";
	case 7:
		return "三";
	case 8:
		return "二";
	case 9:
		return "一";
	default:
		break;
	}
}
string Chess::yNumToChar(unsigned int num) {
	switch (num)
	{
	case 1:
		return "一";
	case 2:
		return "二";
	case 3:
		return "三";
	case 4:
		return "四";
	case 5:
		return "五";
	case 6:
		return "六";
	case 7:
		return "七";
	case 8:
		return "八";
	case 9:
		return "九";
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
			//下一步有棋子
			if (d[index]->m_Camp == 0) {
				//敌方棋子阻挡
				d[index]->beEaten();
				deathChess.push(index);
				return true;
			}
		}
	}
	if (m_Camp == 0) {
		if (index != -1) {
			//下一步有棋子
			if (d[index]->m_Camp == 1) {
				//敌方棋子阻挡
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
		cout << "红方的" << m_Name << "被吃掉了" << endl;
	}
	if (m_Camp == 0) {
		cout << "黑方的" << m_Name << "被吃掉了" << endl;
	}
	isDead = true;
}