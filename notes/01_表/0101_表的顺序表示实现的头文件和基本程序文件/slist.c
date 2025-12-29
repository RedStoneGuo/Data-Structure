/* 线性表的顺序表示：函数实现*/
#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

#define _CRT_SECURE_NO_WARNINGS 
/* SeqList.c*/
/*线性表的顺序表示：函数实现*/

PSeqList createNullList_seq(int m) {
/* 创建新的顺序表 */
    PSeqList palist = (PSeqList)malloc(sizeof(struct SeqList));
  	if (palist!=NULL){
     palist->element = (DataType*)malloc(sizeof(DataType)*m);
 	 if (palist->element){
       palist->MAXNUM=m;
       palist ->n = 0;					/* 空表长度为0 */
       return (palist);
      }
   	else free(palist);
    }
    printf("Out of space!!\n");    	/* 存储分配失败 */
    return NULL;
}


int  isNullList_seq( PSeqList palist ) {
/*判别palist所指顺序表是否为空表。*/
    return ( palist->n == 0 );
}


int  locate_seq( PSeqList palist, DataType x ){
/*在顺序表中寻找第一个值为x的元素的下标*/
	int  q;
	for ( q=0; q<palist->n ; q++) if ( palist->element[q] == x)  return (q);
	return  (-1);
}

int insertPre_seq(PSeqList palist,int p,DataType x)  {
/*在下标为p的元素之前，插入一个值为x的元素*/
	int q;
	if ( palist->n >= palist-> MAXNUM ) {			/* 溢出 */
		printf("Overflow!\n");
		return ( 0 );
		}
	if ( isNullList_seq(palist) ) {			/*空顺序表插入 */
		palist->element[0] = x;					/* 插入元素x */
		palist->n = 1;				/* 元素个数为1 */
		return ( 1 );
		}
	if (p<0  ||  p>palist->n  )	{  			/* 不存在下标为p的元素 */
		printf("Not exist! \n");  
		return (0 );
		}
	for(q=palist->n - 1; q>=p; q--)  /* 插入位置及之后的元素均后移一个位置 */
		palist->element[q+1] = palist->element[q];
	palist->element[p] = x;					/* 插入元素x */
	palist->n = palist->n + 1;				/* 元素个数加1 */
	return ( 1 );
}

int insertPost_seq(PSeqList palist, int p, DataType x) {
	/*在下标为p的元素之后，插入一个值为x的元素*/
    int q;
    if (palist->n >= palist->MAXNUM) { /* 溢出检查 */
        printf("Overflow!\n");
        return 0;
    }
    if (isNullList_seq(palist)) { /* 空表处理 */
        palist->element[0] = x;
        palist->n = 1;
        return 1;
    }
    if (p < -1 || p >= palist->n) { /* 修正位置有效性判断：p最大为n-1 */
        printf("Not exist! \n");
        return 0;
    }
    // 元素移动范围从p+1开始（原p位置元素无需移动）
    for (q = palist->n - 1; q > p; q--) { 
        palist->element[q + 1] = palist->element[q];
    }
    palist->element[p + 1] = x; /* 在p位置后插入元素 */
    palist->n = palist->n + 1;
    return 1;
}

int  deleteP_seq( PSeqList palist, int p )
/* 在palist所指顺序表中删除下标为ｐ的元素 */
{
	int q;
	if (  p<0  ||  p>palist->n - 1 )	
		{
		   printf("Not exist!\n ");
		   return  (0);
		 }
	for(q=p; q<palist->n-1; q++) 	/* 被删除元素之后的元素均前移一个位置 */
		palist->element[q] = palist->element[q+1];
	palist->n = palist->n - 1;			/* 元素个数减1 */
	return ( 1 );
}

int deleteV_seq(PSeqList palist, DataType x) {
/* 在palist所指顺序表中删除第一个值为x的元素 */
    int q = locate_seq(palist, x);
    if (q == -1) {  // 元素x不存在
        printf("Element %d not found!\n", x);
        return 0;
    }
    return deleteP_seq(palist, q);  // 删除下标为q的元素
}

int printList_seq( PSeqList palist )
/* 输出palist所指顺序表的所有元素 */
{
	int q;
	if ( isNullList_seq(palist) ) {
		printf("Empty list!\n");
		return ( 0 );
		}
	for ( q=0; q<palist->n ; q++)
		printf("%d ", palist->element[q]);
	printf("\n");
	return ( 1 );
}

