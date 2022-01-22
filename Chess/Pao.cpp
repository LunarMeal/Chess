#include "Pao.h"
Pao::Pao(int camp, int x) {
	if (camp == 0) {
		m_p = Point(x, 3);
		m_Name = "炮";
	}
	if (camp == 1) {
		m_p = Point(x, 8);
		m_Name = "砲";
	}
	m_Camp = camp;
	mp_temp = m_p;
}
bool Pao::walkRule(int offset_x, int offset_y) {
	Point next(m_p.m_x + offset_x, m_p.m_y + offset_y);
	int index = isHasChess(next.m_x, next.m_y);
	if (next.isOutRange()) {
		return false;
	}
	if (index != -1) {
		//下一步会被任何棋子阻挡
		return false;
	}
	//m_p = next;
	return true;
}
bool Pao::findRoad() {
	//砲/炮可以按直线走任意格，不受限制
	bool isEaten = false;
	isMoving = true;
	if (m_Camp == 1) {
		cout << "请通过wsad方向来控制砲的行走路线：" << endl;
		cout << "（按Y确定，按N返回，吃子后默认确定）" << endl;
		display();
		while (1) {
			if (KEY_DOWN('W')) {
				reset('W');
				if (walkRule(0, -1))
					move(0, -1);
				else {
					isEaten = Boom(0, -1);
					if (isEaten) {
						mp_temp = m_p;
						return true;
					}
					else {
						cout << "砲被挡住了！" << endl;
						Sleep(1000);
					}
				}
				return false;
				
			}
			if (KEY_DOWN('S')) {
				reset('S');
				if (walkRule(0, 1))
					move(0, 1);
				else {
					isEaten = Boom(0, 1);
					if (isEaten) {
						mp_temp = m_p;
						return true;
					}
					else {
						cout << "砲被挡住了！" << endl;
						Sleep(1000);
					}
				}
				return false;
			}
			if (KEY_DOWN('A')) {
				reset('A');
				if (walkRule(-1, 0))
					move(-1, 0);
				else {
					isEaten = Boom(-1, 0);
					if (isEaten) {
						mp_temp = m_p;
						return true;
					}
					else {
						cout << "砲被挡住了！" << endl;
						Sleep(1000);					
					}
				}
				return false;
			}
			if (KEY_DOWN('D')) {
				reset('D');
				if (walkRule(1, 0))
					move(1, 0);
				else {
					isEaten = Boom(1, 0);
					if (isEaten) {
						mp_temp = m_p;
						return true;
					}
					else {
						cout << "砲被挡住了！" << endl;
						Sleep(1000);
					}
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
			Sleep(60);
		}
		/*if (c2 == 72)return 'u';
		if (c2 == 80)return 'd';
		if (c2 == 75)return 'l';
		if (c2 == 77)return 'r';*/
	}
	if (m_Camp == 0) {
		cout << "请通过方向键来控制炮的行走路线：" << endl;
		cout << "（按Y确定，按N返回，吃子后默认确定）" << endl;
		display();
		isEaten = false;
		while (1) {
			if (KEY_DOWN('W')) {
				reset('W');
				if (walkRule(0, -1))
					move(0, -1);
				else {
					isEaten = Boom(0, -1);
					if (isEaten) {
						mp_temp = m_p;
						return true;
					}
					else {
						cout << "炮被挡住了！" << endl;
						Sleep(1000);
					}
				}
				return false;
			}
			if (KEY_DOWN('S')) {
				reset('S');
				if (walkRule(0, 1))
					move(0, 1);
				else {
					isEaten = Boom(0, 1);
					if (isEaten) {
						mp_temp = m_p;
						return true;
					}
					else {
						cout << "炮被挡住了！" << endl;
						Sleep(1000);
					}
				}
				return false;
			}
			if (KEY_DOWN('A')) {
				reset('A');
				if (walkRule(-1, 0))
					move(-1, 0);
				else {
					isEaten = Boom(-1, 0);
					if (isEaten) {
						mp_temp = m_p;
						return true;
					}
					else {
						cout << "炮被挡住了！" << endl;
						Sleep(1000);
					}
				}
				return false;
			}
			if (KEY_DOWN('D')) {
				reset('D');
				if (walkRule(1, 0))
					move(1, 0);
				else {
					isEaten = Boom(1, 0);
					if (isEaten) {
						mp_temp = m_p;
						return true;
					}
					else {
						cout << "炮被挡住了！" << endl;
						Sleep(1000);
					}
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
			Sleep(60);
		}
	}
}
void Pao::reset(char c) {
	if (key != c) {
		m_p = mp_temp;
		key = c;
	}
}
void Pao::display() {
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
bool Pao::Boom(int offset_x, int offset_y) {
	deque<Chess*> temp;
	char confirm;
	if (offset_x != 0) {
		for (int i = 0; i < d.size(); i++) {
			if (d[i]->getPos().m_y == this->m_p.m_y)
				if (!(d[i]->isDead))
					temp.push_back(d[i]);
		}
		if (offset_x < 0) {
			for (int x = m_p.m_x - 2; x > 0; x--) {
				for (int j = 0; j < temp.size(); j++) {
					if (x == temp[j]->getPos().m_x) {
						if (temp[j]->m_Camp!= m_Camp) {
							//阵营不同，炮打
							cout << "是否要将炮发射出去（1.确定/0.取消）？" << endl;
							while (1) {
								if (KEY_DOWN('1')) {
									move(x - m_p.m_x, 0);
									return true;
								}
								if (KEY_DOWN('0')) {
									return false;
								}
								Sleep(100);
							}
						}
						else {
							return false;
						}
					}
				}
			}
		}
		if (offset_x > 0) {
			for (int x = m_p.m_x + 2; x < 10; x++) {
				for (int j = 0; j < temp.size(); j++) {
					if (x == temp[j]->getPos().m_x) {
						if (temp[j]->m_Camp != m_Camp) {
							//阵营不同，炮打
							cout << "是否要将炮发射出去（1.确定/0.取消）？" << endl;
							while (1)
							{
								if (KEY_DOWN('1')) {
									move(x - m_p.m_x, 0);
									return true;
								}
								if (KEY_DOWN('0')) {
									return false;
								}
								Sleep(100);
							}
						}
						else {
							return false;
						}
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < d.size(); i++) {
			if (d[i]->getPos().m_x == this->m_p.m_x)
				if (!(d[i]->isDead))
					temp.push_back(d[i]);
		}
		if (offset_y < 0) {
			for (int y = m_p.m_y - 2; y > 0; y--) {
				for (int j = 0; j < temp.size(); j++) {
					if (y == temp[j]->getPos().m_y) {
						if (temp[j]->m_Camp != m_Camp) {
							//阵营不同，炮打
							cout << "是否要将炮发射出去（1.确定/0.取消）？" << endl;
							while (1) {
								if (KEY_DOWN('1')) {
									move(0, y - m_p.m_y);
									return true;
								}
								if (KEY_DOWN('0')) {
									return false;
								}
								Sleep(100);
							}
						}
						else {
							return false;
						}
					}
				}
			}
		}
		if (offset_y > 0) {
			for (int y = m_p.m_y + 2; y < 11; y++) {
				for (int j = 0; j < temp.size(); j++) {
					if (y == temp[j]->getPos().m_y) {
						if (temp[j]->m_Camp != m_Camp) {
							//阵营不同，炮打
							cout << "是否要将炮发射出去（1.确定/0.取消）？" << endl;
							while (1)
							{
								if (KEY_DOWN('1')) {
									move(0, y - m_p.m_y);
									return true;
								}
								if (KEY_DOWN('0')) {
									return false;
								}
								Sleep(100);
							}
						}
						else {
							return false;
						}
					}
				}
			}
		}
	}
	
}