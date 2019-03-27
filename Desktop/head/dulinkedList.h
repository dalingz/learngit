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
//	p = head;//p指向头结点 
	ElemType num;
	printf("请输入链表节点的值(输入0则停止输入):\n");
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
		scanf("%d",&num);//输入0也将赋值给下一结点
	} 
    (*L) = head;
	return SUCCESS;
}

void Printdata(DuLinkedList L){
	DuLNodePtr p = L->next;
	if(!p)	printf("链表不存在。\n");
	else {
		printf("此时链表各结点数据为：\n");
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
	q = p->next;//循环判断条件从p改成q
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

Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q){//q插入到p前 
	if(!p)	return ERROR;
	q->next = p;		//先搞定q的后继和前驱 
	q->prior = p->prior;
	p->prior->next = q;	//再搞定前结点的后继 
	p->prior = q;      	//和后结点的前驱
	
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
	p->next = q->next;//将q的后继赋给q前驱的后继
	q->next->prior = p;//前驱处理类似 
	*e = q->data; 
	free(q);
	
	return SUCCESS;
}

void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)){
	void Visit(ElemType e);
	DuLNode *p = L->next; 
	void (*q)(ElemType) = Visit;
	printf("各结点数据平方后的链表为：\n");
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
