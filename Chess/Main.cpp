#include "Menu.h"
#include "Layout.h"
//制作一个象棋程序
//1. 需要一个开始菜单
//2. PVP模式（不需要做选择红方/黑方选项）
//3. 打印一个棋盘
//4. 在棋盘上打印棋子
int main() {
	int tab;
	while (1) {
		Menu();
		cin >> tab;
		switch (tab)
		{
		case 0:
			cout << "游戏已退出" << endl;
			system("pause");
			return 0;
		case 1:
			Layout();
			break;
		default:
			cout << "请输入正确的选项！" << endl;
			break;
		}
		system("cls");
	}
}