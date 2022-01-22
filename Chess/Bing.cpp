#include "Bing.h"
Bing::Bing(int camp,int x) {
	if (camp == 0) {
		m_p = Point(x, 4);
		m_Name = "��";
	}
	if (camp == 1) {
		m_p = Point(x, 7);
		m_Name = "��";
	}
	m_Camp = camp;
}
bool Bing::walkRule(int offset_x, int offset_y) {
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
bool Bing::findRoad() {
	//����ֻ����һ���Ҳ��ܺ��ˣ����Ӻ���Ժ�����
	if (m_Camp == 1) {
		cout << "��ѡ������߷���" << endl;
		cout << "����ǰ�����ߣ�";
		if (walkRule(1, 0) && m_p.isOutRange(1, 6, 9, 10)) {
			cout << "1.��" << xNumToChar(m_p.m_x) << "ƽ" << xNumToChar((m_p.m_x) + 1);
		}
		if (walkRule(-1, 0) && m_p.isOutRange(1, 6, 9, 10)) {
			cout << " 2.��" << xNumToChar(m_p.m_x) << "ƽ" << xNumToChar((m_p.m_x) - 1);
		}
		if (walkRule(0, -1)) {
			cout << " 3.��" << xNumToChar(m_p.m_x) << "��" << yNumToChar(1);
		}
	}
	if (m_Camp == 0) {
		cout << "��ѡ������߷���" << endl;
		cout << "����ǰ�����ߣ�";
		if (walkRule(1, 0) && m_p.isOutRange(1, 1, 9, 5)) {
			cout << "1.��" << m_p.m_x << "ƽ" << (m_p.m_x) + 1;
		}
		if (walkRule(-1, 0) && m_p.isOutRange(1, 1, 9, 5)) {
			cout << "   2.��" << m_p.m_x << "ƽ" << (m_p.m_x) - 1;
		}
		if (walkRule(0, 1)) {
			cout << "   3.��" << m_p.m_x << "��" << 1;
		}
	}
	cout << " 0. ���أ�" << endl;
	return chooseRoad();
}
bool Bing::chooseRoad() {
	int choose;
retry1:
	if (m_Camp == 1) {
		cin >> choose;
		switch (choose)
		{
		case 1: {
			if (walkRule(1, 0) && m_p.isOutRange(1, 6, 9, 10)) {
				this->move(1, 0);
				return true;
			}
		}
			  break;
		case 2: {
			if (walkRule(-1, 0) && m_p.isOutRange(1, 6, 9, 10)) {
				this->move(-1, 0);
				return true;
			}
		}
			  break;
		case 3: {
			if (walkRule(0, -1)) {
				this->move(0, -1);
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
	}
	if (m_Camp == 0) {
		cin >> choose;
		switch (choose)
		{
		case 1: {
			if (walkRule(1, 0) && m_p.isOutRange(1, 1, 9, 5)) {
				this->move(1, 0);
				return true;
			}
		}
			  break;
		case 2: {
			if (walkRule(-1, 0) && m_p.isOutRange(1, 1, 9, 5)) {
				this->move(-1, 0);
				return true;
			}
		}
			  break;
		case 3: {
			if (walkRule(0, 1)) {
				this->move(0, 1);
				return true;
			}
		}
		case 0: {
			return false;
		}
		default:
			  break;
		}
	}
	cout << "�Ƿ����壡����������" << endl;
	goto retry1;
}
	
