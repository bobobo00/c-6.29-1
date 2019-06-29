#define _CRT_SECURE_NO_WARNINGS 1
#include "Contact.h"
//�˵���ѡ��ִ�в���
void Menue(){
	printf("____________________________\n");
	printf("  1.Show      |     2.Delet  \n");
	printf("  3.Alter     |     4.Check  \n");
	printf("  5.Add       |     6.Clear  \n");
	printf("  7.Sort      |     8.Exit   \n");
	printf("____________________________\n");
	printf("Please enter your choice��\n");
//�жϸ�ͨѶ¼�Ƿ���
}static int Isfull(contact_ct ct){
	return ct->size == ct->cap ? 1 : 0;
}
//��������ͨѶ¼��������
static int Inc(contact_ct *cp){
	int new_size = sizeof(contact)+((*cp)->cap + INC_SIZE)*sizeof(person);//���ݵĴ�СΪԭ������Ĵ�С�������ӵ����鳤��
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
//��ʼ��ͨѶ¼�ļ�
int InitContactFile(contact **ct,FILE *fp){
	contact_ct ct_p = (contact_ct)malloc(sizeof(contact));
	if (ct_p){
		fread(ct_p, sizeof(contact), 1, fp);//��һ���ִ�fp�ж�ͨѶ¼ͷ������ͨѶ¼��������������ϵ�˸����Ĵ�С��ct_p�С�
		int _cap = ct_p->cap;
		int size = sizeof(contact)+ct_p->cap*sizeof(person);
		contact_ct p = (contact_ct)realloc(ct_p, size);//�������ݣ����ݴ�СΪͨѶ¼ͷ����С+ͨѶ¼��������û�����cap
		if (p){
			ct_p = p;
			fread(ct_p->contact, ct_p->cap*sizeof(person), 1, fp);//�ڶ����ִ�fp�ж�ͨѶ¼cap����ϵ�˵���Ϣ��ct_p->contact�С�
			*ct = ct_p;
			return 1;//���ݷ������ִ��ļ��ж�ȡ�����ݻָ��ɹ���
		}
		else{ 
			return 0; 
		}
	}
	else{
		return 0;
	}
}
//���ļ�ʧ�ܻ��һ�δ�ͨѶ¼�ļ�ʱʹ�ø÷�����ʼ��ͨѶ¼
void InitContactDefault(contact **ct){
	*ct = malloc(sizeof(contact)+sizeof(person)*LIST_DEFAULT);//�״�ΪͨѶ¼����ռ�
	if (NULL == *ct){
		printf("%s:%d", strerror(errno), errno);
		exit(1);
	}
	(*ct)->cap = LIST_DEFAULT;
	(*ct)->size = 0;
	printf("Init Conact Success!\n");
}
//��������
int Load(contact **ct){
	FILE *fp = fopen(CT_FILE, "rb");//���ļ�
	if (NULL == fp){//���ļ�ʧ�ܻ��һ��ʹ�ø�ͨѶ¼
		printf("Init Contact Default!\n");
		InitContactDefault(ct);
		return 1;
	}
	int ret = InitContactFile(ct, fp);//�ӱ����ļ��лָ���Ϣ��ͨѶ¼��
	fclose(fp);//�ر��ļ���
	return ret;
}
//�����ϵ��
void AddList(contact_ct *cp){
	if (!Isfull(*cp) || Inc(cp)){//����ص㵱��һ������Ϊ��ʱ���жϵڶ�������������һ������Ϊ��ʱ���жϵڶ�������
		person_p a=&((*cp)->contact[(*cp)->size]);
		printf("Please Enter Name:");
		scanf("%s", a->name);
		printf("Please Enter Elp:");
		scanf(" %s", a->elp);//sacnfǰ�ÿո��ֹ�س�����һ��scanf���롣
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
//ɾ����ϵ��
void DeletList(contact_ct ct){
	char per[NAME_SIZE];
	printf("Please enter contact information to delet��\n");
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
				printf("Delet\n");//��ϵ��ɾ���ɹ�
				flag = 0;
			}
		}
		if (flag){//��ϵ�˲�����
			printf("Not exit!Failure\n");
			flag = 0;
		}
	}
}
//�޸ĵ�ǰ��ϵ����Ϣ
void AlterList(contact_ct ct){
	char per[NAME_SIZE];
	printf("Please enter contact information to alter��\n");
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
			printf("Alter!\n");//�޸ĳɹ�
		}
	}
	if (flag){
		printf("Contact person not exit��\n");//��ϵ�˲������޷��޸�
	}
}
//������ϵ��
void CheckList(contact_ct ct){
	char per[NAME_SIZE];
	printf("Please enter contact information to find��\n");
	scanf("%s", per);
	int i = 0;
	int flag = 1;
	for (i = 0; i <= ct->size; i++)
	if (!(strcmp(ct->contact[i].name, per))){
			printf("name��%s elp��%s state��%s street��%s city��%s\n", ct->contact[i].name, ct->contact[i].elp, ct->contact[i].state, ct->contact[i].street, ct->contact[i].city);
			flag = 0;
			printf("Check!\n");//���ҵ���ϵ��
		}
    if (flag){
		printf("Not Exit!\n");//��ϵ�˲�����
	}
}
//��ʾ������ϵ����Ϣ
void ShowList(contact_ct ct){
	if (ct->size == 0){
		printf("Contact book is empty.please enter information first\n");
	}
	else{
		int i = 0;
		for (i = 0; i < ct->size; i++){
			printf("name��%s elp��%s state��%s street��%s city��%s\n", ct->contact[i].name, ct->contact[i].elp, ct->contact[i].state, ct->contact[i].street, ct->contact[i].city);
			printf("\n");
		}
	}
}
//�����ϵ��
void ClearList(contact_ct ct){
	ct->size=0;
}
static int person_cmp(const void *x, const void *y){
	person_p _x = (person_p)x;
	person_p _y = (person_p)y;
	return strcmp(_x->name, _y->name);
}
//���ÿ���ʵ�ְ�����ϵ����������
void SortList(contact_ct ct){
	person_p p = ct->contact;
	qsort(p, ct->size, sizeof(person), person_cmp);
}
//��ÿ��д��ͨ��¼�е���Ч��Ϣ�����ڱ����ļ��С�
void Save(contact_ct ct){
	FILE *fp = fopen(CT_FILE, "wb");//���ļ�
	if (NULL == fp){//���ļ�ʧ��
		printf("fopen error!\n");
		return;
	}
	int size = sizeof(contact)+ct->cap*sizeof(person);//ͨѶ¼����Ĵ�С+ͨѶ¼���洢��Ч�û���С
	fwrite(ct, size, 1, fp);//д��ʱ��ȷ���м����ֽڣ�ȷ��������λ��С����һ����λ�Ĵ�С��������ͨѶ¼��size��
	fclose(fp);//�ر��ļ�
}
