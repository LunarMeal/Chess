#include "Ma.h"
Ma::Ma(int camp, int x) {
	if (camp == 0) {
		m_p = Point(x, 1);
		m_Name = "��";
	}
	if (camp == 1) {
		m_p = Point(x, 10);
		m_Name = "�R";
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
bool Ma::findRoad() {
	//�������֣����Χ�����ƣ����ǻᱻ������
	if (m_Camp == 1) {
		cout << "��ѡ���R���߷���" << endl;
		cout << "����ǰ�����ߣ�";
		if (walkRule(1, 2)) {
			cout << "1.�R" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) + 1);
		}
		if (walkRule(-1, 2)) {
			cout << " 2.�R" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) - 1);
		}
		if (walkRule(2, 1)) {
			cout << " 3.�R" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) + 2);
		}
		if (walkRule(-2, 1)) {
			cout << " 4.�R" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) - 2);
		}
		if (walkRule(1, -2)) {
			cout << " 5.�R" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) + 1);
		}
		if (walkRule(-1, -2)) {
			cout << " 6.�R" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) - 1);
		}
		if (walkRule(2, -1)) {
			cout << " 7.�R" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) + 2);
		}
		if (walkRule(-2, -1)) {
			cout << " 8.�R" << xNumToChar(m_p.m_x) << "��" << xNumToChar((m_p.m_x) - 2);
		}
	}
	if (m_Camp == 0) {
		cout << "��ѡ������߷���" << endl;
		cout << "����ǰ�����ߣ�";
		if (walkRule(1, 2)) {
			cout << "1.��" << m_p.m_x << "��" << (m_p.m_x) + 1;
		}
		if (walkRule(-1, 2)) {
			cout << " 2.��" << m_p.m_x << "��" << (m_p.m_x) - 1;
		}
		if (walkRule(2, 1)) {
			cout << " 3.��" << m_p.m_x << "��" << (m_p.m_x) + 2;
		}
		if (walkRule(-2, 1)) {
			cout << " 4.��" << m_p.m_x << "��" << (m_p.m_x) - 2;
		}
		if (walkRule(1, -2)) {
			cout << " 5.��" << m_p.m_x << "��" << (m_p.m_x) + 1;
		}
		if (walkRule(-1, -2)) {
			cout << " 6.��" << m_p.m_x << "��" << (m_p.m_x) - 1;
		}
		if (walkRule(2, -1)) {
			cout << " 7.��" << m_p.m_x << "��" << (m_p.m_x) + 2;
		}
		if (walkRule(-2, -1)) {
			cout << " 8.��" << m_p.m_x << "��" << (m_p.m_x) - 2;
		}
	}
	cout << " 0. ���أ�" << endl;
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
	cout << "�Ƿ����壡����������" << endl;
	goto retry;
}
bool Ma::isBlock(int x, int y) {
	int block_x, block_y;
	int differ_x = x - m_p.m_x;
	int differ_y = y - m_p.m_y;
	if (abs(differ_x) == 2) {
		//�����ķ����Ǻ�������
		block_x = m_p.m_x + differ_x / 2;
		block_y = m_p.m_y;
	}
	else {
		//�����ķ�������������
		block_x = m_p.m_x;
		block_y = m_p.m_y + differ_y / 2;
	}
	int index = isHasChess(block_x, block_y);
	if (index != -1) {
		//���ȱ���ס��
		return true;
	}
	else {
		return false;
	}
}