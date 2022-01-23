#include "Xiang.h"
Xiang::Xiang(int camp, int x) {
	if (camp == 0) {
		m_p = Point(x, 1);
		m_Name = "��";
	}
	if (camp == 1) {
		m_p = Point(x, 10);
		m_Name = "��";
	}
	m_Camp = camp;
}
Xiang::Xiang(int camp, int x, int y) {
	if (camp == 0) {
		m_p = Point(x, y);
		m_Name = "��";
	}
	if (camp == 1) {
		m_p = Point(x, y);
		m_Name = "��";
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
			//��һ��������
			if (d[index]->m_Camp == 1) {
				//���������赲
				return false;
			}
		}
	}
	if (m_Camp == 0) {
		if (next.isOutRange(1, 1, 9, 5)) {
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
bool Xiang::findRoad() {
	//����Է����Ӹ񣬵����ܹ��ӣ�ͬʱ�ᱻ������
	if (m_Camp == 1) {
		cout << "��ѡ������߷���" << endl;
		cout << "����ǰ�����ߣ�";
		if (walkRule(2, 2)) {
			cout << "1.��" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) + 2);
		}
		if (walkRule(-2, 2)) {
			cout << " 2.��" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) - 2);
		}
		if (walkRule(2, -2)) {
			cout << " 3.��" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) + 2);
		}
		if (walkRule(-2, -2)) {
			cout << " 4.��" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) - 2);
		}
	}
	if (m_Camp == 0) {
		cout << "��ѡ������߷���" << endl;
		cout << "����ǰ�����ߣ�";
		if (walkRule(2, 2)) {
			cout << "1.��" << m_p.m_x << "��" << (m_p.m_x) + 2;
		}
		if (walkRule(-2, 2)) {
			cout << "   2.��" << m_p.m_x << "��" << (m_p.m_x) - 2;
		}
		if (walkRule(2, -2)) {
			cout << "   3.��" << m_p.m_x << "��" << (m_p.m_x) + 2;
		}
		if (walkRule(-2, -2)) {
			cout << " 4.��" << xNumToChar(m_p.m_x) << "��" << (m_p.m_x) - 2;
		}
	}
	cout << " 0. ���أ�" << endl;
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
	cout << "�Ƿ����壡����������" << endl;
	goto retry;
}
bool Xiang::isBlock(int x,int y) {
	int block_x = (m_p.m_x + x) / 2;
	int block_y = (m_p.m_y + y) / 2;
	int index = isHasChess(block_x, block_y);
	if (index != -1) {
		//���۱���ס��
		return true;
	}
	else {
		return false;
	}
}