#include "Shi.h"
extern stack<int> deathChess;
Shi::Shi(int camp, int x) {
	if (camp == 0) {
		m_p = Point(x, 1);
		m_Name = "士";
	}
	if (camp == 1) {
		m_p = Point(x, 10);
		m_Name = "仕";
	}
	m_Camp = camp;
}
Shi::Shi(int camp, int x, int y) {
	if (camp == 0) {
		m_p = Point(x, y);
		m_Name = "士";
	}
	if (camp == 1) {
		m_p = Point(x, y);
		m_Name = "仕";
	}
	m_Camp = camp;
}
bool Shi::walkRule(int offset_x, int offset_y) {
	Point next(m_p.m_x + offset_x, m_p.m_y + offset_y);
	int index = isHasChess(next.m_x, next.m_y);
	if (next.isOutRange()) {
		return false;
	}
	if (m_Camp == 1) {
		if (next.isOutRange(4, 8, 6, 10)) {
			return false;
		}
		if (index != -1) {
			//下一步有棋子
			if (d[index]->m_Camp == 1) {
				//己方棋子阻挡
				return false;
			}
		}
	}
	if (m_Camp == 0) {
		if (next.isOutRange(4, 1, 6, 3)) {
			return false;
		}
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
bool Shi::findRoad() {
	//士只能斜着走一格，且不能出九宫
	if (m_Camp == 1) {
		cout << "请选择仕的走法：" << endl;
		cout << "（当前可以走：";
		if (walkRule(1, 1)) {
			cout << "1.仕" << xNumToChar(m_p.m_x) << "退" << xNumToChar((m_p.m_x) + 1);
		}
		if (walkRule(-1, 1)) {
			cout << " 2.仕" << xNumToChar(m_p.m_x) << "退" << xNumToChar((m_p.m_x) - 1);
		}
		if (walkRule(1, -1)) {
			cout << " 3.仕" << xNumToChar(m_p.m_x) << "进" << xNumToChar((m_p.m_x) + 1);
		}
		if (walkRule(-1, -1)) {
			cout << " 4.仕" << xNumToChar(m_p.m_x) << "进" << xNumToChar((m_p.m_x) - 1);
		}
	}
	if (m_Camp == 0) {
		cout << "请选择士的走法：" << endl;
		cout << "（当前可以走：";
		if (walkRule(1, 1)) {
			cout << "1.士" << m_p.m_x << "进" << (m_p.m_x) + 1;
		}
		if (walkRule(-1, 1)) {
			cout << "   2.士" << m_p.m_x << "进" << (m_p.m_x) - 1;
		}
		if (walkRule(1, -1)) {
			cout << "   3.士" << m_p.m_x << "退" << (m_p.m_x) + 1;
		}
		if (walkRule(-1, -1)) {
			cout << " 4.士" << xNumToChar(m_p.m_x) << "退" << (m_p.m_x) - 1;
		}
	}
	cout << " 0. 返回）" << endl;
	return chooseRoad();
}
bool Shi::chooseRoad() {
	int choose;
retry:

	cin >> choose;
	switch (choose)
	{
	case 1: {
		if (walkRule(1, 1)) {
			if(!this->move(1, 1))
				deathChess.push(-1);
			return true;
		}
	}
		  break;
	case 2: {
		if (walkRule(-1, 1)) {
			if(!this->move(-1, 1))
				deathChess.push(-1);
			return true;
		}
	}
		  break;
	case 3: {
		if (walkRule(1, -1)) {
			if(!this->move(1, -1))
				deathChess.push(-1);
			return true;
		}
	}
		  break;
	case 4: {
		if (walkRule(-1, -1)) {
			if(!this->move(-1, -1))
				deathChess.push(-1);
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
	cout << "非法走棋！请重新输入" << endl;
	goto retry;
}