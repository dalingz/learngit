/***************************************************************************************
 *	File Name				:	linkedList.h
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
#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

/**************************************************************
*	Macro Define Section
**************************************************************/

#define OVERFLOW -1

/**************************************************************
*	Struct Define Section
**************************************************************/

// define element type
typedef int ElemType; 

// define struct of linked list
typedef struct LNode { 
	ElemType data; 
  	struct LNode *next; 
} LNode, *LinkedList;

// define Status
typedef enum Status { 
	ERROR,
	SUCCESS
} Status;
#define LNodePtr LinkedList
#define LNodeLength sizeof(LNode)
/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : Status InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList(LinkedList *L)
{
	LNodePtr head = (struct LNode*)malloc(LNodeLength);
	LNodePtr p = (struct LNode*)malloc(LNodeLength);
	(*L) = head;//����ָ��ָ���Lͷָ�븳��head 
	head->next = p;
	ElemType num;
	printf("����������ڵ��ֵ(����0��ֹͣ����):\n");
	scanf("%d",&num);
	p->data = num;
	while(num){
		p->next = (LNodePtr)malloc(LNodeLength);
		scanf("%d",&num);//����0Ҳ����ֵ����һ��� 
		p = p->next;
		p->data = num;
	} 
	p->next = NULL;
	return SUCCESS;
} 

void Printdata(LinkedList L){
	LNodePtr p;
	p = L->next;
	if(!p)	printf("�������ڡ�\n");
	else {
		printf("��ʱ������������Ϊ��\n");
	    while(p->next != NULL){
			printf("%d ",p->data);
			p = p->next;
	}
	printf("\n");	
	}
}
void DestroyList(LinkedList *L){
	LNodePtr p,q;
	p = (*L);
	q = p->next; 
	while(p != NULL){
		free(p);
		p = q;
		q = q->next;	
	}
	free(q);
}
Status InsertList(LNode *p, LNode *q){
	if(!p)	return ERROR;//p=NULL���˳� 
	
	q->next = p->next;//���¾�˳�򲻿ɵߵ������������ж�  
	p->next = q;
	
	return SUCCESS;
}

void Plus(LinkedList L){//ֱ�۱���������Ĳ��� 
	printf("������������ֵ:\n");
	ElemType a;
	scanf("%d",&a);
	LNodePtr q = (LNodePtr)malloc(LNodeLength);
	q->data = a;
	printf("����������뵽�ĸ�ֵ��\n");
	scanf("%d",&a);
	LNodePtr p = LocatePtr(L,a);
	InsertList(p,q);
}

LNode* LocatePtr(LinkedList L,ElemType e){
	LNode *p = L->next;
	/*
	while(p->next != NULL){
		if(p->data == e)  return p; 
		p = p->next;
	}
	*/
	while(p->next){
		if(p->data == e){
			return p;
		}
		p = p->next;
	} 
	return NULL;
}

Status DeleteList(LNode *p, ElemType *e){
	
	LNodePtr q;
	q = p->next;
	*e = q->data;
	p->next = q->next;//��q�ĺ��ֵ����p�ĺ�� 
//	printf("\n------%d %d %d %d-------\n",p->data,q->data,p->next->data,q->next->data);
	
	free(q);

	return SUCCESS;
}

void Settle(LinkedList L){
	ElemType a;
	ElemType *e;

    printf("��������ɾ���ĸ�ֵ���ֵ��\n");
    scanf("%d",&a);
    LNodePtr p = LocatePtr(L,a);
	
    //printf("%d",p->data);
	DeleteList(p,e);
	
	printf("��ʱ�������ָ�루e��ָ���ֵΪ��%d\n",*e);
}

int LinkedListLength(LinkedList L){
	LNodePtr p = L;
	int t = 1;
	while(!p->next){
		p = p->next;
		t++;
	}
	return t;
}
void TraverseList(LinkedList L, void (*visit)(ElemType e)){
	LNode *p = L->next; 
	void (*q)(ElemType) = Twice;//�������������ƽ������Ϊ�� 
	printf("���������ƽ���������Ϊ��\n"); 
	while(p->next != NULL){
		(*q)(p->data);
		p = p->next;
	}
	printf("\n");
} 
void Twice(ElemType e)
{
	printf("%d ",e*e);
}

Status SearchList(LinkedList L, ElemType e){
	LNode *p = L->next;
	printf("����������Ҳ�����\n");
	scanf("%d",&e);
	while(p->next != NULL){
		if(p->data == e)  return SUCCESS; 
		p = p->next;
	}
	return ERROR;
} 

Status ReverseList(LinkedList *L){
	if(!(*L))  return ERROR;
	//LNode *p1 = (*L)->next,*p2,*p3;//�������ý���������ָ�� 
	LNode *p1 = (*L),*p2,*p3;
	p2 = p1->next;
	p3 = p2->next; 
	/*
	while(p3){
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
	*/
	p1->next = NULL;		//����ͷ���,���ú�Ϊβ��� 
	
	while(p3){
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
    p2->next = p1;        	//�޸�L��ָ����Lָ���µ�ͷ���
    (*L) = p2;
	return SUCCESS;
}
Status IsLoopList(LinkedList L){
	LNodePtr p = L->next,q = L->next;
	while(p && p->next){
		p = p->next;
		if(p){
			p = p->next;
		}	
		q = q->next;
		if(p == q){
			printf("������ڻ�\n");
			return SUCCESS;	
		}
//		else if(p < q){
//			printf("����ɻ�\n");
//			return SUCCESS;
//		}	
	}
	
	printf("�������ڻ�\n");
	return ERROR;
}

LNode* FindMidNode(LinkedList *L){
	int t = 1;//������ 
	LNodePtr p = *L;
	while(p->next){
		p = p->next;
		t++;
	}
	if(t % 2 == 0)	return NULL;
	p = *L;
	t = t/2;
	while(t--){
		p = p->next;
	} 
	return p;
} 

void ExpressMid(LinkedList *L){
	LNodePtr p = FindMidNode(L); 
	if(p) 	printf("�����м����ֵΪ%d��\n",p->data);
	else	
	printf("��������Ϊż�����޷����һ���м���ֵ��\n");
} 

void show(LNodePtr head){
	LNodePtr p = head;
	while(p){
		
		printf("p=%d p->next=%d p->data=%d\n",p,p->next,p->data);
		p=p->next;
	}

 /**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif 
