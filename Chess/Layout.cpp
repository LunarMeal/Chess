#include "Layout.h"
#include "config.h"
//1.按行打印
//2.按列打印
//3.判断棋子
//4.划分阵营 （红方为1，黑方为0）
//5.用双向数组存放，头插法放入红方，尾插法放入黑方，便于管理
//6.先判断棋子当前状态，再执行移动
//7.依次编写每种棋子的走法规则和状态检测
//8.测试
deque<Chess*> Chess::d;
int Chess::tail;
int Chess::bound;
int tab;
int result;
bool isMore;
int mChessIndex;
void color(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
void Layout() {
	Chess::d = InitChess();
	while (1)
	{
		/*if (cin.fail()) {
			cin.clear();
			cin.ignore();
		}*/
		Board();
		int index;
		if (!isMore)
			index = selectChess();
		else
			index = mChessIndex;
		if (index == -1) {
			if (tab == 1) {
				cout << "红方希望求和，是否同意（Y.同意/N.拒绝）?" << endl;
			}
			if (tab == 0) {
				cout << "黑方希望求和，是否同意（Y.同意/N.拒绝）?" << endl;
			}
			char confirm;
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y') {
				result = 2;
			}
			else {
				cout << "已拒绝和棋！" << endl;
				system("pause");
				tab = !tab;
			}
		}
		else if (index == -2) {
			cout << "是否认输（Y.确认/N.取消）？" << endl;
			char confirm;
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y') {
				if (tab == 1) {
					result = 0;
				}
				if (tab == 0) {
					result = 1;
				}
			}
			else {
				cout << "已取消！" << endl;
				system("pause");
				tab = !tab;
			}
		}
		else if (index == -3) {
			cout << "已返回!" << endl;
			system("pause");
			tab = !tab;
		}
		else {
			if (!(Chess::d[index]->findRoad())) {
				//循环
				if (Chess::d[index]->isMoving) {
					//未移动完成
					isMore = true;
				}
				else {
					//返回
					isMore = false;
					cout << "已取消!" << endl;
					system("pause");
				}
				tab = !tab;
			}
			else {
				//移动完成
				isMore = false;
				cout << "移动完成！" << endl;
				Chess::d[index]->isMoving = false;
				system("pause");
			}
		}
		Check();
		if (result == 0) {
			cout << "游戏结束，黑胜红负！" << endl;
			system("pause");
			break;
		}
		if (result == 1) {
			cout << "游戏结束，红胜黑负！" << endl;
			system("pause");
			break;
		}
		if (result == 2) {
			cout << "游戏结束，和棋！" << endl;
			system("pause");
			break;
		}
		tab = !tab;
	}
	for (int i = 0; i < Chess::tail + 1; i++) {
		//释放所有棋子在堆区开辟的空间
		delete Chess::d[i];
	}
}
void Board(){
	system("cls");
	cout << "1 ==2 ==3 ==4 ==5 ==6 ==7 ==8 ==9 " << endl;
	for (int y = 1; y < 11; y++) {
		for (int x = 1; x < 10; x++) {
			//棋子点位
			int obj = Chess::isHasChess(x, y);
			if (obj != -1) {
				//有棋子
				if (Chess::d[obj]->m_Camp == 1) {
					//代表红方
					color(64);
				}
				else {
					color(32);
					//代表黑方
				}
				cout << Chess::d[obj]->m_Name;
				color(7);
			}
			else {
				//无棋子
				if (y == 5 || y == 6) {
					cout << LINE;
				}
				else {
					cout << NODE;
				}
			}
			//棋子点位
			if (x != 9) {
				cout << LINE;
			}
		}
		cout << endl;
		//竖线区，不用判断有无棋子
		if (y != 10) {
			if (y == 5) {
				cout << "|      楚河              汉界   | ";
			}
			else {
				for (int x = 1; x < 10; x++) {
					cout << VLINE;
					if (x != 9) {
						cout << spSign(x, y);
					}
				}
			}
			cout << endl;
		}
	}
	cout << "九==八==七==六==五==四==三==二==一" << endl;
	if (tab == 1) {
		cout << "当前轮到红方走棋：" << endl;
	}
	else {
		cout << "当前轮到黑方走棋：" << endl;
	}
	return;
}
void Check() {
	if (Chess::d[0]->isDead) {
		//红帅死亡
		result = 0;
	}
	if (Chess::d[Chess::tail]->isDead) {
		//黑将死亡
		result = 1;
	}
}
string spSign(int x, int y) {
	if (x == 4) {
		if (y == 1 || y == 8) {
			return BSLASH;
		}
		if (y == 2 || y == 9) {
			return SLASH;
		}
	}
	if (x == 5) {
		if (y == 1 || y == 8) {
			return SLASH;
		}
		if (y == 2 || y == 9) {
			return BSLASH;
		}
	}
	return SPACE;
}
deque<Chess*> InitChess() {
	tab = 1;
	result = 3;
	isMore = false;
	deque<Chess*> Rchess;
	Chess* jiang = new Jiang(0);
	Chess* shuai = new Jiang(1);
	//留空===========================留空//
	int k = 1;
	for (int i = 0; i < 2; i++) {
		Chess* BXiang = new Xiang(0, 5 + 2 * k);
		Rchess.push_back(BXiang);
		Chess* RXiang = new Xiang(1, 5 + 2 * k);
		Rchess.push_front(RXiang);
		Chess* Bshi = new Shi(0, 5 + k);
		Rchess.push_back(Bshi);
		Chess* Rshi = new Shi(1, 5 + k);
		Rchess.push_front(Rshi);
		Chess* pao = new Pao(0, 5 + 3 * k);
		Rchess.push_back(pao);
		Chess* bao = new Pao(1, 5 + 3 * k);
		Rchess.push_front(bao);
		Chess* Bma = new Ma(0, 5 + 3 * k);
		Rchess.push_back(Bma);
		Chess* Rma = new Ma(1, 5 + 3 * k);
		Rchess.push_front(Rma);
		Chess* che = new Che(0, 5 + 4 * k);
		Rchess.push_back(che);
		Chess* ju = new Che(1, 5 + 4 * k);
		Rchess.push_front(ju);
		k = -k;
	}
	for (int x = 1; x < 10; x += 2) {
		Chess* zu = new Bing(0, x);
		Rchess.push_back(zu);
		Chess* bing = new Bing(1, x);
		Rchess.push_front(bing);
	}
	Rchess.push_back(jiang);
	Rchess.push_front(shuai);
	//cout << Rchess.size();
	Chess::tail = Rchess.size() - 1;
	Chess::bound = Rchess.size() / 2;
	return Rchess;
}
int selectChess() {
	deque<int> index_j; //老将
	deque<int> index_b; //兵
	deque<int> index_c; //车
	deque<int> index_m; //马
	deque<int> index_p; //炮
	deque<int> index_s; //士
	deque<int> index_x; //象
	int select;//选择
	cout << "请选择你要走的棋子：" << endl;
	cout << "（";
	if (tab == 1) {
		//红方走棋，遍历红方棋子总数
		deque<int> r_d = Chess::getRchess();
		for (int i = 0; i < r_d.size(); i++) {
			if (Chess::d[r_d[i]]->m_Name == "帅") {
				if (index_j.empty())
					cout << "1. 帅 ";
				index_j.push_back(r_d[i]);
			}
			if (Chess::d[r_d[i]]->m_Name == "兵") {
				if (index_b.empty())
					cout << "2. 兵 ";
				index_b.push_back(r_d[i]);
			}
			if (Chess::d[r_d[i]]->m_Name == "車") {
				if (index_c.empty())
					cout << "3. 車 ";
				index_c.push_back(r_d[i]);
			}
			if (Chess::d[r_d[i]]->m_Name == "馬") {
				if (index_m.empty())
					cout << "4. 馬 ";
				index_m.push_back(r_d[i]);
			}
			if (Chess::d[r_d[i]]->m_Name == "砲") {
				if (index_p.empty())
					cout << "5. 砲 ";
				index_p.push_back(r_d[i]);
			}
			if (Chess::d[r_d[i]]->m_Name == "仕") {
				if (index_s.empty())
					cout << "6. 仕 ";
				index_s.push_back(r_d[i]);
			}
			if (Chess::d[r_d[i]]->m_Name == "相") {
				if (index_x.empty())
					cout << "7. 相 ";
				index_x.push_back(r_d[i]);
			}
		}
	}
	if (tab == 0) {
		//黑方走棋，遍历黑方棋子总数
		deque<int> b_d = Chess::getBchess();
		for (int i = 0; i < b_d.size(); i++) {
			if (Chess::d[b_d[i]]->m_Name == "将") {
				if (index_j.empty())
					cout << "1. 将 ";
				index_j.push_back(b_d[i]);
			}
			if (Chess::d[b_d[i]]->m_Name == "卒") {
				if (index_b.empty())
					cout << "2. 卒 ";
				index_b.push_back(b_d[i]);
			}
			if (Chess::d[b_d[i]]->m_Name == "车") {
				if (index_c.empty())
					cout << "3. 车 ";
				index_c.push_back(b_d[i]);
			}
			if (Chess::d[b_d[i]]->m_Name == "马") {
				if (index_m.empty())
					cout << "4. 马 ";
				index_m.push_back(b_d[i]);
			}
			if (Chess::d[b_d[i]]->m_Name == "炮") {
				if (index_p.empty())
					cout << "5. 炮 ";
				index_p.push_back(b_d[i]);
			}
			if (Chess::d[b_d[i]]->m_Name == "士") {
				if (index_s.empty())
					cout << "6. 士 ";
				index_s.push_back(b_d[i]);
			}
			if (Chess::d[b_d[i]]->m_Name == "象") {
				if (index_x.empty())
					cout << "7. 象 ";
				index_x.push_back(b_d[i]);
			}
		}
	}
	cout << " 9. 求和  0.认输）" << endl;
retry:
	cin >> select;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		select = -1;
	}
	switch (select)
	{
	case 1:
		return index_j[0];
	case 2:
		if (!(index_b.empty())){
			return selectChess(index_b);
		}
	case 3:
		if (!(index_c.empty())) {
			isMore = true;
			//用全局变量存储多步棋的下标
			mChessIndex = selectChess(index_c);
			return mChessIndex;
		}
	case 4:
		if (!(index_m.empty())) {
			return selectChess(index_m);
		}
	case 5:
		if (!(index_p.empty())) {
			isMore = true;
			//用全局变量存储多步棋的下标
			mChessIndex = selectChess(index_p);
			return mChessIndex;
		}
	case 6:
		if (!(index_s.empty())) {
			return selectChess(index_s);
		}
	case 7:
		if (!(index_x.empty())) {
			return selectChess(index_x);
		}
	case 9:
		return -1;
	case 0:
		return -2;
	default:
		cout << "棋子已死亡或没有该棋子！请重新选择" << endl;
		goto retry;
	}
	return 0;
}
int selectChess(deque<int> ds) {
	int num = ds.size(); //当前兵种有多少颗棋子
	int select;
	cout << "请选择：";
	if (Chess::d[ds[0]]->m_Camp == 1) {
		for (int i = 0; i < num; i++) {
			cout << i + 1 << ". " << Chess::d[ds[i]]->m_Name << Chess::d[ds[i]]->xNumToChar() << " ";
		}
	}
	if (Chess::d[ds[0]]->m_Camp == 0) {
		for (int i = 0; i < num; i++) {
			cout << i + 1 << ". " << Chess::d[ds[i]]->m_Name << Chess::d[ds[i]]->getPos().m_x << " ";
		}
	}
	cout << "0. 返回" << endl;
retry2:
	cin >> select;
	switch (select)
	{
	case 1:
		return ds[0];
		break;
	case 2:
		if(select<=num)
			return ds[1];
		break;
	case 3:
		if (select <= num)
			return ds[2];
		break;
	case 4:
		if (select <= num)
			return ds[3];
		break;
	case 5:
		if (select <= num)
			return ds[4];
		break;
	case 0:
		isMore = false;
		return -3;
	default:
		break;
	}
	cout << "棋子已死亡或没有该棋子！请重新选择" << endl;
	goto retry2;
}