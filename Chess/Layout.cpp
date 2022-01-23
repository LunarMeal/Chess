#include "Layout.h"
#include "config.h"
//1.���д�ӡ
//2.���д�ӡ
//3.�ж�����
//4.������Ӫ ���췽Ϊ1���ڷ�Ϊ0��
//5.��˫�������ţ�ͷ�巨����췽��β�巨����ڷ������ڹ���
//6.���ж����ӵ�ǰ״̬����ִ���ƶ�
//7.���α�дÿ�����ӵ��߷������״̬���
//8.����
//9.���ӹ��ܣ������������ʾ���Զ��кͣ�˫�����޹����ӣ������塢���׵����뵼�����Զ�����֣�
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
				cout << "�췽ϣ����ͣ��Ƿ�ͬ�⣨Y.ͬ��/N.�ܾ���?" << endl;
			}
			if (tab == 0) {
				cout << "�ڷ�ϣ����ͣ��Ƿ�ͬ�⣨Y.ͬ��/N.�ܾ���?" << endl;
			}
			char confirm;
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y') {
				result = 2;
			}
			else {
				cout << "�Ѿܾ����壡" << endl;
				system("pause");
				tab = !tab;
			}
		}
		else if (index == -2) {
			cout << "�Ƿ����䣨Y.ȷ��/N.ȡ������" << endl;
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
				cout << "��ȡ����" << endl;
				system("pause");
				tab = !tab;
			}
		}
		else if (index == -3) {
			cout << "�ѷ���!" << endl;
			system("pause");
			tab = !tab;
		}
		else if (index == -4) {
			//����
			cout << "�Ƿ���壨Y.ȷ��/N.ȡ������" << endl;
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
					cout << "�޷����壡" << endl;
					Sleep(1000);
				}
			}
			else {
				cout << "��ȡ����" << endl;
				system("pause");
			}
			tab = !tab;
		}
		else {
			
			if (!(Chess::d[index]->findRoad())) {
				//ѭ��
				if (Chess::d[index]->isMoving) {
					//δ�ƶ����
					isMore = true;
				}
				else {
					//����
					isMore = false;
					cout << "��ȡ��!" << endl;
					system("pause");
				}
				tab = !tab;
			}
			else {
				//�ƶ����
				isMore = false;
				cout << "�ƶ���ɣ�" << endl;
				Chess::d[index]->isMoving = false;
				system("pause");
			}
		}
		Check();
		if (result == 0) {
			color(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			cout << "��Ϸ��������ʤ�츺��" << endl;
			break;
		}
		if (result == 1) {
			color(FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "��Ϸ��������ʤ�ڸ���" << endl;
			break;
		}
		if (result == 2) {
			color(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			cout << "��Ϸ���������壡" << endl;
			break;
		}
		tab = !tab;
	}
	color(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	char c;
	cout << "�Ƿ񱣴浱ǰ���ף���Yȷ�ϣ���" << endl;
	cin >> c;
	if (c == 'y' || c == 'Y') {
		ofstream ofs;
		ofs.open(PATH, ios::out);
		ofs << "1 ==2 ==3 ==4 ==5 ==6 ==7 ==8 ==9 " << endl;
		for (int y = 1; y < 11; y++) {
			for (int x = 1; x < 10; x++) {
				//���ӵ�λ
				int obj = Chess::isHasChess(x, y);
				if (obj != -1) {
					//������
					ofs << Chess::d[obj]->m_Name;
				}
				else {
					//������
					if (y == 5 || y == 6) {
						ofs << LINE;
					}
					else {
						ofs << NODE;
					}
				}
				//���ӵ�λ
				if (x != 9) {
					ofs << LINE;
				}
			}
			ofs << endl;
			//�������������ж���������
			if (y != 10) {
				if (y == 5) {
					ofs << "|      ����                                     ����   | ";
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
		ofs << "��==��==��==��==��==��==��==��==һ" << endl;
		ofs.close();
		cout << "�ѱ��棡" << endl;
	}
	else {
		cout << "��ȡ����" << endl;
	}
	system("pause");
	while (!Event.empty()) {
		//�ͷ��������׼�¼�ڶ������ٵĿռ�
		delete[] Event.top();
		Event.pop();
	}
	for (int i = 0; i < Chess::tail + 1; i++) {
		//�ͷ����������ڶ������ٵĿռ�
		delete Chess::d[i];
	}
}
void Board() {
	system("cls");
	cout << "1 ==2 ==3 ==4 ==5 ==6 ==7 ==8 ==9 " << endl;
	for (int y = 1; y < 11; y++) {
		for (int x = 1; x < 10; x++) {
			//���ӵ�λ
			int obj = Chess::isHasChess(x, y);
			if (obj != -1) {
				//������
				if (Chess::d[obj]->m_Camp == 1) {
					//����췽
					color(64);
				}
				else {
					color(32);
					//����ڷ�
				}
				cout << Chess::d[obj]->m_Name;
				color(7);
			}
			else {
				//������
				if (y == 5 || y == 6) {
					cout << LINE;
				}
				else {
					cout << NODE;
				}
			}
			//���ӵ�λ
			if (x != 9) {
				cout << LINE;
			}
		}
		cout << endl;
		//�������������ж���������
		if (y != 10) {
			if (y == 5) {
				cout << "|      ����              ����   | ";
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
	cout << "��==��==��==��==��==��==��==��==һ" << endl;
	if (tab == 1) {
		cout << "��ǰ�ֵ��췽���壺" << endl;
		Chess::d[0]->isJiang();
	}
	else {
		cout << "��ǰ�ֵ��ڷ����壺" << endl;
		Chess::d[Chess::tail]->isJiang();
	}
	return;
}
void Check() {
	if (Chess::d[0]->isDead) {
		//��˧����
		result = 0;
	}
	if (Chess::d[Chess::tail]->isDead) {
		//�ڽ�����
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
		//������ȫ������ϵͳ�Զ��к�
		cout << "˫�����޹�������" << endl;
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
	//����===========================����//
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
		cout << "���׵���ʧ��\n";
		return Rchess;
	}
	string buf;
	int line = 1;
	while (getline(ifs, buf)) {
		//��ż���ж���
		if (line % 2 == 0) {
			int i = 0;
			int column = 1;
			while (buf[i] != '\0') {
				string s = { buf[i],buf[i + 1]};
				if (line / 2 == 5 || line / 2 == 6) {
					//�ӽ�
					if (s != "��") {
						//���Կ�λ��
						if (s == "˧") {
							delete Rchess[0];
							Rchess[0] = new Jiang(1, column, line / 2);
							Rchess[0]->isDead = false;
						}
						if (s == "��") {
							for (int i = 1; i < 6; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Bing(1, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "܇") {
							for (int i = 6; i < 8; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Che(1, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "�R") {
							for (int i = 8; i < 10; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Ma(1, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "�h") {
							for (int i = 10; i < 12; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Pao(1, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "��") {
							for (int i = 12; i < 14; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Shi(1, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "��") {
							for (int i = 14; i < 16; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Xiang(1, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "��") {
							delete Rchess[Chess::tail];
							Rchess[Chess::tail] = new Jiang(0, column, line / 2);
							Rchess[Chess::tail]->isDead = false;
						}
						if (s == "��") {
							for (int i = 26; i < 31; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Bing(0, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "��") {
							for (int i = 24; i < 26; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Che(0, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "��") {
							for (int i = 22; i < 24; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Ma(0, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "��") {
							for (int i = 20; i < 22; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Pao(0, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "ʿ") {
							for (int i = 18; i < 20; i++) {
								if (Rchess[i]->isDead) {
									delete Rchess[i];
									Rchess[i] = new Shi(0, column, line / 2);
									Rchess[i]->isDead = false;
									break;
								}
							}
						}

						if (s == "��") {
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
					//�Ǻӽ�
					if (s != "��") {
						//���Էָ���
						if (buf[i] != '+') {
							if (s == "˧") {
								delete Rchess[0];
								Rchess[0] = new Jiang(1, column, line / 2);
								Rchess[0]->isDead = false;
							}
							if (s == "��") {
								for (int i = 1; i < 6; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Bing(1, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "܇") {
								for (int i = 6; i < 8; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Che(1, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "�R") {
								for (int i = 8; i < 10; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Ma(1, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "�h") {
								for (int i = 10; i < 12; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Pao(1, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "��") {
								for (int i = 12; i < 14; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Shi(1, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "��") {
								for (int i = 14; i < 16; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Xiang(1, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "��") {
								delete Rchess[Chess::tail];
								Rchess[Chess::tail] = new Jiang(0, column, line / 2);
								Rchess[Chess::tail]->isDead = false;
							}
							if (s == "��") {
								for (int i = 26; i < 31; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Bing(0, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "��") {
								for (int i = 24; i < 26; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Che(0, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "��") {
								for (int i = 22; i < 24; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Ma(0, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "��") {
								for (int i = 20; i < 22; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Pao(0, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "ʿ") {
								for (int i = 18; i < 20; i++) {
									if (Rchess[i]->isDead) {
										delete Rchess[i];
										Rchess[i] = new Shi(0, column, line / 2);
										Rchess[i]->isDead = false;
										break;
									}
								}
							}

							if (s == "��") {
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
	deque<int> index_j; //�Ͻ�
	deque<int> index_b; //��
	deque<int> index_c; //��
	deque<int> index_m; //��
	deque<int> index_p; //��
	deque<int> index_s; //ʿ
	deque<int> index_x; //��
	int select;//ѡ��
	cout << "��ѡ����Ҫ�ߵ����ӣ�" << endl;
	cout << "��";
	if (tab == 1) {
		//�췽���壬�����췽��������
		deque<int> r_d = Chess::getRchess();
		for (int i = 0; i < r_d.size(); i++) {
			if (Chess::d[r_d[i]]->m_Name == "˧") {
				if (index_j.empty())
					cout << "1. ˧ ";
				index_j.push_back(r_d[i]);
			}
			if (Chess::d[r_d[i]]->m_Name == "��") {
				if (index_b.empty())
					cout << "2. �� ";
				index_b.push_back(r_d[i]);
			}
			if (Chess::d[r_d[i]]->m_Name == "܇") {
				if (index_c.empty())
					cout << "3. ܇ ";
				index_c.push_back(r_d[i]);
			}
			if (Chess::d[r_d[i]]->m_Name == "�R") {
				if (index_m.empty())
					cout << "4. �R ";
				index_m.push_back(r_d[i]);
			}
			if (Chess::d[r_d[i]]->m_Name == "�h") {
				if (index_p.empty())
					cout << "5. �h ";
				index_p.push_back(r_d[i]);
			}
			if (Chess::d[r_d[i]]->m_Name == "��") {
				if (index_s.empty())
					cout << "6. �� ";
				index_s.push_back(r_d[i]);
			}
			if (Chess::d[r_d[i]]->m_Name == "��") {
				if (index_x.empty())
					cout << "7. �� ";
				index_x.push_back(r_d[i]);
			}
		}
	}
	if (tab == 0) {
		//�ڷ����壬�����ڷ���������
		deque<int> b_d = Chess::getBchess();
		for (int i = 0; i < b_d.size(); i++) {
			if (Chess::d[b_d[i]]->m_Name == "��") {
				if (index_j.empty())
					cout << "1. �� ";
				index_j.push_back(b_d[i]);
			}
			if (Chess::d[b_d[i]]->m_Name == "��") {
				if (index_b.empty())
					cout << "2. �� ";
				index_b.push_back(b_d[i]);
			}
			if (Chess::d[b_d[i]]->m_Name == "��") {
				if (index_c.empty())
					cout << "3. �� ";
				index_c.push_back(b_d[i]);
			}
			if (Chess::d[b_d[i]]->m_Name == "��") {
				if (index_m.empty())
					cout << "4. �� ";
				index_m.push_back(b_d[i]);
			}
			if (Chess::d[b_d[i]]->m_Name == "��") {
				if (index_p.empty())
					cout << "5. �� ";
				index_p.push_back(b_d[i]);
			}
			if (Chess::d[b_d[i]]->m_Name == "ʿ") {
				if (index_s.empty())
					cout << "6. ʿ ";
				index_s.push_back(b_d[i]);
			}
			if (Chess::d[b_d[i]]->m_Name == "��") {
				if (index_x.empty())
					cout << "7. �� ";
				index_x.push_back(b_d[i]);
			}
		}
	}
	cout << "8. ���� 9. ��� 0. ���䣩" << endl;
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
			//��ȫ�ֱ����洢�ಽ����±�
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
			//��ȫ�ֱ����洢�ಽ����±�
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
		cout << "������������û�и����ӣ�������ѡ��" << endl;
		goto retry;
	}
	return 0;
}
int selectChess(deque<int> ds) {
	int num = ds.size(); //��ǰ�����ж��ٿ�����
	int select;
	cout << "��ѡ��";
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
	cout << "0. ����" << endl;
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
	cout << "������������û�и����ӣ�������ѡ��" << endl;
	goto retry2;
}