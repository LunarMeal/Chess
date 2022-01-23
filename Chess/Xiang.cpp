#include "Xiang.h"
Xiang::Xiang(int camp, int x) {
	if (camp == 0) {
		m_p = Point(x, 1);
		m_Name = "象";
	}
	if (camp == 1) {
		m_p = Point(x, 10);
		m_Name = "相";
	}
	m_Camp = camp;
}
Xiang::Xiang(int camp, int x, int y) {
	if (camp == 0) {
		m_p = Point(x, y);
		m_Name = "象";
	}
	if (camp == 1) {
		m_p = Point(x, y);
		m_Name = "相";
	}
	m_Camp = camp;
}
bool Xiang::walkRule(int offset_x, int offset_y) {
	Point next(m_p.m_x + offset_x, m_p.m_y + offset_y);
	int index = isHasChess(next.m_x, next.m_y);
	if (next.isOutRange()) {
		return false;
	}
	if (isBlock(next.m_x, next.m_y)) {
		return false;
	}
	if (m_Camp == 1) {
		if (next.isOutRange(1, 6, 9, 10)) {
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
		if (next.isOutRange(1, 1, 9, 5)) {
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
bool Xiang::findRoad() {
	//象可以飞田子格，但不能过河，同时会被卡象眼
	if (m_Camp == 1) {
		cout << "请选择相的走法：" << endl;
		cout << "（当前可以走：";
		if (walkRule(2, 2)) {
			cout << "1.相" << xNumToChar(m_p.m_x) << "退" << xNumToChar((m_p.m_x) + 2);
		}
		if (walkRule(-2, 2)) {
			cout << " 2.相" << xNumToChar(m_p.m_x) << "退" << xNumToChar((m_p.m_x) - 2);
		}
		if (walkRule(2, -2)) {
			cout << " 3.相" << xNumToChar(m_p.m_x) << "进" << xNumToChar((m_p.m_x) + 2);
		}
		if (walkRule(-2, -2)) {
			cout << " 4.相" << xNumToChar(m_p.m_x) << "进" << xNumToChar((m_p.m_x) - 2);
		}
	}
	if (m_Camp == 0) {
		cout << "请选择象的走法：" << endl;
		cout << "（当前可以走：";
		if (walkRule(2, 2)) {
			cout << "1.象" << m_p.m_x << "进" << (m_p.m_x) + 2;
		}
		if (walkRule(-2, 2)) {
			cout << "   2.象" << m_p.m_x << "进" << (m_p.m_x) - 2;
		}
		if (walkRule(2, -2)) {
			cout << "   3.象" << m_p.m_x << "退" << (m_p.m_x) + 2;
		}
		if (walkRule(-2, -2)) {
			cout << " 4.象" << xNumToChar(m_p.m_x) << "退" << (m_p.m_x) - 2;
		}
	}
	cout << " 0. 返回）" << endl;
	return chooseRoad();
}
bool Xiang::chooseRoad() {
	int choose;
retry:
	cin >> choose;
	switch (choose)
	{
	case 1: {
		if (walkRule(2, 2)) {
			this->move(2, 2);
			return true;
		}
	}
		break;
	case 2: {
		if (walkRule(-2, 2)) {
			this->move(-2, 2);
			return true;
		}
	}
			break;
	case 3: {
		if (walkRule(2, -2)) {
			this->move(2, -2);
			return true;
		}
	}
			break;
	case 4: {
		if (walkRule(-2, -2)) {
			this->move(-2, -2);
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
bool Xiang::isBlock(int x,int y) {
	int block_x = (m_p.m_x + x) / 2;
	int block_y = (m_p.m_y + y) / 2;
	int index = isHasChess(block_x, block_y);
	if (index != -1) {
		//象眼被卡住了
		return true;
	}
	else {
		return false;
	}
}