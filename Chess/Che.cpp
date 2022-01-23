#include "Che.h"
Che::Che(int camp, int x) {
	if (camp == 0) {
		m_p = Point(x, 1);
		m_Name = "车";
	}
	if (camp == 1) {
		m_p = Point(x, 10);
		m_Name = "車";
	}
	m_Camp = camp;
	mp_temp = m_p;
}
Che::Che(int camp, int x, int y) {
	if (camp == 0) {
		m_p = Point(x, y);
		m_Name = "车";
	}
	if (camp == 1) {
		m_p = Point(x, y);
		m_Name = "車";
	}
	m_Camp = camp;
	mp_temp = m_p;
}
bool Che::walkRule(int offset_x, int offset_y) {
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
bool Che::findRoad() {
	//車/车可以按直线走任意格，不受限制
	bool isEaten = false;
	isMoving = true;
	if (m_Camp == 1) {
		cout << "请通过wsad方向来控制車的行走路线：" << endl;
		cout << "（按Y确定，按N返回，吃子后默认确定）" << endl;
		display();
		while (1) {
			if (KEY_DOWN('W')) {
				reset('W');
				if (walkRule(0, -1))
					isEaten = move(0, -1);
				else {
					cout << "車被挡住了！" << endl;
					Sleep(1000);
				}
				if (isEaten) {
					mp_temp = m_p;
					return true;
				}
				return false;
			}
			if (KEY_DOWN('S')) {
				reset('S');
				if (walkRule(0, 1))
					isEaten = move(0, 1);
				else {
					cout << "車被挡住了！" << endl;
					Sleep(1000);
				}
				if (isEaten) {
					mp_temp = m_p;
					return true;
				}
				return false;
			}
			if (KEY_DOWN('A')) {
				reset('A');
				if (walkRule(-1, 0))
					isEaten = move(-1, 0);
				else {
					cout << "車被挡住了！" << endl;
					Sleep(1000);
				}
				if (isEaten) {
					mp_temp = m_p;
					return true;
				}
				return false;
			}
			if (KEY_DOWN('D')) {
				reset('D');
				if (walkRule(1, 0))
					isEaten = move(1, 0);
				else {
					cout << "車被挡住了！" << endl;
					Sleep(1000);
				}
				if (isEaten) {
					mp_temp = m_p;
					return true;
				}
				return false;
			}
			if (KEY_DOWN('Y')) {
				//完成
				if (m_p != mp_temp) {
					mp_temp = m_p;
					return true;
				}
				else {
					cout << "您必须要走一步棋！" << endl;
					Sleep(1000);
					return false;
				}

			}
			if (KEY_DOWN('N')) {
				//取消
				m_p = mp_temp;
				isMoving = false;
				return false;
			}
			Sleep(100);
		}
		/*if (c2 == 72)return 'u';
		if (c2 == 80)return 'd';
		if (c2 == 75)return 'l';
		if (c2 == 77)return 'r';*/
	}
	if (m_Camp == 0) {
		cout << "请通过方向键来控制车的行走路线：" << endl;
		cout << "（按Y确定，按N返回，吃子后默认确定）" << endl;
		display();
		while (1) {
			if (KEY_DOWN('W')) {
				reset('W');
				if (walkRule(0, -1))
					isEaten = move(0, -1);
				else {
					cout << "车被挡住了！" << endl;
					Sleep(1000);
				}
				if (isEaten) {
					mp_temp = m_p;
					return true;
				}
				return false;
			}
			if (KEY_DOWN('S')) {
				reset('S');
				if (walkRule(0, 1))
					isEaten = move(0, 1);
				else {
					cout << "车被挡住了！" << endl;
					Sleep(1000);
				}
				if (isEaten) {
					mp_temp = m_p;
					return true;
				}
				return false;
			}
			if (KEY_DOWN('A')) {
				reset('A');
				if (walkRule(-1, 0))
					isEaten = move(-1, 0);
				else {
					cout << "车被挡住了！" << endl;
					Sleep(1000);
				}
				if (isEaten) {
					mp_temp = m_p;
					return true;
				}
				return false;
			}
			if (KEY_DOWN('D')) {
				reset('D');
				if (walkRule(1, 0))
					isEaten = move(1, 0);
				else {
					cout << "车被挡住了！" << endl;
					Sleep(1000);
				}
				if (isEaten) {
					mp_temp = m_p;
					return true;
				}
				return false;
			}
			if (KEY_DOWN('Y')) {
				//完成
				if (m_p != mp_temp) {
					mp_temp = m_p;
					return true;
				}
				else {
					cout << "您必须要走一步棋！" << endl;
					Sleep(1000);
					return false;
				}
			}
			if (KEY_DOWN('N')) {
				//取消
				m_p = mp_temp;
				isMoving = false;
				return false;
			}
			Sleep(100);
		}
	}
}
void Che::reset(char c) {
	if (key != c) {
		m_p = mp_temp;
		key = c;
	}
}
void Che::display() {
	cout << "当前招法：";
	if (m_p != mp_temp) {
		if (m_Camp == 1) {
			cout << m_Name << xNumToChar(mp_temp.m_x);
			if (mp_temp.m_y == m_p.m_y) {
				cout << "平" << xNumToChar(m_p.m_x);
			}
			else {
				int offset_y = m_p.m_y - mp_temp.m_y;
				if (offset_y < 0) {
					cout << "进" << yNumToChar(abs(offset_y));
				}
				else {
					cout << "退" << yNumToChar(offset_y);
				}
			}
		}
		if (m_Camp == 0) {
			cout << m_Name << mp_temp.m_x;
			if (mp_temp.m_y == m_p.m_y) {
				cout << "平" << m_p.m_x;
			}
			else {
				int offset_y = m_p.m_y - mp_temp.m_y;
				if (offset_y < 0) {
					cout << "退" << abs(offset_y);
				}
				else {
					cout << "进" << offset_y;
				}
			}
		}
	}
	cout << endl;
}