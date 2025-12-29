/* 线性表的单链表表示*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "llist.h"


LinkList createNullList_link( void )
/* 创建一个带头结点的空链表 */
{  
	LinkList llist;
	llist = (LinkList)malloc( sizeof( struct Node ) );		/* 申请表头结点空间 */
    if( llist != NULL )
		llist->link = NULL;
	else
		printf("Out of space!!\n");
	return (llist);
}

int isNullList_link(LinkList llist)
/* 判断llist带有头结点的单链表是否是空链表 */
{
	if (llist == NULL)
		return(1);
	else
		return (llist->link == NULL);

}

PNode locate_link(LinkList llist, DataType x)
/* 在llist带有头结点的单链表中找第一个值为x的结点存储位置 */
{
	PNode p;
	if (llist==NULL)  return(NULL);
	p = llist->link;
	while( p != NULL && p->info != x )
		p = p->link;
	return (p);
}

int insertPost_link(LinkList llist, PNode p, DataType x) {
/* 在带头结点的单链表 llist 中，在 p 所指结点之后插入值为 x 的新结点 */
	PNode q = (PNode)malloc(sizeof(struct Node));	/*申请新结点*/ 
	if (q == NULL) {
		printf("Out of Space!\n");  
		return 0;
	}
	else {
		q->info = x;
		q->link = p->link;
		p->link = q;
		return 1;
	}
}

PNode locatePre_link (LinkList llist, PNode p)
/*在带有头结点的单链表 llist 中,求 p 所指结点的前驱结点存储位置*/
{ 
	PNode p1;
	if(llist==NULL)
		return NULL;
	p1 = llist;
	while(p1 != NULL && p1->link != p) 
		p1 = p1->link; 
	return p1;
}

// int insertPre_link(LinkList llist, PNode p, DataType x)
// /* 在带头结点的单链表 llist 中，在 p 所指结点之前插入值为 x 的新结点 */
// {
// 	PNode pre, q = (PNode)malloc(sizeof(struct Node));	/*申请新结点*/ 
// 	if (q == NULL) {
// 		printf("Out of Space!\n");  
// 		return 0;
// 	}
// 	else {
// 		pre = locatePre_link(llist, p); /* 找到 p 的前驱结点 */
// 		if (pre == NULL) {
// 			printf("未找到前驱！\n");
// 			free(q);
// 			return 0;
// 		}
// 		q->info = x;
// 		q->link = pre->link;
// 		pre->link = q;
// 		return 1;
// 	}
// }

int insertPre_link(LinkList llist, DataType value, DataType x)
/* 在带头结点的单链表 llist 中，在值为 value 的结点之前插入值为 x 的新结点 */
{
    if (llist == NULL) {  
        printf("链表不存在！\n");
        return 0;
    }
    PNode p = locate_link(llist, value);	// 找到值为 value 的结点位置
    if (p == NULL) {
        printf("未找到值为 %d 的结点！\n", value);
        return 0;
    }
    PNode pre = locatePre_link(llist, p);   // 找到前驱
    if (pre == NULL) {
        printf("未找到前驱！\n");
        return 0;
    }
    PNode q = (PNode)malloc(sizeof(struct Node));    // 申请新结点
    if (q == NULL) {
        printf("Out of Space!\n");  
        return 0;
    }

    q->info = x;
    q->link = pre->link;
    pre->link = q;
    return 1;
}

int deleteNode_link(LinkList llist, PNode p)
/* 在带头结点的单链表 llist 中删除 p 所指结点 */
{
    if (llist == NULL || p == NULL || llist->link == NULL) {
        printf("链表为空或结点不存在！\n");
        return 0;
    }

    PNode pre = locatePre_link(llist, p);
    if (pre == NULL) {
        printf("未找到前驱结点！\n");
        return 0;
    }

    pre->link = p->link;
    free(p);
    return 1;
}

int deleteIndex_link(LinkList llist, int i)
/* 删除带头结点的单链表 llist 中下标为 i 的结点 */
{
    if (llist == NULL || i < 0) {
        printf("链表为空或下标不合法！\n");
        return 0;
    }

    PNode pre = llist;       // 前驱结点，从头结点开始
    PNode p = llist->link;   // 当前结点，跳过头结点
    int index = 0;

    // 遍历找到下标为 i 的结点
    while (p != NULL && index < i) {
        pre = p;
        p = p->link;
        index++;
    }

    if (p == NULL) {
        printf("下标 %d 超出链表长度！\n", i);
        return 0;
    }

    // 删除结点
    pre->link = p->link;
    free(p);

    return 1;
}


int deleteV_link(LinkList llist, DataType x)
/* 在带头结点的单链表 llist 中删除第一个元素值为 x 的结点 */
{    
    PNode p, q;	
    p = llist;
    if(p==NULL) return 0 ;
    while( p->link != NULL && p->link->info != x )
      p = p->link;	/*找值为x的结点的前驱结点的存储位置 */     
    if( p->link == NULL ) {	/* 没找到值为x的结点 */
        printf("Not exist!\n ");	
		return 0 ;
	}
    else {
    	q = p->link;	//p的后继
        p->link = q->link;	//p的后继的后继
		free(q);
		return 1;
    } 

}

void deletLink_(LinkList llist)
{
	PNode p, pre, q; int n = 0; //printflist(llist);

	p = llist->link;
	for (; (p != NULL) && (p->link != NULL); p = p->link)
	{
		n++;
		pre = p;
		for (q = p->link; q != NULL; )
		{
			if (p->info == q->info)
			{
				pre->link = q->link;
				q = q->link; 
			}
			else
			{
				pre = pre->link;
				q = q->link;
			}
		}
	}
}

