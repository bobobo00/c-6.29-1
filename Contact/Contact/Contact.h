#ifndef _CONTACT_H_
#define _CONTACT_H_

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <errno.h>
#include <string.h>

#define NAME_SIZE 64
#define TELE_SIZE 16
#define ELP_SIZE 16
#define STATE_SIZE 16
#define ADDRESS_SIZE 128
#define LIST_DEFAULT 5
#define INC_SIZE 2

#define CT_FILE "contact.bin"
typedef struct Person{
	char name[NAME_SIZE];
	char elp[ELP_SIZE];
	char state[STATE_SIZE];
	char street[NAME_SIZE]; 
	char  city[ADDRESS_SIZE];
}person,*person_p,**person_pp;

typedef struct Contact{
	int cap;
	int size;
	person contact[0];
}contact,*contact_ct;

int InitContactFile(contact **ct, FILE *fp);
void InitContactDefault(contact **ct);
void AddList(contact_ct ct);
void DeletList(contact_ct ct);
void CheckList(contact_ct ct);
void AlterList(contact_ct ct);
void ShowList(contact_ct ct);
void ClearList(contact_ct ct);
void SortList(contact_ct ct);
void DesList(contact_ct ct);
void Menue();
void Save(contact_ct ct);
int Load(contact **ct);

#endif