#include "Shi.h"
extern stack<int> deathChess;
Shi::Shi(int camp, int x) {
	if (camp == 0) {
		m_p = Point(x, 1);
		m_Name = "ʿ";
	}
	if (camp == 1) {
		m_p = Point(x, 10);
		m_Name = "��";
	}
	m_Camp = camp;
}
Shi::Shi(int camp, int x, int y) {
	if (camp == 0) {
		m_p = Point(x, y);
		m_Name = "ʿ";
	}
	if (camp == 1) {
		m_p = Point(x, y);
		m_Name = "��";
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
			//��һ��������
			if (d[index]->m_Camp == 1) {
				//���������赲
				return false;
			}
		}
	}
	if (m_Camp == 0) {
		if (next.isOutRange(4, 1, 6, 3)) {
			return false;
		}
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
bool Shi::findRoad() {
	//ʿֻ��б����һ���Ҳ��ܳ��Ź�
	if (m_Camp == 1) {
		cout << "��ѡ���˵��߷���" << endl;
		cout << "����ǰ�����ߣ�";
		if (walkRule(1, 1)) {
			cout << "1.��" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) + 1);
		}
		if (walkRule(-1, 1)) {
			cout << " 2.��" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) - 1);
		}
		if (walkRule(1, -1)) {
			cout << " 3.��" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) + 1);
		}
		if (walkRule(-1, -1)) {
			cout << " 4.��" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) - 1);
		}
	}
	if (m_Camp == 0) {
		cout << "��ѡ��ʿ���߷���" << endl;
		cout << "����ǰ�����ߣ�";
		if (walkRule(1, 1)) {
			cout << "1.ʿ" << m_p.m_x << "��" << (m_p.m_x) + 1;
		}
		if (walkRule(-1, 1)) {
			cout << "   2.ʿ" << m_p.m_x << "��" << (m_p.m_x) - 1;
		}
		if (walkRule(1, -1)) {
			cout << "   3.ʿ" << m_p.m_x << "��" << (m_p.m_x) + 1;
		}
		if (walkRule(-1, -1)) {
			cout << " 4.ʿ" << xNumToChar(m_p.m_x) << "��" << (m_p.m_x) - 1;
		}
	}
	cout << " 0. ���أ�" << endl;
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
	cout << "�Ƿ����壡����������" << endl;
	goto retry;
}