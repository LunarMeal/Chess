#include "Ma.h"
Ma::Ma(int camp, int x) {
	if (camp == 0) {
		m_p = Point(x, 1);
		m_Name = "马";
	}
	if (camp == 1) {
		m_p = Point(x, 10);
		m_Name = "馬";
	}
	m_Camp = camp;
}
bool Ma::walkRule(int offset_x, int offset_y) {
	Point next(m_p.m_x + offset_x, m_p.m_y + offset_y);
	int index = isHasChess(next.m_x, next.m_y);
	if (next.isOutRange()) {
		return false;
	}
	if (isBlock(next.m_x, next.m_y)) {
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
bool Ma::findRoad() {
	//马走日字，活动范围不限制，但是会被蹩马腿
	if (m_Camp == 1) {
		cout << "请选择馬的走法：" << endl;
		cout << "（当前可以走：";
		if (walkRule(1, 2)) {
			cout << "1.馬" << xNumToChar(m_p.m_x) << "退" << xNumToChar((m_p.m_x) + 1);
		}
		if (walkRule(-1, 2)) {
			cout << " 2.馬" << xNumToChar(m_p.m_x) << "退" << xNumToChar((m_p.m_x) - 1);
		}
		if (walkRule(2, 1)) {
			cout << " 3.馬" << xNumToChar(m_p.m_x) << "退" << xNumToChar((m_p.m_x) + 2);
		}
		if (walkRule(-2, 1)) {
			cout << " 4.馬" << xNumToChar(m_p.m_x) << "退" << xNumToChar((m_p.m_x) - 2);
		}
		if (walkRule(1, -2)) {
			cout << " 5.馬" << xNumToChar(m_p.m_x) << "进" << xNumToChar((m_p.m_x) + 1);
		}
		if (walkRule(-1, -2)) {
			cout << " 6.馬" << xNumToChar(m_p.m_x) << "进" << xNumToChar((m_p.m_x) - 1);
		}
		if (walkRule(2, -1)) {
			cout << " 7.馬" << xNumToChar(m_p.m_x) << "进" << xNumToChar((m_p.m_x) + 2);
		}
		if (walkRule(-2, -1)) {
			cout << " 8.馬" << xNumToChar(m_p.m_x) << "进" << xNumToChar((m_p.m_x) - 2);
		}
	}
	if (m_Camp == 0) {
		cout << "请选择马的走法：" << endl;
		cout << "（当前可以走：";
		if (walkRule(1, 2)) {
			cout << "1.马" << m_p.m_x << "进" << (m_p.m_x) + 1;
		}
		if (walkRule(-1, 2)) {
			cout << " 2.马" << m_p.m_x << "进" << (m_p.m_x) - 1;
		}
		if (walkRule(2, 1)) {
			cout << " 3.马" << m_p.m_x << "进" << (m_p.m_x) + 2;
		}
		if (walkRule(-2, 1)) {
			cout << " 4.马" << m_p.m_x << "进" << (m_p.m_x) - 2;
		}
		if (walkRule(1, -2)) {
			cout << " 5.马" << m_p.m_x << "退" << (m_p.m_x) + 1;
		}
		if (walkRule(-1, -2)) {
			cout << " 6.马" << m_p.m_x << "退" << (m_p.m_x) - 1;
		}
		if (walkRule(2, -1)) {
			cout << " 7.马" << m_p.m_x << "退" << (m_p.m_x) + 2;
		}
		if (walkRule(-2, -1)) {
			cout << " 8.马" << m_p.m_x << "退" << (m_p.m_x) - 2;
		}
	}
	cout << " 0. 返回）" << endl;
	return chooseRoad();
}
bool Ma::chooseRoad() {
	int choose;
retry:
	cin >> choose;
	switch (choose)
	{
	case 1: {
		if (walkRule(1, 2)) {
			this->move(1, 2);
			return true;
		}
	}
		  break;
	case 2: {
		if (walkRule(-1, 2)) {
			this->move(-1, 2);
			return true;
		}
	}
		  break;
	case 3: {
		if (walkRule(2, 1)) {
			this->move(2, 1);
			return true;
		}
	}
		  break;
	case 4: {
		if (walkRule(-2, 1)) {
			this->move(-2, 1);
			return true;
		}
	}
		  break;
	case 5: {
		if (walkRule(1, -2)) {
			this->move(1, -2);
			return true;
		}
	}
		  break;
	case 6: {
		if (walkRule(-1, -2)) {
			this->move(-1, -2);
			return true;
		}
	}
		  break;
	case 7: {
		if (walkRule(2, -1)) {
			this->move(2, -1);
			return true;
		}
	}
		  break;
	case 8: {
		if (walkRule(-2, -1)) {
			this->move(-2, -1);
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
bool Ma::isBlock(int x, int y) {
	int block_x, block_y;
	int differ_x = x - m_p.m_x;
	int differ_y = y - m_p.m_y;
	if (abs(differ_x) == 2) {
		//如果马的方向是横着跳的
		block_x = m_p.m_x + differ_x / 2;
		block_y = m_p.m_y;
	}
	else {
		//如果马的方向是纵着跳的
		block_x = m_p.m_x;
		block_y = m_p.m_y + differ_y / 2;
	}
	int index = isHasChess(block_x, block_y);
	if (index != -1) {
		//马腿被蹩住了
		return true;
	}
	else {
		return false;
	}
}