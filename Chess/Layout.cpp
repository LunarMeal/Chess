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
//9.附加功能：将军检测与提示、自动判和（双方均无过河子）、悔棋、棋谱导入与导出（自定义棋局）
deque<Chess*> Chess::d;
stack<int*> Event;
stack<int> deathChess;
int Chess::tail;
int Chess::bound;
int tab;
int result;
bool isMore;
int mChessIndex;
void color(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
void Layout(int mode) {
	if (mode == 0) {
		Chess::d = InitChess();
	}
	if (mode == 1) {
		Chess::d = CustomChess();
	}
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
		else if (index == -4) {
			//悔棋
			cout << "是否悔棋（Y.确认/N.取消）？" << endl;
			char confirm;
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y') {
				if (Event.size() > 1) {
					for (int i = 0; i < 2; i++) {
						Chess::d[Event.top()[0]]->setPos(Event.top()[1], Event.top()[2]);
						delete[] Event.top();
						Event.pop();
						if (!deathChess.empty()) {
							if (deathChess.top() != -1) {
								Chess::d[deathChess.top()]->isDead = false;
							}
							deathChess.pop();
						}
					}
				}
				else {
					cout << "无法悔棋！" << endl;
					Sleep(1000);
				}
			}
			else {
				cout << "已取消！" << endl;
				system("pause");
			}
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
			color(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			cout << "游戏结束，黑胜红负！" << endl;
			break;
		}
		if (result == 1) {
			color(FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "游戏结束，红胜黑负！" << endl;
			break;
		}
		if (result == 2) {
			color(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			cout << "游戏结束，和棋！" << endl;
			break;
		}
		tab = !tab;
	}
	color(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	char c;
	cout << "是否保存当前棋谱（按Y确认）？" << endl;
	cin >> c;
	if (c == 'y' || c == 'Y') {
		ofstream ofs;
		ofs.open(PATH, ios::out);
		ofs << "1 ==2 ==3 ==4 ==5 ==6 ==7 ==8 ==9 " << endl;
		for (int y = 1; y < 11; y++) {
			for (int x = 1; x < 10; x++) {
				//棋子点位
				int obj = Chess::isHasChess(x, y);
				if (obj != -1) {
					//有棋子
					ofs << Chess::d[obj]->m_Name;
				}
				else {
					//无棋子
					if (y == 5 || y == 6) {
						ofs << LINE;
					}
					else {
						ofs << NODE;
					}
				}
				//棋子点位
				if (x != 9) {
					ofs << LINE;
				}
			}
			ofs << endl;
			//竖线区，不用判断有无棋子
			if (y != 10) {
				if (y == 5) {
					ofs << "|      楚河                                     汉界   | ";
				}
				else {
					for (int x = 1; x < 10; x++) {
						ofs << VLINE;
						if (x != 9) {
							ofs << "_";
							ofs << spSign(x, y);
							ofs << "_";
						}
					}
				}
				ofs << endl;
			}
		}
		ofs << "九==八==七==六==五==四==三==二==一" << endl;
		ofs.close();
		cout << "已保存！" << endl;
	}
	else {
		cout << "已取消！" << endl;
	}
	system("pause");
	while (!Event.empty()) {
		//释放所有棋谱记录在堆区开辟的空间
		delete[] Event.top();
		Event.pop();
	}
	for (int i = 0; i < Chess::tail + 1; i++) {
		//释放所有棋子在堆区开辟的空间
		delete Chess::d[i];
	}
}
void Board() {
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
		Chess::d[0]->isJiang();
	}
	else {
		cout << "当前轮到黑方走棋：" << endl;
		Chess::d[Chess::tail]->isJiang();
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
	bool isPeace = true;
	for (int i = 1; i < 12; i++) {
		if (!(Chess::d[i]->isDead)) {
			isPeace = false;
		}
	}
	for (int i = (Chess::tail)-1; i > (Chess::tail)-12; i--) {
		if (!(Chess::d[i]->isDead)) {
			isPeace = false;
		}
	}
	if (isPeace) {
		//过河子全部死亡系统自动判和
		cout << "双方均无过河子力" << endl;
		result = 2;
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
deque<Chess*> CustomChess() {
	tab = 1;
	result = 3;
	isMore = false;
	deque<Chess*> Rchess(32);
	Chess::tail = Rchess.size() - 1;
	Chess::bound = Rchess.size() / 2;
	for (int i = 0; i < Rchess.size(); i++) {
		Rchess[i] = new Jiang(1);
		Rchess[i]->isDead = true;
	}
	ifstream ifs;
	ifs.open(PATH, ios::in);
	if (!ifs.is_open()) {
		cout << "棋谱导入失败\n";
		return Rchess;
	}
	string buf;
	int line = 1;
	while (getline(ifs, buf)) {
		//按偶数行读入
		if (line % 2 == 0) {
			int i = 0;
			int column = 1;
			while (buf[i] != '\0') {
				string s = { buf[i],buf[i + 1]};
				if (line / 2 == 5 || line / 2 == 6) {
					//河界
					if (s != "—") {
						//忽略空位置
						if (s == "帅") {
							delete Rchess[0];
							Rchess[0] = new Jiang(1, column, line / 2);
							Rchess[0]->isDead = false;
						}
						if (s == "兵") {
							for (int i = 1; i < 6; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Bing(1, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "車") {
							for (int i = 6; i < 8; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Che(1, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "馬") {
							for (int i = 8; i < 10; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Ma(1, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "砲") {
							for (int i = 10; i < 12; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Pao(1, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "仕") {
							for (int i = 12; i < 14; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Shi(1, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "相") {
							for (int i = 14; i < 16; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Xiang(1, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "将") {
							delete Rchess[Chess::tail];
							Rchess[Chess::tail] = new Jiang(0, column, line / 2);
							Rchess[Chess::tail]->isDead = false;
						}
						if (s == "卒") {
							for (int i = 26; i < 31; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Bing(0, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "车") {
							for (int i = 24; i < 26; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Che(0, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "马") {
							for (int i = 22; i < 24; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Ma(0, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "炮") {
							for (int i = 20; i < 22; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Pao(0, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "士") {
							for (int i = 18; i < 20; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Shi(0, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "象") {
							for (int i = 16; i < 18; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Xiang(0, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}
					}
					column++;
					if (i != 32) {
						i += 4;
					}
					else {
						buf[i] = '\0';
					}
				}
				else {
					//非河界
					if (s != "—") {
						//忽略分隔符
						if (buf[i] != '+') {
							if (s == "帅") {
								delete Rchess[0];
								Rchess[0] = new Jiang(1, column, line / 2);
								Rchess[0]->isDead = false;
							}
							if (s == "兵") {
								for (int i = 1; i < 6; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Bing(1, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "車") {
								for (int i = 6; i < 8; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Che(1, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "馬") {
								for (int i = 8; i < 10; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Ma(1, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "砲") {
								for (int i = 10; i < 12; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Pao(1, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "仕") {
								for (int i = 12; i < 14; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Shi(1, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "相") {
								for (int i = 14; i < 16; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Xiang(1, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "将") {
								delete Rchess[Chess::tail];
								Rchess[Chess::tail] = new Jiang(0, column, line / 2);
								Rchess[Chess::tail]->isDead = false;
							}
							if (s == "卒") {
								for (int i = 26; i < 31; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Bing(0, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "车") {
								for (int i = 24; i < 26; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Che(0, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "马") {
								for (int i = 22; i < 24; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Ma(0, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "炮") {
								for (int i = 20; i < 22; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Pao(0, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "士") {
								for (int i = 18; i < 20; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Shi(0, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "象") {
								for (int i = 16; i < 18; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Xiang(0, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

						}
						column++;
					}
					i += 2;
				}
			}
		}
		line++;
	}
	system("pause");
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
	cout << "8. 悔棋 9. 求和 0. 认输）" << endl;
retry:
	cin >> select;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		select = -1;
	}
	switch (select)
	{
	case 1: {
		int* event = new int[3];
		event[0] = index_j[0];
		event[1] = Chess::d[index_j[0]]->getPos().m_x;
		event[2] = Chess::d[index_j[0]]->getPos().m_y ;
		Event.push(event);
		return index_j[0];
	}
	case 2:
		if (!(index_b.empty())) {
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
	case 8:
		return -4;
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
	case 1: {
		int* event = new int[3];
		event[0] = ds[0];
		event[1] = Chess::d[ds[0]]->getPos().m_x;
		event[2] = Chess::d[ds[0]]->getPos().m_y;
		Event.push(event);
		return ds[0];
	}
		break;
	case 2:
		if (select <= num) {
			int* event = new int[3];
			event[0] = ds[1];
			event[1] = Chess::d[ds[1]]->getPos().m_x;
			event[2] = Chess::d[ds[1]]->getPos().m_y;
			Event.push(event);
			return ds[1];
		}
		break;
	case 3:
		if (select <= num) {
			int* event = new int[3];
			event[0] = ds[2];
			event[1] = Chess::d[ds[2]]->getPos().m_x;
			event[2] = Chess::d[ds[2]]->getPos().m_y;
			Event.push(event);
			return ds[2];
		}
		break;
	case 4:
		if (select <= num) {
			int* event = new int[3];
			event[0] = ds[3];
			event[1] = Chess::d[ds[3]]->getPos().m_x;
			event[2] = Chess::d[ds[3]]->getPos().m_y;
			Event.push(event);
			return ds[3];
		}
		break;
	case 5:
		if (select <= num) {
			int* event = new int[3];
			event[0] = ds[4];
			event[1] = Chess::d[ds[4]]->getPos().m_x;
			event[2] = Chess::d[ds[4]]->getPos().m_y;
			Event.push(event);
			return ds[4];
		}
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