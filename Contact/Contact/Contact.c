#define _CRT_SECURE_NO_WARNINGS 1
#include "Contact.h"
//菜单，选择执行操作
void Menue(){
	printf("____________________________\n");
	printf("  1.Show      |     2.Delet  \n");
	printf("  3.Alter     |     4.Check  \n");
	printf("  5.Add       |     6.Clear  \n");
	printf("  7.Sort      |     8.Exit   \n");
	printf("____________________________\n");
	printf("Please enter your choice：\n");
//判断该通讯录是否满
}static int Isfull(contact_ct ct){
	return ct->size == ct->cap ? 1 : 0;
}
//对已满的通讯录进行扩容
static int Inc(contact_ct *cp){
	int new_size = sizeof(contact)+((*cp)->cap + INC_SIZE)*sizeof(person);//扩容的大小为原来数组的大小加上增加的数组长度
	contact_ct c = realloc(*cp, new_size);
	if (!c){
		printf("Inc error!\n");
		return 0;
	}
	c->cap = (*cp)->cap + INC_SIZE;
	*cp = c;
	printf("Inc success!\n");
	return 1;
}
//初始化通讯录文件
int InitContactFile(contact **ct,FILE *fp){
	contact_ct ct_p = (contact_ct)malloc(sizeof(contact));
	if (ct_p){
		fread(ct_p, sizeof(contact), 1, fp);//第一部分从fp中读通讯录头部包括通讯录的容量和现有联系人个数的大小到ct_p中。
		int _cap = ct_p->cap;
		int size = sizeof(contact)+ct_p->cap*sizeof(person);
		contact_ct p = (contact_ct)realloc(ct_p, size);//进行扩容，扩容大小为通讯录头部大小+通讯录所保存的用户个数cap
		if (p){
			ct_p = p;
			fread(ct_p->contact, ct_p->cap*sizeof(person), 1, fp);//第二部分从fp中读通讯录cap个联系人的信息到ct_p->contact中。
			*ct = ct_p;
			return 1;//数据分两部分从文件中读取，数据恢复成功。
		}
		else{ 
			return 0; 
		}
	}
	else{
		return 0;
	}
}
//打开文件失败或第一次打开通讯录文件时使用该方法初始化通讯录
void InitContactDefault(contact **ct){
	*ct = malloc(sizeof(contact)+sizeof(person)*LIST_DEFAULT);//首次为通讯录申请空间
	if (NULL == *ct){
		printf("%s:%d", strerror(errno), errno);
		exit(1);
	}
	(*ct)->cap = LIST_DEFAULT;
	(*ct)->size = 0;
	printf("Init Conact Success!\n");
}
//程序的入口
int Load(contact **ct){
	FILE *fp = fopen(CT_FILE, "rb");//打开文件
	if (NULL == fp){//打开文件失败或第一次使用该通讯录
		printf("Init Contact Default!\n");
		InitContactDefault(ct);
		return 1;
	}
	int ret = InitContactFile(ct, fp);//从本地文件中恢复信息到通讯录中
	fclose(fp);//关闭文件啊
	return ret;
}
//添加联系人
void AddList(contact_ct *cp){
	if (!Isfull(*cp) || Inc(cp)){//或的特点当第一个条件为真时不判断第二个条件，当第一个条件为假时才判断第二个条件
		person_p a=&((*cp)->contact[(*cp)->size]);
		printf("Please Enter Name:");
		scanf("%s", a->name);
		printf("Please Enter Elp:");
		scanf(" %s", a->elp);//sacnf前置空格防止回车被下一个scanf输入。
		printf("Please Enter State:");
		scanf(" %s", a->state);
		printf("Please Enter Street:");
		scanf(" %s", a->street);
		printf("Please Enter City:");
		scanf(" %s", a->city);
		((*cp)->size)++;
	}
	else{
		printf("realloc error!\n");
		return;
	}
}
//删除联系人
void DeletList(contact_ct ct){
	char per[NAME_SIZE];
	printf("Please enter contact information to delet：\n");
	scanf("%s", per);
	int i = 0;
	int flag = 1;
	int j = 0;
	while (flag){
		for (i = 0; i <= ct->size; i++){
			if (!(strcmp(ct->contact[i].name, per))){
				for (j = i; j < ct->size; j++){
					ct->contact[j] = ct->contact[j + 1];
				}
				ct->size--;
				printf("Delet\n");//联系人删除成功
				flag = 0;
			}
		}
		if (flag){//联系人不存在
			printf("Not exit!Failure\n");
			flag = 0;
		}
	}
}
//修改当前联系人信息
void AlterList(contact_ct ct){
	char per[NAME_SIZE];
	printf("Please enter contact information to alter：\n");
	scanf("%s", per);
	int i = 0;
	int flag = 1;
	for (i = 0; i <= ct->size; i++){
		if (!(strcmp(ct->contact[i].name, per))){
			printf("Please enter modified contact information:\n");
			printf("Please Enter Name:");
			scanf("%s", ct->contact[i].name);
			printf("Please Enter Elp:");
			scanf(" %s", ct->contact[i].elp);
			printf("Please Enter State:");
			scanf(" %s", ct->contact[i].state);
			printf("Please Enter Street:");
			scanf(" %s", ct->contact[i].street);
			printf("Please Enter City:");
			scanf(" %s", ct->contact[i].city);
			
			flag = 0;
			printf("Alter!\n");//修改成功
		}
	}
	if (flag){
		printf("Contact person not exit！\n");//联系人不存在无法修改
	}
}
//查找联系人
void CheckList(contact_ct ct){
	char per[NAME_SIZE];
	printf("Please enter contact information to find：\n");
	scanf("%s", per);
	int i = 0;
	int flag = 1;
	for (i = 0; i <= ct->size; i++)
	if (!(strcmp(ct->contact[i].name, per))){
			printf("name：%s elp：%s state：%s street：%s city：%s\n", ct->contact[i].name, ct->contact[i].elp, ct->contact[i].state, ct->contact[i].street, ct->contact[i].city);
			flag = 0;
			printf("Check!\n");//已找到联系人
		}
    if (flag){
		printf("Not Exit!\n");//联系人不存在
	}
}
//显示所有联系人信息
void ShowList(contact_ct ct){
	if (ct->size == 0){
		printf("Contact book is empty.please enter information first\n");
	}
	else{
		int i = 0;
		for (i = 0; i < ct->size; i++){
			printf("name：%s elp：%s state：%s street：%s city：%s\n", ct->contact[i].name, ct->contact[i].elp, ct->contact[i].state, ct->contact[i].street, ct->contact[i].city);
			printf("\n");
		}
	}
}
//清空联系人
void ClearList(contact_ct ct){
	ct->size=0;
}
static int person_cmp(const void *x, const void *y){
	person_p _x = (person_p)x;
	person_p _y = (person_p)y;
	return strcmp(_x->name, _y->name);
}
//利用快排实现按照联系人名字排序
void SortList(contact_ct ct){
	person_p p = ct->contact;
	qsort(p, ct->size, sizeof(person), person_cmp);
}
//将每次写进通信录中的有效信息保存在本地文件中。
void Save(contact_ct ct){
	FILE *fp = fopen(CT_FILE, "wb");//打开文件
	if (NULL == fp){//打开文件失败
		printf("fopen error!\n");
		return;
	}
	int size = sizeof(contact)+ct->cap*sizeof(person);//通讯录本身的大小+通讯录所存储有效用户大小
	fwrite(ct, size, 1, fp);//写入时需确定有几个字节，确定基本单位大小，而一个单位的大小就是整个通讯录即size。
	fclose(fp);//关闭文件
}
