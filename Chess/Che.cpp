#include "Che.h"
Che::Che(int camp, int x) {
	if (camp == 0) {
		m_p = Point(x, 1);
		m_Name = "��";
	}
	if (camp == 1) {
		m_p = Point(x, 10);
		m_Name = "܇";
	}
	m_Camp = camp;
	mp_temp = m_p;
}
Che::Che(int camp, int x, int y) {
	if (camp == 0) {
		m_p = Point(x, y);
		m_Name = "��";
	}
	if (camp == 1) {
		m_p = Point(x, y);
		m_Name = "܇";
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
			//��һ��������
			if (d[index]->m_Camp == 1) {
				//���������赲
				return false;
			}
		}
	}
	if (m_Camp == 0) {
		if (index != -1) {
			//��һ��������
			if (d[index]->m_Camp == 0) {
				//���������赲
				return false;
			}
		}
	}
	//m_p = next;
	return true;
}
bool Che::findRoad() {
	//܇/�����԰�ֱ��������񣬲�������
	bool isEaten = false;
	isMoving = true;
	if (m_Camp == 1) {
		cout << "��ͨ��wsad����������܇������·�ߣ�" << endl;
		cout << "����Yȷ������N���أ����Ӻ�Ĭ��ȷ����" << endl;
		display();
		while (1) {
			if (KEY_DOWN('W')) {
				reset('W');
				if (walkRule(0, -1))
					isEaten = move(0, -1);
				else {
					cout << "܇����ס�ˣ�" << endl;
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
					cout << "܇����ס�ˣ�" << endl;
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
					cout << "܇����ס�ˣ�" << endl;
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
					cout << "܇����ס�ˣ�" << endl;
					Sleep(1000);
				}
				if (isEaten) {
					mp_temp = m_p;
					return true;
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
			Sleep(100);
		}
		/*if (c2 == 72)return 'u';
		if (c2 == 80)return 'd';
		if (c2 == 75)return 'l';
		if (c2 == 77)return 'r';*/
	}
	if (m_Camp == 0) {
		cout << "��ͨ������������Ƴ�������·�ߣ�" << endl;
		cout << "����Yȷ������N���أ����Ӻ�Ĭ��ȷ����" << endl;
		display();
		while (1) {
			if (KEY_DOWN('W')) {
				reset('W');
				if (walkRule(0, -1))
					isEaten = move(0, -1);
				else {
					cout << "������ס�ˣ�" << endl;
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
					cout << "������ס�ˣ�" << endl;
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
					cout << "������ס�ˣ�" << endl;
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
					cout << "������ס�ˣ�" << endl;
					Sleep(1000);
				}
				if (isEaten) {
					mp_temp = m_p;
					return true;
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