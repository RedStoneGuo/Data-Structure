/* 线性表的单链表表示：函数实现*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* 定义链接表元素类型。应根据需要定义 */
typedef struct{float f;int n;}  DataType;

struct Node;					  /* 单链表结点类型 */
typedef  struct Node  *PNode;	  /* 结点指针类型 */
typedef  struct Node  *LinkList;  /* 单链表类型 */

struct  Node { 					  /* 单链表结点结构 */
    DataType  info;
    PNode     link;
};

/* 创建一个带头结点的空链表 */
LinkList createNullList_link( void );

/* 在llist带头结点的单链表中下标为i的(第i+1个)结点前插入元素x */
int insert_link(LinkList llist, int i, DataType x);

/* 在llist带有头结点的单链表中删除第一个值为x的结点 */
int  delete_link( LinkList llist, DataType x );

/* 在llist带有头结点的单链表中找第一个值为x的结点存储位置 */
PNode  locate_link(LinkList llist, DataType x );

/* 在带有头结点的单链表llist中求下标为i的(第i+1个)结点的存储位置 */
/* 当表中无下标为i的(第i+1个)元素时，返回值为NULL */
PNode  find_link( LinkList llist, int i );

/* 判断llist带有头结点的单链表是否是空链表 */
int  isNullList_link( LinkList llist);


/* 创建一个带头结点的空链表 */
LinkList  createNullList_link( void ) {   
    LinkList llist;
    llist = (LinkList)malloc( sizeof( struct Node ) );	/* 申请表头结点空间 */
    if( llist != NULL ) llist->link = NULL;
    return llist;
}

/* 在llist带头结点的单链表中下标为i的(第i+1个)结点前插入元素x */
int insert_link(LinkList llist, int i, DataType x) { 
    PNode p = llist, q;
    int j;
    for (j = 0 ; p != NULL && j < i; j++)		/* 找下标为i-1的(第i个)结点 */
        p = p->link;
 	  
    if (j != i) {								/* i<1或者大于表长 */
        printf("Index of link-list is out of range.\n");
  	 	return 0;
    }
 	  
    q = (PNode)malloc( sizeof( struct Node ) );	/* 申请新结点 */
    if( q == NULL ) { 
        printf( "Out of space!\n" );
        return 0;
    }
    									/* 插入链表中 */
    q->info = x;
    q->link = p->link;
    p->link = q;						/* 注意该句必须在上句后执行 */
    return 1 ;
}
int insertPost_link(LinkList llist,PNode p , DataType x) { 
    PNode q = (PNode)malloc( sizeof( struct Node ) );	/* 申请新结点 */
    if( q == NULL ) { 
        printf( "Out of space!\n" );
        return 0;
    }
    									/* 插入链表中 */
    q->info = x;
    q->link = p->link;
    p->link = q;						/* 注意该句必须在上句后执行 */
    return 1 ;
}

int insertEnd_link(LinkList llist,  DataType x) { 
    PNode q =llist;
    while(q->link!=NULL)
    q=q->link ;
    insertPost_link(  llist,q ,   x);
}
/* 在llist带有头结点的单链表中删除第一个值为x的结点 */
/* 这时要求 DataType 可以用 != 比较 */
int delete_link( LinkList llist, DataType x ) { 
    PNode p = llist, q;      	
    /*找值为x的结点的前驱结点的存储位置 */
    while( p->link != NULL && p->link->info.n != x.n  )
       	
    if( p->link == NULL ) {  	/* 没找到值为x的结点 */
        printf("Datum does not exist!\n ");
        return 0;
    }
    
    q = p->link;	  			/* 找到值为x的结点 */
    p->link = p->link->link;  	/* 删除该结点 */
    free( q );      
    return 1; 
}

/* 在llist带有头结点的单链表中找第一个值为x的结点存储位置 */
/* 找不到时返回空指针 */
PNode locatePre_link( LinkList llist, PNode p ) { 
    PNode p1;
    p1=llist;
    
    while ( p1!=NULL&&p1->link!=p)
        p = p->link;
    return p1;
}

/* 在带有头结点的单链表llist中下标为i的(第i+1个)结点的存储位置 */
/* 当表中无下标为i的(第i+1个)元素时，返回值为NULL */
PNode find_link( LinkList llist, int i ) { 
    PNode p;
    int j;
    if (i < 0) {					/* 检查i的值 */
        printf("Index of link-list is out of range.\n");
        return NULL;
    }
	  
    for ( p = llist->link, j = 0; p != NULL && j < i; j++) 
        p = p->link;

    if (p == NULL) 
        printf("Index of link-list is out of range.\n");

    return p;
}

/* 判断llist带有头结点的单链表是否是空链表 */
int  isNullList_link( LinkList llist) {     
    return llist == NULL || llist->link == NULL;
    
    
}

int length(LinkList list)
{
	int n=0;
	PNode p=list->link;
	while(!p)
	{n++;p=p->link;
	}
	return n;
	
} 
DataType retrive(LinkList llist,int i)
{
	int j;
	PNode p=llist;
	for(j=1;j<=i;j++)
	p=p->link;
	return p->info;
	
}
void ADD(LinkList f,LinkList g,LinkList s) 
{  
	 DataType  a,b,x; 
     int i=1,j=1; 
     while(i<=length(f) && j<=length(g) ) 
	 {     
		 a=retrive(f,i); b=retrive(g,j); 
         if(a.n == b.n) 
			 {      
				     x.f=a.f+b.f; 
                     if(x.f!=0)  
						 insertEnd_link( s,  x) ; 
					 i++;  j++; 
			} 
            else {
				if(a.n > b.n) { insertEnd_link(s,  a) ; i++ ; }  
				else{ insertEnd_link(s,  b) ; j++;} 
			 } 
		for(;i<=length(f);i++) {
			 a = retrive (f  , i); 
			 insertEnd_link(s,  a) ;
		 } 
        for(;j<=length(g) ; j++) {
		     b=retrive (g,j);  insertEnd_link( s,b);  
	     } 
      }  
}

//printf	
	
	
	
	
	  
main(){
	int i, j; int n;
	LinkList f=createNullList_link();
	LinkList g=createNullList_link();
	LinkList s=createNullList_link();
	printf("输入第一个多项式的项数");scanf("%d", &n);
	printf("输入第一个多项式,按指数从高到低的次序");
	
	DataType x;
	for(i=1;i<=n;i++) 
	{
		scanf("%f %d",&x.f ,&x.n);
		insertEnd_link(  f,    x);
		
		
		
	}
	printf("输入第二个多项式的项数"); scanf("%d", &n);
	printf("输入第二个多项式,按指数从高到低的次序");
	for(i=1;i<=n;i++) 
	{
		scanf("%f %d",&x.f ,&x.n);
		insertEnd_link(  g,    x);
		
		
		 
	}
	ADD(f,g,s);
	getchar();
}
