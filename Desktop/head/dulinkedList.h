/***************************************************************************************
 *	File Name				:	duLinkedList.h
 *	CopyRight				:	2019 QG Studio  
 *	SYSTEM					:   win10
 *	Create Data				:	2019.3.20
 *	Author/Corportation		:	ed1son
 *
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *
 *
 ***************************************************************************************/

 /**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/

#ifndef DULINKEDLIST_H_INCLUDED
#define DULINKEDLIST_H_INCLUDED

/**************************************************************
*	Macro Define Section
**************************************************************/

#define OVERFLOW -1

/**************************************************************
*	Struct Define Section
**************************************************************/
#define DuLNodePtr DuLinkedList
#define DuLNodeLength sizeof(DuLNode)
// define element type
typedef int ElemType; 

// define struct of linked list
typedef struct DuLNode { 
	ElemType data; 
  	struct DuLNode *prior,  *next; 
} DuLNode, *DuLinkedList;

// define status
typedef enum Status { 
	ERROR,
	SUCCESS, 
} Status;

Status InitList_DuL(DuLinkedList *L){
	DuLNodePtr head = (struct DuLNode*)malloc(DuLNodeLength);
	DuLNodePtr p = (struct DuLNode*)malloc(DuLNodeLength);
	head->next = NULL;
	head->prior = NULL; 
//	p = head;//pָ��ͷ��� 
	ElemType num;
	printf("�����������ڵ��ֵ(����0��ֹͣ����):\n");
	scanf("%d",&num);
	p->data = num;
	head->next = p;
	p->prior = head;
	while(num){
		DuLNodePtr s = (DuLNodePtr)malloc(DuLNodeLength);
		p->next = s;
		s->prior = p;
		if(!s)	return ERROR;
		s->next = NULL; 
		p->data = num;
		p = s;
		scanf("%d",&num);//����0Ҳ����ֵ����һ���
	} 
    (*L) = head;
	return SUCCESS;
}

void Printdata(DuLinkedList L){
	DuLNodePtr p = L->next;
	if(!p)	printf("���������ڡ�\n");
	else {
		printf("��ʱ�������������Ϊ��\n");
	    while(p->next != NULL){
			printf("%d ",p->data);
			p = p->next;
        }
	printf("\n");	
	}
}

void DestroyList_DuL(DuLinkedList *L){
	DuLNodePtr p,q;
	p = (*L);
	q = p->next;//ѭ���ж�������p�ĳ�q
	while(q != NULL){
		free(p);
		p = q;
		q = q->next;	
	}
	free(q);
}

DuLNode* LocatePtr(DuLinkedList L,ElemType e){
	DuLNode *p = L->next;

	while(p->next){
		if(p->data == e){
			return p;
		}
		p = p->next;
	} 
	return NULL;
}

Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q){//q���뵽pǰ 
	if(!p)	return ERROR;
	q->next = p;		//�ȸ㶨q�ĺ�̺�ǰ�� 
	q->prior = p->prior;
	p->prior->next = q;	//�ٸ㶨ǰ���ĺ�� 
	p->prior = q;      	//�ͺ����ǰ��
	
	return SUCCESS;
}

Status InsertAfterList_DuL(DuLNode *p, DuLNode *q){
	if(!p)	return ERROR;
	q->prior = p;
	q->next = p->next;
	p->next->prior = q;
	p->next = q;
	
	return SUCCESS;
}

Status DeleteList_DuL(DuLNode *p, ElemType *e){
	DuLNode *q; 
	q = p->next;
	p->next = q->next;//��q�ĺ�̸���qǰ���ĺ��
	q->next->prior = p;//ǰ���������� 
	*e = q->data; 
	free(q);
	
	return SUCCESS;
}

void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)){
	void Visit(ElemType e);
	DuLNode *p = L->next; 
	void (*q)(ElemType) = Visit;
	printf("���������ƽ���������Ϊ��\n");
	while(p->next != NULL){
		(*q)(p->data);
		p = p->next;
	}
	printf("\n");
}

void Visit(ElemType e)
{
	printf("%d ",e*e); 
}
void show(DuLinkedList head){

	DuLinkedList p = head;
	while(p){
		
		printf("prev=%d p=%d next=%d data=%d\n",p->prior,p,p->next,p->data);
		p=p->next;
	}
	
	
}
/*************************************************************
**************************************************************/
#endif 