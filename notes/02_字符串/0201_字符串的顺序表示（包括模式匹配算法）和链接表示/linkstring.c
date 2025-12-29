/* 字符串的链接表示 */

#include<stdio.h>
#include<stdlib.h>

struct StrNode;						/* 链串的结点 */
typedef struct StrNode *PStrNode;	/* 结点指针类型 */

struct StrNode {  					/* 链串的结点结构 */
    char      c;
    PStrNode  link;
};

typedef  struct  StrNode  *LinkString;  	/* 链串的类型 */

/*创建带头结点的空链串*/
LinkString  createNullStr_link( void ) {   
    LinkString pst = (LinkString)malloc( sizeof(struct StrNode) );
    if (pst != NULL) pst->link = NULL;
    return (pst);
}

/*判断带头结点的串s是否为空串，若为空串，则返回1，否则返回0*/
int IsNullStr (LinkString s) {
    return (s->link==NULL);
}

/*返回串s的长度*/
int length (LinkString s) {
    int len = -1;
    LinkString p = s;
    for ( p=s; p!=NULL; p=p->link ) len++;
    return len;
}

/*返回将串s1和s2拼接在一起构成一个新串*/
LinkString concat (LinkString s1, LinkString s2 ) {
    LinkString pst, p1, p2, temp;
    pst = createNullStr_link();
    if (pst != NULL) 	{
        p1 = pst->link;
        for (p2=s1->link;p2!=NULL;p2=p2->link) {
            temp = (LinkString)malloc(sizeof(struct StrNode));  /* !! 需要检查分配情况 */
            temp->c = p2->c;
            temp->link = NULL;
            p1->link = temp;
        }
        p1 = p1->link;
        for ( p2 = s2->link; p2 != NULL; p2 = p2->link) {
            temp = (LinkString)malloc(sizeof(struct StrNode));  /* !! 需要检查分配情况 */
            temp->c = p2->c;
            temp->link = NULL;
            p1->link = temp;
        }
    }
    return pst;
}

/* 求从s所指的带头结点的链串中第i(i>0)个字符开始连续取j个字符所构成的子串 */
LinkString subStr_link(LinkString s,int i,int j) {
    PStrNode p,q,t;
    int k;
    LinkString s1 = createNullStr_link( );  /* 创建空链串 */
    if( s1 == NULL ) {	
        printf( "Out of space!\n" );
        return NULL;
    }
    if (i<1 || j<1 ) return(s1);	/* i,j值不合适，返回空串 */

    for (p = s, k = 1; k <= i; k++)  		/*找第i个结点*/
        if ( p != NULL) p = p->link;
        else return s1;
        
    if (p == NULL) return s1;

    for (t = s1, k=1; k<=j; k++) 		 /*连续取j个字符*/
        if (p != NULL) { 
            q = (PStrNode)malloc(sizeof(struct StrNode));
            if (q == NULL) { 
                printf( "Out of space!\n" );
                return(s1);
            }
            q->c = p->c;
            q->link = NULL;
            t->link = q;			/* 结点放入子链串中 */
            t = q;
            p = p->link;
        }
       
    return s1;
}


int insert_PostlinkStr(LinkString s, PStrNode p, char x) { 
    PStrNode q = (PStrNode)malloc( sizeof( struct StrNode ) );	/* 申请新结点 */
    if( q == NULL ) { 
        printf( "Out of space!\n" );
        return 0;
    }
    									/* 插入链表中 */
    q->c = x;
    q->link = p->link;
    p->link = q;						/* 注意该句必须在上句后执行 */
    return 1 ;
}
void append_insert_PostlinkStr(LinkString s,  char x){
	
	PStrNode p=s;
	while(p->link!=NULL)
	p=p->link ;
	insert_PostlinkStr( s,  p,  x);
	
}

void printf_LinkStr(LinkString s)
{
	
	PStrNode  p=s->link ;int i=0;
	printf("表中的数据为：\n");
	
	
	while(p!=NULL)
	{
		printf("%c",p->c );
		p=p->link ;i++;
		if(i%5==0)
		printf("	");
	}
	printf("\n");
	
}

/* 判断 s1 是否包含 s2，若包含返回 1，否则返回 0 */
int indexSubStr_link(LinkString s1, LinkString s2) {
    if (s1 == NULL || s2 == NULL || s2->link == NULL) return 0;

    PStrNode p = s1->link;  // 主串的当前起始位置
    PStrNode q, t;

    while (p != NULL) {
        q = p;
        t = s2->link;

        // 从当前位置开始比较两个串
        while (q != NULL && t != NULL && q->c == t->c) {
            q = q->link;
            t = t->link;
        }

        if (t == NULL)  // 若子串扫描完，说明匹配成功
            return 1;

        p = p->link;  // 主串向后移动一位
    }

    return 0;  // 没有匹配成功
}
	
void main()
{
	int i, n,  a; char x;
	LinkString s1, s2 ;
	s1 = createNullStr_link(  );
	s2 = createNullStr_link(  );
	printf("请输入表A需要存储的字符串，以& 结束作为结束标志：\n");
	while(1)
    {
        scanf("%c", &x);
        if(x>='A'&&x<='Z'||x>='a'&&x<='z')  
        append_insert_PostlinkStr(s1,  x);
        if(x=='&') break;	
	}
    printf_LinkStr(s1);
	printf("请输入表B需要存储的字符串，以& 结束作为结束标志：\n");
	while(1)
    {
        scanf("%c", &x);
        if(x>='A'&&x<='Z'||x>='a'&&x<='z')  
        append_insert_PostlinkStr(s2,  x);
        if(x=='&') break;
	}
	printf_LinkStr(s2);

    if (indexSubStr_link(s1, s2))
        printf("\nDNA片段 B 存在于 DNA片段 A 中！\n");
    else
        printf("\nDNA片段 B 不存在于 DNA片段 A 中。\n");
	
    return 0;
}