int reverseList_seq(PSeqList palist)
/*反转线性表元素*/
{
	if (palist == NULL || isNullList_seq(palist)) {
	return 0;
    }
	int i = 0;
    int j = palist->n - 1;
    DataType temp;

	while (i < j) {
		temp = palist->element[i];
		palist->element[i] = palist->element[j];
		palist->element[j] = temp;
		i++;
		j--;
    }
	return 1;
	//参考：C 数组反转
    // int i,j,m=(n-1)/2;
    // for(i=0;i<=m;i++)
    // {   j=n-1-i;
    //     temp=x[i]; x[i]=x[j]; x[j]=temp;
    // }
}
int reverse_seq(PSeqList palist) {
    /* 将顺序表逆序排列，返回1表示成功，0表示失败 */

    
    int i = 0;                  // 头部指针
    int j = palist->n - 1;      // 尾部指针
    DataType temp;              // 临时变量用于交换
    
    // 双指针向中间靠拢并交换元素
    while (i < j) {
        // 交换i和j位置的元素
        temp = palist->element[i];
        palist->element[i] = palist->element[j];
        palist->element[j] = temp;
        
        // 移动指针
        i++;
        j--;
    }
    
    return 1;   // 反转成功
}

DataType minElement_seq(PSeqList palist) {
    /* 查找顺序表中的最小元素，返回最小元素值；空表返回-1 */
    if (isNullList_seq(palist)) {
        printf("Error: Empty list!\n");
        return -1;
    }
    
    DataType min_val = palist->element[0];  // 初始化为第一个元素
    for (int i = 1; i < palist->n; i++) {   // 遍历
        if (palist->element[i] < min_val) {
            min_val = palist->element[i];   // 更新最小值
        }
    }
    return min_val;
}

int deleteAllX_seq(PSeqList palist, DataType x) {
/* 删除顺序表中所有值为x的元素 */   
    if (isNullList_seq(palist)) {
        return 1;  // 空表无需删除，返回成功
    }
    
    int i = 0;

    for (int j = 0; j < palist->n; j++) {
        if (palist->element[j] != x) {
            palist->element[i] = palist->element[j];
            i++;
        }
    }
    
    palist->n = i;
    return 1;
}

DataType retrive_seq(PSeqList list,int p)
{
	if(p >= 0 && p < list->n)
		return(list->element[p]);
	return(-1);

}

PSeqList initList_seq(int n)
{
	PSeqList palist = createNullList_seq(100);
	int i;	//添加数据位置
	DataType x;
	printf("线性表的输入%d个数据\n", n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &x);
		insertPre_seq(palist, palist->n, x);
		
	}
		return palist;
}
 
int main()
{
	int n=0; DataType x;
	PSeqList palist;
	printf("输入线性表的长度");
	scanf("%d", &n);
	palist = initList_seq(n);	//初始化线性表，并赋给 palist
	printf("当前线性表的元素为:");
	printList_seq(palist);

	/* 以下为顺序表作业（第二周）
	printf("请输入要插入的位置和元素:");	
	int p;
	scanf("%d %d", &p, &x);
	insertPost_seq(palist, p, x); 
	printf("插入后线性表的元素为:");
	printList_seq(palist);

	printf("请输入要删除的元素:");
	scanf("%d", &x);
	deleteV_seq(palist, x);
	printf("删除后线性表的元素为:");
	printList_seq(palist);

	reverseList_seq(palist);
	printf("反转后线性表的元素为:");
	printList_seq(palist);

	int q = minElement_seq(palist);
	if(q != -1)
	printf("当前表最小的元素为：%d",q);

	printf("请输入要删除的元素:");
	scanf("%d", &x);
	deleteAllX_seq(palist, x);
	printf("删除后线性表的元素为:");
	printList_seq(palist);
	*/

    //DataType x;
	//int i,p;
	/***for(p=0;p<10;p++)
	{
		scanf("%d ", &x);
		insertPre_seq( palist, p, x);

	}
	printf("请输入表中数据元素,以-1 结尾:");
	i = 0; 
	while (1)
	{


		scanf("%d", &x);
		if (x == -1) break;
		insertPre_seq(palist, n, x);
		n++;
	}***/
	
}

    






	
