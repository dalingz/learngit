#include <stdio.h>
#include <stdlib.h>

typedef int ElemType; 

typedef struct LNode { 
	ElemType data; 
  	struct LNode *next; 
} LNode, *LinkedList;
#define LNodePtr LinkedList
#define LNodeLength sizeof(LNode)
#define OVERFLOW -1
// define Status
typedef enum Status { 
	ERROR,
	SUCCESS
} Status;


Status InitList(LinkedList *L);
void Printdata(LinkedList L);
void DestroyList(LinkedList *L);
Status InsertList(LNode *p, LNode *q);
Status DeleteList(LNode *p, ElemType *e); 
Status SearchList(LinkedList L, ElemType e);
Status ReverseList(LinkedList *L);
Status IsLoopList(LinkedList L);
LNode* FindMidNode(LinkedList *L);
void TraverseList(LinkedList L, void (*visit)(ElemType e));
void show(LNodePtr head);
int LinkedListLength(LinkedList L); 
void Twice(ElemType e);
void Plus(LinkedList L);
void Settle(LinkedList L);
void ExpressMid(LinkedList *L);
LNode* LocatePtr(LinkedList L,ElemType e);
int main() {
	LinkedList p;
	ElemType e;
	InitList(&p); 
	Printdata(p);

    Plus(p);// ������������㺯��
    Printdata(p); 
    //show(p);
	Settle(p);//��������ɾ����㺯��
	Printdata(p); 
	//show(p);
	if(SearchList(p,e)==SUCCESS)
	printf("�������ҵ�����������\n");
	else	printf("�������������С�\n"); 
	
	if(ReverseList(&p)==SUCCESS)//�������� 
	printf("-----����������-----\n"); 
	Printdata(p);
	
	TraverseList(p,Twice);//��������õ������� 
	
	IsLoopList(p);//�ж������Ƿ���ڻ��������ɻ���
	 
	ExpressMid(&p);//��ʾ���м���Ľ�� 
	 
	DestroyList(&p);//�������� 
	Printdata(p);   //��ʱ���޽����Ϣ���룬��������� 
	return 0;
}

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
/*

ElemType i,j; 
	LNode *q,*head;
	typedef struct LNode *LinkedList;
	head=p;
	printf("��������ɾ�����q��λ��:\n");
	scanf("%d ",&i);
	if(i>LinkedListLength(LinkedList L))
	printf("����λ�ó����������Χ��\n");
	else
	for(j=1;j<i;i--){//ѭ����iΪp->next��� 
		p=p->next;
	}
	if(!p->next){
		printf("��ɾ����㲻����\n");
		return ERROR;
	}
	LNode *head;
	ElemType i,j,plusdata;
	typedef struct LNode *LinkedList;
	head=p; //����ͷ��� 
	printf("�����������ڵ�q��λ�úͲ����ֵ:\n");
	scanf("%d %d",&i,&plusdata);
	if(i>LinkedListLength(L))
	printf("����λ�ó����������Χ��\n");
	else
	for(j=1;j<i;i--){
		p=p->next;
	}
*/


void show(LNodePtr head){
	LNodePtr p = head;
	while(p){
		
		printf("p=%d p->next=%d p->data=%d\n",p,p->next,p->data);
		p=p->next;
	}
	
	
	
}
