#include "Pao.h"
Pao::Pao(int camp, int x) {
	if (camp == 0) {
		m_p = Point(x, 3);
		m_Name = "��";
	}
	if (camp == 1) {
		m_p = Point(x, 8);
		m_Name = "�h";
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
		//��һ���ᱻ�κ������赲
		return false;
	}
	//m_p = next;
	return true;
}
bool Pao::findRoad() {
	//�h/�ڿ��԰�ֱ��������񣬲�������
	bool isEaten = false;
	isMoving = true;
	if (m_Camp == 1) {
		cout << "��ͨ��wsad���������Ƴh������·�ߣ�" << endl;
		cout << "����Yȷ������N���أ����Ӻ�Ĭ��ȷ����" << endl;
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
						cout << "�h����ס�ˣ�" << endl;
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
						cout << "�h����ס�ˣ�" << endl;
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
						cout << "�h����ס�ˣ�" << endl;
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
						cout << "�h����ס�ˣ�" << endl;
						Sleep(1000);
					}
				}
				return false;
			}
			if (KEY_DOWN('Y')) {
				//���
				if (m_p != mp_temp) {
					mp_temp = m_p;
					return true;
				}
				else {
					cout << "������Ҫ��һ���壡" << endl;
					Sleep(1000);
					return false;
				}

			}
			if (KEY_DOWN('N')) {
				//ȡ��
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
		cout << "��ͨ��������������ڵ�����·�ߣ�" << endl;
		cout << "����Yȷ������N���أ����Ӻ�Ĭ��ȷ����" << endl;
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
						cout << "�ڱ���ס�ˣ�" << endl;
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
						cout << "�ڱ���ס�ˣ�" << endl;
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
						cout << "�ڱ���ס�ˣ�" << endl;
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
						cout << "�ڱ���ס�ˣ�" << endl;
						Sleep(1000);
					}
				}
				return false;
			}
			if (KEY_DOWN('Y')) {
				//���
				if (m_p != mp_temp) {
					mp_temp = m_p;
					return true;
				}
				else {
					cout << "������Ҫ��һ���壡" << endl;
					Sleep(1000);
					return false;
				}
			}
			if (KEY_DOWN('N')) {
				//ȡ��
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
	cout << "��ǰ�з���";
	if (m_p != mp_temp) {
		if (m_Camp == 1) {
			cout << m_Name << xNumToChar(mp_temp.m_x);
			if (mp_temp.m_y == m_p.m_y) {
				cout << "ƽ" << xNumToChar(m_p.m_x);
			}
			else {
				int offset_y = m_p.m_y - mp_temp.m_y;
				if (offset_y < 0) {
					cout << "��" << yNumToChar(abs(offset_y));
				}
				else {
					cout << "��" << yNumToChar(offset_y);
				}
			}
		}
		if (m_Camp == 0) {
			cout << m_Name << mp_temp.m_x;
			if (mp_temp.m_y == m_p.m_y) {
				cout << "ƽ" << m_p.m_x;
			}
			else {
				int offset_y = m_p.m_y - mp_temp.m_y;
				if (offset_y < 0) {
					cout << "��" << abs(offset_y);
				}
				else {
					cout << "��" << offset_y;
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
							//��Ӫ��ͬ���ڴ�
							cout << "�Ƿ�Ҫ���ڷ����ȥ��1.ȷ��/0.ȡ������" << endl;
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
							//��Ӫ��ͬ���ڴ�
							cout << "�Ƿ�Ҫ���ڷ����ȥ��1.ȷ��/0.ȡ������" << endl;
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
							//��Ӫ��ͬ���ڴ�
							cout << "�Ƿ�Ҫ���ڷ����ȥ��1.ȷ��/0.ȡ������" << endl;
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
							//��Ӫ��ͬ���ڴ�
							cout << "�Ƿ�Ҫ���ڷ����ȥ��1.ȷ��/0.ȡ������" << endl;
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