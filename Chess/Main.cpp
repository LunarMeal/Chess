#include "Menu.h"
#include "Layout.h"
//����һ���������
//1. ��Ҫһ����ʼ�˵�
//2. PVPģʽ������Ҫ��ѡ��췽/�ڷ�ѡ�
//3. ��ӡһ������
//4. �������ϴ�ӡ����
int main() {
	int tab;
	while (1) {
		Menu();
		cin >> tab;
		switch (tab)
		{
		case 0:
			cout << "��Ϸ���˳�" << endl;
			system("pause");
			return 0;
		case 1:
			Layout();
			break;
		default:
			cout << "��������ȷ��ѡ�" << endl;
			break;
		}
		system("cls");
	}
}