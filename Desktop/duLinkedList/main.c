#include <stdio.h>
#include <stdlib.h>
#include "C:\Users\大伶\Desktop\head\dulinkedList.h"


//Status InitList_DuL(DuLinkedList *L);
//void DestroyList_DuL(DuLinkedList *L);
//Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q);
//Status InsertAfterList_DuL(DuLNode *p, DuLNode *q);
//Status DeleteList_DuL(DuLNode *p, ElemType *e);
//void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e));
//void show(DuLinkedList head);
//void Visit(ElemType e);
//void Printdata(DuLinkedList L);
//DuLNode* LocatePtr(DuLinkedList L,ElemType e);
int main(){
	DuLinkedList d;
	DuLNodePtr p,q;
	ElemType *e;
	printf("--------------------\n");
	InitList_DuL(&d);
//	show(d);
	Printdata(d);
	
//	InsertBeforeList_DuL(p, q);//q插入到p前
	
//	InsertAfterList_DuL(p, q);//q插入到p后 
	
//	DeleteList_DuL(p, e);
//	printf("--------------------\n");
	TraverseList_DuL(d, Visit);
//	printf("--------------------\n");
	DestroyList_DuL(&d);
//	printf("--------------------\n");
	system("pause");
}
