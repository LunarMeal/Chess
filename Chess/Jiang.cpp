#include "Jiang.h"
#include "Layout.h"
extern stack<int> deathChess;
Jiang::Jiang(int camp) {
	if (camp == 0) {
		m_p = Point(5, 1);
		m_Name = "将";
	}
	if (camp == 1) {
		m_p = Point(5, 10);
		m_Name = "帅";
	}
	m_Camp = camp;
}
Jiang::Jiang(int camp,int x,int y) {
	if (camp == 0) {
		m_p = Point(x, y);
		m_Name = "将";
	}
	if (camp == 1) {
		m_p = Point(x, y);
		m_Name = "帅";
	}
	m_Camp = camp;
}
int Jiang::isFaced() {
	deque<Chess*> temp;
	for (int i = 0; i < d.size(); i++) {
		if (d[i]->getPos().m_x == this->m_p.m_x)
			if(!(d[i]->isDead))
				temp.push_back(d[i]);
	}
	if (m_Camp == 1) {
		for (int y = m_p.m_y - 1; y > 0; y--) {
			for (int j = 0; j < temp.size(); j++) {
				if (y == temp[j]->getPos().m_y) {					
					if ((temp[j]->m_Name).compare("将")==0) {
						return y - (m_p.m_y);
					}
					else {
						return 0;
					}
				}
			}
		}
	}
	if (m_Camp == 0) {
		for (int y = m_p.m_y + 1; y < 11; y++) {
			for (int j = 0; j < temp.size(); j++) {
				if (y == temp[j]->getPos().m_y) {
					if ((temp[j]->m_Name).compare("帅") == 0) {
						return y - (m_p.m_y);
					}
					else {
						return 0;
					}
				}
			}
		}
	}
	
}
bool Jiang::walkRule(int offset_x,int offset_y) {
	Point next(m_p.m_x+offset_x,m_p.m_y+offset_y);
	int index=isHasChess(next.m_x, next.m_y);
	if (next.isOutRange()) {
		return false;
	}
	if (m_Camp == 1) {
		if (next.isOutRange(4, 8, 6, 10)) {
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
		if (next.isOutRange(4, 1, 6, 3)) {
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
bool Jiang::findRoad() {
	//将帅只能走一格
	int offset_y= isFaced();
	if (m_Camp == 1) {
		cout << "请选择帅的走法：" << endl;
		cout << "（当前可以走：" ;
		if (walkRule(1, 0)) {
			cout << "1.帅" << xNumToChar(m_p.m_x) << "平" << xNumToChar((m_p.m_x) + 1);
		}
		if (walkRule(-1, 0)) {
			cout << " 2.帅" << xNumToChar(m_p.m_x) << "平" << xNumToChar((m_p.m_x) - 1);
		}
		if (walkRule(0, -1)) {
			cout << " 3.帅" << xNumToChar(m_p.m_x) << "进" << yNumToChar(1);
		}
		if (walkRule(0, 1)) {
			cout << " 4.帅" << xNumToChar(m_p.m_x) << "退" << yNumToChar(1);
		}
		if (offset_y!=0) {
			cout << " 5.帅"<< xNumToChar(m_p.m_x) << "进" << yNumToChar(abs(offset_y)) << "<飞将>";
		}
	}
	if (m_Camp == 0) {
		cout << "请选择将的走法：" << endl;
		cout << "（当前可以走：";
		if (walkRule(1, 0)) {
			cout << "1.将" << m_p.m_x << "平" << (m_p.m_x) + 1;
		}
		if (walkRule(-1, 0)) {
			cout << "   2.将" << m_p.m_x << "平" << (m_p.m_x) - 1;
		}
		if (walkRule(0, -1)) {
			cout << "   3.将" << m_p.m_x << "退" << 1;
		}
		if (walkRule(0, 1)) {
			cout << "   4.将" << m_p.m_x << "进" << 1;
		}
		if (offset_y != 0) {
			cout << "   5.将" << m_p.m_x << "进" << abs(offset_y)<<"<飞将>";
		}
	}
	cout << " 0. 返回）" << endl;
	return chooseRoad(offset_y);
}
bool Jiang::chooseRoad(int offset_y) {
	int choose;
	retry1:
	cin >> choose;
	switch (choose)
	{
	case 1: {
		if (walkRule(1, 0)) {
			if (!this->move(1, 0))
				deathChess.push(-1);
			return true;
		}
	}
		  break;
	case 2: {
		if (walkRule(-1, 0)) {
			if (!this->move(-1, 0))
				deathChess.push(-1);
			return true;
		}
	}
		  break;
	case 3: {
		if (walkRule(0, -1)) {
			if (!this->move(0, -1))
				deathChess.push(-1);
			return true;
		}
	}
		  break;
	case 4: {
		if (walkRule(0, 1)) {
			if (!this->move(0, 1))
				deathChess.push(-1);
			return true;
		}
	}
		  break;
	case 5: {
		if (offset_y != 0) {
			this->move(0, offset_y);
			return true;
		}
	}
	case 0: {
		return false;
	}
		  break;
	default:
		break;
	}
	cout << "非法走棋！请重新输入" << endl;
	goto retry1;
}
bool Jiang::isJiang() {
	vector<string> j_chess;
	vector<int> bj_chess;
	vector<int> mj_chess;
	if (m_Camp == 1) {
		if (isFaced() != 0) {
			//判断是否对将
			j_chess.push_back("将");
		}
		//判断是否被卒将
		bj_chess.push_back(isHasChess(m_p.m_x + 1, m_p.m_y));
		bj_chess.push_back(isHasChess(m_p.m_x - 1, m_p.m_y));
		bj_chess.push_back(isHasChess(m_p.m_x, m_p.m_y - 1));
		for (int i = 0; i < 3; i++) {
			if (bj_chess[i] != -1) {
				if (d[bj_chess[i]]->m_Name == "卒") {
					j_chess.push_back("卒");
				}
			}
		}
		//===================================================//
		//判断是否被马将
		if (!(Point(m_p.m_x + 2, m_p.m_y + 1).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x + 2, m_p.m_y + 1));
		}
		if (!(Point(m_p.m_x + 2, m_p.m_y - 1).isOutRange())){
			mj_chess.push_back(isHasChess(m_p.m_x + 2, m_p.m_y - 1));
		}
		if (!(Point(m_p.m_x - 2, m_p.m_y + 1).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x - 2, m_p.m_y + 1));
		}
		if (!(Point(m_p.m_x - 2, m_p.m_y - 1).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x - 2, m_p.m_y - 1));
		}
		if (!(Point(m_p.m_x + 1, m_p.m_y + 2).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x + 1, m_p.m_y + 2));
		}
		if (!(Point(m_p.m_x + 1, m_p.m_y - 2).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x + 1, m_p.m_y - 2));
		}
		if (!(Point(m_p.m_x - 1, m_p.m_y + 2).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x - 1, m_p.m_y + 2));
		}
		if (!(Point(m_p.m_x - 1, m_p.m_y - 2).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x - 1, m_p.m_y - 2));
		}
		for (int i = 0; i < mj_chess.size(); i++) {
			if (mj_chess[i] != -1) {
				if (d[mj_chess[i]]->m_Name == "马") {
					if (!(d[mj_chess[i]]->isBlock(m_p.m_x, m_p.m_y))) {
						j_chess.push_back("马");
					}
				}
			}
		}
		//===================================================//
		//判断是否被车将，四个方向全做判断
		deque<Chess*> temp;
		int flag;
		for (int i = 0; i < d.size(); i++) {
			if (d[i]->getPos().m_y == this->m_p.m_y || d[i]->getPos().m_x == this->m_p.m_x)
				if (!(d[i]->isDead))
					temp.push_back(d[i]);
		}
		flag = 0;
		for (int x = m_p.m_x - 1; x > 0; x--) {
			for (int j = 0; j < temp.size(); j++) {
				if (flag == 1) {
					if (x == temp[j]->getPos().m_x) {
						flag++;
						if (temp[j]->m_Name == "炮") {
							j_chess.push_back("炮");
						}
					}
				}
				if (flag == 0) {
					if (x == temp[j]->getPos().m_x) {
						flag++;
						if (temp[j]->m_Name == "车") {
							j_chess.push_back("车");
						}
					}
				}
			}
		}
		flag = 0;
		for (int x = m_p.m_x + 1; x < 10; x++) {
			for (int j = 0; j < temp.size(); j++) {
				if (flag == 1) {
					if (x == temp[j]->getPos().m_x) {
						flag++;
						if (temp[j]->m_Name == "炮") {
							j_chess.push_back("炮");
						}
					}
				}
				if (flag == 0) {
					if (x == temp[j]->getPos().m_x) {
						flag++;
						if (temp[j]->m_Name == "车") {
							j_chess.push_back("车");
						}
					}
				}
			}
		}
		flag = 0;
		for (int y = m_p.m_y - 1; y > 0; y--) {
			for (int j = 0; j < temp.size(); j++) {
				if (flag == 1) {
					if (y == temp[j]->getPos().m_y) {
						flag++;
						if (temp[j]->m_Name == "炮") {
							j_chess.push_back("炮");
						}
					}
				}
				if (flag == 0) {
					if (y == temp[j]->getPos().m_y) {
						flag ++;
						if (temp[j]->m_Name == "车") {
							j_chess.push_back("车");
						}
					}
				}
			}
		}
		flag = 0;
		for (int y = m_p.m_y + 1; y < 11; y++) {
			for (int j = 0; j < temp.size(); j++) {
				if (flag == 1) {
					if (y == temp[j]->getPos().m_y) {
						flag++;
						if (temp[j]->m_Name == "炮") {
							j_chess.push_back("炮");
						}
					}
				}
				if (flag == 0) {
					if (y == temp[j]->getPos().m_y) {
						flag++;
						if (temp[j]->m_Name == "车") {
							j_chess.push_back("车");
						}
					}
				}
			}
		}
		//===================================================//
	}
	if (m_Camp == 0) {
		if (isFaced() != 0) {
			//判断是否对将
			j_chess.push_back("帅");

		}
		//判断是否被卒将
		bj_chess.push_back(isHasChess(m_p.m_x + 1, m_p.m_y));
		bj_chess.push_back(isHasChess(m_p.m_x - 1, m_p.m_y));
		bj_chess.push_back(isHasChess(m_p.m_x, m_p.m_y + 1));
		for (int i = 0; i < 3; i++) {
			if (bj_chess[i] != -1) {
				if (d[bj_chess[i]]->m_Name == "兵") {
					j_chess.push_back("兵");
				}
			}
		}
		//===================================================//
		//判断是否被马将
		if (!(Point(m_p.m_x + 2, m_p.m_y + 1).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x + 2, m_p.m_y + 1));
		}
		if (!(Point(m_p.m_x + 2, m_p.m_y - 1).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x + 2, m_p.m_y - 1));
		}
		if (!(Point(m_p.m_x - 2, m_p.m_y + 1).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x - 2, m_p.m_y + 1));
		}
		if (!(Point(m_p.m_x - 2, m_p.m_y - 1).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x - 2, m_p.m_y - 1));
		}
		if (!(Point(m_p.m_x + 1, m_p.m_y + 2).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x + 1, m_p.m_y + 2));
		}
		if (!(Point(m_p.m_x + 1, m_p.m_y - 2).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x + 1, m_p.m_y - 2));
		}
		if (!(Point(m_p.m_x - 1, m_p.m_y + 2).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x - 1, m_p.m_y + 2));
		}
		if (!(Point(m_p.m_x - 1, m_p.m_y - 2).isOutRange())) {
			mj_chess.push_back(isHasChess(m_p.m_x - 1, m_p.m_y - 2));
		}
		for (int i = 0; i < mj_chess.size(); i++) {
			if (mj_chess[i] != -1) {
				if (d[mj_chess[i]]->m_Name == "馬") {
					if (!(d[mj_chess[i]]->isBlock(m_p.m_x, m_p.m_y))) {
						j_chess.push_back("馬");
					}
				}
			}
		}
		//===================================================//
		//判断是否被车砲将，四个方向全做判断
		deque<Chess*> temp;
		int flag;
		for (int i = 0; i < d.size(); i++) {
			if (d[i]->getPos().m_y == this->m_p.m_y || d[i]->getPos().m_x == this->m_p.m_x)
				if (!(d[i]->isDead))
					temp.push_back(d[i]);
		}
		flag = 0;
		for (int x = m_p.m_x - 1; x > 0; x--) {
			for (int j = 0; j < temp.size(); j++) {
				if (flag == 1) {
					if (x == temp[j]->getPos().m_x) {
						flag++;
						if (temp[j]->m_Name == "砲") {
							j_chess.push_back("砲");
						}
					}
				}
				if (flag == 0) {
					if (x == temp[j]->getPos().m_x) {
						flag++;
						if (temp[j]->m_Name == "車") {
							j_chess.push_back("車");
						}
					}
				}
			}
		}
		flag = 0;
		for (int x = m_p.m_x + 1; x < 10; x++) {
			for (int j = 0; j < temp.size(); j++) {
				if (flag == 1) {
					if (x == temp[j]->getPos().m_x) {
						flag++;
						if (temp[j]->m_Name == "砲") {
							j_chess.push_back("砲");
						}
					}
				}
				if (flag == 0) {
					if (x == temp[j]->getPos().m_x) {
						flag++;
						if (temp[j]->m_Name == "車") {
							j_chess.push_back("車");
						}
					}
				}
			}
		}
		flag = 0;
		for (int y = m_p.m_y - 1; y > 0; y--) {
			for (int j = 0; j < temp.size(); j++) {
				if (flag == 1) {
					if (y == temp[j]->getPos().m_y) {
						flag++;
						if (temp[j]->m_Name == "砲") {
							j_chess.push_back("砲");
						}
					}
				}
				if (flag == 0) {
					if (y == temp[j]->getPos().m_y) {
						flag++;
						if (temp[j]->m_Name == "車") {
							j_chess.push_back("車");
						}
					}
				}
			}
		}
		flag = 0;
		for (int y = m_p.m_y + 1; y < 11; y++) {
			for (int j = 0; j < temp.size(); j++) {
				if (flag == 1) {
					if (y == temp[j]->getPos().m_y) {
						flag++;
						if (temp[j]->m_Name == "砲") {
							j_chess.push_back("砲");
						}
					}
				}
				if (flag == 0) {
					if (y == temp[j]->getPos().m_y) {
						flag++;
						if (temp[j]->m_Name == "車") {
							j_chess.push_back("車");
						}
					}
				}
			}
		}
		//===================================================//
	}
	


	//==================================================//
	if (!(j_chess.empty())) {
		color(FOREGROUND_RED);
		cout << "您正在被将军，请应将，将军的棋子有：";
		for (int i = 0; i < j_chess.size(); i++) {
			cout << j_chess[i] << " ";
		}
		color(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << endl;
		return true;
	}
}