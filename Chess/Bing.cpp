#include "Bing.h"
Bing::Bing(int camp,int x) {
	if (camp == 0) {
		m_p = Point(x, 4);
		m_Name = "卒";
	}
	if (camp == 1) {
		m_p = Point(x, 7);
		m_Name = "兵";
	}
	m_Camp = camp;
}
bool Bing::walkRule(int offset_x, int offset_y) {
	Point next(m_p.m_x + offset_x, m_p.m_y + offset_y);
	int index = isHasChess(next.m_x, next.m_y);
	if (next.isOutRange()) {
		return false;
	}
	if (m_Camp == 1) {
		if (index != -1) {
			//下一步有棋子
			if (d[index]->m_Camp == 1) {
				//己方棋子阻挡
				return false;
			}
		}
	}
	if (m_Camp == 0) {
		if (index != -1) {
			//下一步有棋子
			if (d[index]->m_Camp == 0) {
				//己方棋子阻挡
				return false;
			}
		}
	}
	//m_p = next;
	return true;
}
bool Bing::findRoad() {
	//兵卒只能走一格，且不能后退，过河后可以横着走
	if (m_Camp == 1) {
		cout << "请选择兵的走法：" << endl;
		cout << "（当前可以走：";
		if (walkRule(1, 0) && m_p.isOutRange(1, 6, 9, 10)) {
			cout << "1.兵" << xNumToChar(m_p.m_x) << "平" << xNumToChar((m_p.m_x) + 1);
		}
		if (walkRule(-1, 0) && m_p.isOutRange(1, 6, 9, 10)) {
			cout << " 2.兵" << xNumToChar(m_p.m_x) << "平" << xNumToChar((m_p.m_x) - 1);
		}
		if (walkRule(0, -1)) {
			cout << " 3.兵" << xNumToChar(m_p.m_x) << "进" << yNumToChar(1);
		}
	}
	if (m_Camp == 0) {
		cout << "请选择卒的走法：" << endl;
		cout << "（当前可以走：";
		if (walkRule(1, 0) && m_p.isOutRange(1, 1, 9, 5)) {
			cout << "1.卒" << m_p.m_x << "平" << (m_p.m_x) + 1;
		}
		if (walkRule(-1, 0) && m_p.isOutRange(1, 1, 9, 5)) {
			cout << "   2.卒" << m_p.m_x << "平" << (m_p.m_x) - 1;
		}
		if (walkRule(0, 1)) {
			cout << "   3.卒" << m_p.m_x << "进" << 1;
		}
	}
	cout << " 0. 返回）" << endl;
	return chooseRoad();
}
bool Bing::chooseRoad() {
	int choose;
retry1:
	if (m_Camp == 1) {
		cin >> choose;
		switch (choose)
		{
		case 1: {
			if (walkRule(1, 0) && m_p.isOutRange(1, 6, 9, 10)) {
				this->move(1, 0);
				return true;
			}
		}
			  break;
		case 2: {
			if (walkRule(-1, 0) && m_p.isOutRange(1, 6, 9, 10)) {
				this->move(-1, 0);
				return true;
			}
		}
			  break;
		case 3: {
			if (walkRule(0, -1)) {
				this->move(0, -1);
				return true;
			}
		}
			  break;
		case 0: {
			return false;
		}
		default:
			break;
		}
	}
	if (m_Camp == 0) {
		cin >> choose;
		switch (choose)
		{
		case 1: {
			if (walkRule(1, 0) && m_p.isOutRange(1, 1, 9, 5)) {
				this->move(1, 0);
				return true;
			}
		}
			  break;
		case 2: {
			if (walkRule(-1, 0) && m_p.isOutRange(1, 1, 9, 5)) {
				this->move(-1, 0);
				return true;
			}
		}
			  break;
		case 3: {
			if (walkRule(0, 1)) {
				this->move(0, 1);
				return true;
			}
		}
		case 0: {
			return false;
		}
		default:
			  break;
		}
	}
	cout << "非法走棋！请重新输入" << endl;
	goto retry1;
}
	