void printList_link(LinkList llist)
/* 打印单链表中所有结点的值 */
{
    if (llist == NULL) {
        printf("Not exist!\n");
        return;
    }

    PNode p = llist->link;   // 跳过头结点
    if (p == NULL) {
        printf("Empty list!\n");
        return;
    }

    while (p != NULL) {
        printf("%d ", p->info);
        p = p->link;
    }
    printf("\n");
}

int length_link(LinkList llist)
/* 求链表中元素个数 */
{
    if (llist == NULL) return 0;

    int c = 0;
    PNode p = llist->link;   // 跳过头结点
    while (p != NULL) {
        c++;
        p = p->link;
    }
    return c;
}


LinkList initList_link(int n)
{
	PNode p;
	LinkList llist = createNullList_link();
	p = llist; 
	int i;
	DataType x;
	printf("链表的输入%d个数据：\n", n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &x);
		insertPost_link(llist, p, x);
		p = p->link;
	}
	return llist;
}

void expandList_link(LinkList palist, LinkList pblist)
/* 将 pblist 中存在但 palist 中不存在的元素插入 palist 尾部 */
{
    if (palist == NULL || pblist == NULL) {
        printf("Not exist!\n");
        return;
    }

    PNode pb = pblist->link;   // 跳过头结点
    PNode pa_tail = palist;    // 指向 palist 尾部

    // 找到 palist 尾结点
    while (pa_tail->link != NULL)
        pa_tail = pa_tail->link;

    // 遍历 pblist
    while (pb != NULL) {
        if (locate_link(palist, pb->info) == NULL) {	// 如果 palist 中没有当前元素
            insertPost_link(palist, pa_tail, pb->info);
            pa_tail = pa_tail->link;  // 更新尾指针
        }
        pb = pb->link;
    }
}

LinkList mergeList_link(LinkList palist, LinkList pblist, LinkList pclist)
/* 构建 palist 和 pblist 的交集链表 pclist（有序且无重复） */
{
    PNode pa = palist->link;
    PNode pb = pblist->link;
    PNode pc_tail = pclist;  // pclist 的尾指针

    while (pa != NULL && pb != NULL)
    {
        if (pa->info < pb->info)
		{
			insertPost_link(pclist, pc_tail, pa->info);
			pa = pa->link;
            pc_tail = pc_tail->link;
		}
        else if (pa->info > pb->info)
		{
			insertPost_link(pclist, pc_tail, pb->info);
			pb = pb->link;
            pc_tail = pc_tail->link;
		}
		else
		{
			insertPost_link(pclist, pc_tail, pa->info);
			pa = pa->link;
			pb = pb->link;
			pc_tail = pc_tail->link;
		}
    }

	while (pa != NULL) {
        insertPost_link(pclist, pc_tail, pa->info);
        pc_tail = pc_tail->link;
        pa = pa->link;
    }
    while (pb != NULL) {
        insertPost_link(pclist, pc_tail, pb->info);
        pc_tail = pc_tail->link;
        pb = pb->link;
    }

    return pclist;
}


int main()
{
	/*
	int i,n = 0;
	LinkList list;
	printf("输入链表的长度");
	scanf("%d", &n);
	list = initList_link(n);
	printf("当前链表的元素为:");
	printList_link(list);
	*/

	/* 以下为链表作业（第三周）
	
	printf("当前链表的元素为:");
	printList_link(list);

	int c = length_link(list);
	printf("链表的长度为: %d\n", c);

	printf("请输入要插入的结点值和元素:");
	DataType value, x;
	scanf("%d %d", &value, &x);
	insertPre_link(list, value, x);
	printf("插入后链表的元素为:");
	printList_link(list);

	printf("请输入要删除的元素:");
	DataType x;
	scanf("%d", &x);
	PNode p = locate_link(list, x);
	deleteNode_link(list, p);
	printf("删除后链表的元素为:");
	printList_link(list);

	printf("请输入要删除结点的下标：");
	int index;
	scanf("%d", &index);
	deleteIndex_link(list, index);
	printf("删除后链表的元素为:");
	printList_link(list);

	*/

	/*
	int Action_choice;
	DataType x;
	list=  createNullList_link(  );
	printf("建立线性表,请输入表中数据元素,以-1 结尾:");   
	i=0;
	while(1)
	{
	  
	scanf("%d",&x);
	if(x==-1) break;
	insert_link(list,i ,x);
	i++;
	}
	*/ 
	//printflist(list); 

	/* 第三周
	LinkList palist, pblist, pclist;
    int n, m;

    printf("请输入 palist 的元素个数: ");
    scanf("%d", &n);
    palist = initList_link(n);
    printf("palist = ");
    printList_link(palist);

    printf("请输入 pblist 的元素个数: ");
    scanf("%d", &m);
    pblist = initList_link(m);
    printf("pblist = ");
    printList_link(pblist);

	// 第三周作业一
    expandList_link(palist, pblist);

    printf("\n扩展后的 palist 为: ");
    printList_link(palist);

	// 第三周作业二
	pclist = createNullList_link();
	pclist = mergeList_link(palist, pblist, pclist);

    printf("\npclist（合并结果）= ");
    prinertList_link(pclist);

	*/
    return 0;
}



 

