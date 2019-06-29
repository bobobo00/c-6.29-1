#define _CRT_SECURE_NO_WARNINGS 1
#include "Contact.h"
int main(){
	contact_ct ct;
	volatile int quit = 0;
	int select = 0;
	Load(&ct);//每次运行程序时先判断按哪种方式初始化通讯录
		while (!quit){
			Menue();
			scanf("%d", &select);
			switch (select){
			case 1:
			    ShowList(ct);
				break;
			case 2:
				DeletList(ct);
				break;
			case 3:
				AlterList(ct);
				break;
			case 4:
				CheckList(ct);
				break;
			case 5:
				AddList(&ct);
				break;
			case 6:
				ClearList(ct);
				break;
			case 7:
				SortList(ct);
				break;
			case 8:
				Save(ct);
				quit = 1;
				break;
			default:
				break;
			}
		}
	system("pause");
	return 0;
}