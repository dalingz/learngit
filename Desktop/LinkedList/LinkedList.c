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

    Plus(p);// 调用链表插入结点函数
    Printdata(p); 
    //show(p);
	Settle(p);//调用链表删除结点函数
	Printdata(p); 
	//show(p);
	if(SearchList(p,e)==SUCCESS)
	printf("链表中找到给定参数！\n");
	else	printf("参数不在链表中。\n"); 
	
	if(ReverseList(&p)==SUCCESS)//链表逆置 
	printf("-----链表已逆置-----\n"); 
	Printdata(p);
	
	TraverseList(p,Twice);//将链表调用到函数中 
	
	IsLoopList(p);//判断链表是否存在环（包括成环）
	 
	ExpressMid(&p);//显示找中间结点的结果 
	 
	DestroyList(&p);//链表销毁 
	Printdata(p);   //此时已无结点信息传入，所以无输出 
	return 0;
}

Status InitList(LinkedList *L)
{
	LNodePtr head = (struct LNode*)malloc(LNodeLength);
	LNodePtr p = (struct LNode*)malloc(LNodeLength);
	(*L) = head;//二级指针指向的L头指针赋给head 
	head->next = p;
	ElemType num;
	printf("请输入链表节点的值(输入0则停止输入):\n");
	scanf("%d",&num);
	p->data = num;
	while(num){
		p->next = (LNodePtr)malloc(LNodeLength);
		scanf("%d",&num);//输入0也将赋值给下一结点 
		p = p->next;
		p->data = num;
	} 
	p->next = NULL;
	return SUCCESS;
} 

void Printdata(LinkedList L){
	LNodePtr p;
	p = L->next;
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
	if(!p)	return ERROR;//p=NULL，退出 
	
	q->next = p->next;//与下句顺序不可颠倒，否则链表中断  
	p->next = q;
	
	return SUCCESS;
}

void Plus(LinkedList L){//直观表现链表结点的插入 
	printf("请输入需插入的值:\n");
	ElemType a;
	scanf("%d",&a);
	LNodePtr q = (LNodePtr)malloc(LNodeLength);
	q->data = a;
	printf("请输入需插入到哪个值后：\n");
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
	p->next = q->next;//将q的后继值赋给p的后继 
//	printf("\n------%d %d %d %d-------\n",p->data,q->data,p->next->data,q->next->data);
	
	free(q);

	return SUCCESS;
}

void Settle(LinkedList L){
	ElemType a;
	ElemType *e;

    printf("请输入需删除哪个值后的值：\n");
    scanf("%d",&a);
    LNodePtr p = LocatePtr(L,a);
	
    //printf("%d",p->data);
	DeleteList(p,e);
	
	printf("此时链表外的指针（e）指向的值为：%d\n",*e);
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
	void (*q)(ElemType) = Twice;//以输出链表数据平方函数为例 
	printf("各结点数据平方后的链表为：\n"); 
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
	printf("请输入需查找参数：\n");
	scanf("%d",&e);
	while(p->next != NULL){
		if(p->data == e)  return SUCCESS; 
		p = p->next;
	}
	return ERROR;
} 

Status ReverseList(LinkedList *L){
	if(!(*L))  return ERROR;
	//LNode *p1 = (*L)->next,*p2,*p3;//链表逆置借助三连续指针 
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
	p1->next = NULL;		//处理头结点,逆置后为尾结点 
	
	while(p3){
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
    p2->next = p1;        	//修改L的指向，让L指向新的头结点
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
			printf("链表存在环\n");
			return SUCCESS;	
		}
//		else if(p < q){
//			printf("链表成环\n");
//			return SUCCESS;
//		}	
	}
	
	printf("链表不存在环\n");
	return ERROR;
}

LNode* FindMidNode(LinkedList *L){
	int t = 1;//计数器 
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
	if(p) 	printf("链表中间结点的值为%d。\n",p->data);
	else	
	printf("链表结点数为偶数，无法输出一个中间结点值。\n");
} 
/*

ElemType i,j; 
	LNode *q,*head;
	typedef struct LNode *LinkedList;
	head=p;
	printf("请输入需删除结点q的位置:\n");
	scanf("%d ",&i);
	if(i>LinkedListLength(LinkedList L))
	printf("输入位置超过链表最大范围！\n");
	else
	for(j=1;j<i;i--){//循环后i为p->next结点 
		p=p->next;
	}
	if(!p->next){
		printf("需删除结点不存在\n");
		return ERROR;
	}
	LNode *head;
	ElemType i,j,plusdata;
	typedef struct LNode *LinkedList;
	head=p; //保留头结点 
	printf("请输入需插入节点q的位置和插入的值:\n");
	scanf("%d %d",&i,&plusdata);
	if(i>LinkedListLength(L))
	printf("输入位置超过链表最大范围！\n");
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
