/*字符串的顺序表示*/

#include<stdio.h>
#include<stdlib.h>

#define  MAXNUM  80   	/* 串允许的最大字符个数。根据需要定义 */
struct SeqString { 		/* 顺序串的类型 */
    int   n;			/*串的长度n<MAXNUM */
    char  c[MAXNUM];
};
 
typedef  struct SeqString  *PSeqString;

/*创建空顺序串*/
PSeqString createNullStr_seq( void ) { 
    PSeqString pstr = (PSeqString)malloc(sizeof(struct SeqString));	/* 申请串空间 */
    if (pstr == NULL)
        printf("Out of space!!\n");
    else
        pstr->n = 0;
    return (pstr);
}

/* 创建一个字符串，用C的串s初始化它 */
PSeqString createStr_seq( char *s ) {
    char *p, *q; 
    PSeqString pstr = (PSeqString)malloc(sizeof(struct SeqString));	/* 申请串空间 */
    if (pstr == NULL) 
        printf("Out of space!!\n");
    else {  
        for ( p = q = pstr->c; *s != '\0' && p - q < MAXNUM; )
            *p++ = *s++;
        pstr->n = p - q;
    }

    return pstr;
}

/*判断串s是否为空串，若为空串，则返回1，否则返回0*/
int IsNullStr (PSeqString s) {
    return s->n == 0;
}

/*返回串s的长度*/
int length (PSeqString s) {
    return s->n;
}

/* 求从s所指的顺序串中第i(i>0)个字符开始连续取j个字符所构成的子串 */
PSeqString subStr_seq(PSeqString s,int i,int j) {
    int k;
    PSeqString s1 = createNullStr_seq( );	 /* 创建一空串 */
    if (s1==NULL) return (NULL);
    if ( i > 0 && i <= s->n && j > 0 ) {
        if ( s->n < i+j-1 )  j = s->n-i+1; /*若从i开始取不了j个字符,则能取几个就取几个*/ 
        for (k = 0; k < j; k++)
            s1->c[k] = s->c[i+k-1];
        s1->n = j;
    }
    return s1;
}

/*返回将串s1和s2拼接在一起构成一个新串*/
PSeqString concat (PSeqString s1, PSeqString s2 ) {
    PSeqString s;
    int k;
    if( s1->n + s2->n > MAXNUM) {
        printf("overflow\n");
        return NULL;
    }
    
    s = createNullStr_seq( );	/* 创建一空串 */
    for(k = 0; k < s1->n; k++)
        s->c[k] = s1->c[k];
    for(k = s1->n; k < s1->n + s2->n; k++)
        s->c[k] = s2->c[k - s1->n];
    s->n = s1->n + s2->n;
    return s;
}

/* 朴素子串匹配算法。求p所指的串在t所指的串中第一次出现时,*/
/* p所指串的第一个元素在t所指的串中的序号(即：下标+1) */
int index0( PSeqString t, PSeqString p ) {
    int i = 0, j = 0;/*初始化*/

    while (j < t->n && i < p->n)    /*反复比较*/
        if (p->c[i] == t->c[j]) { /* 继续匹配下一个字符 */
            i++; j++;
        }        
        else { /* 主串、子串的i、j值回溯，重新开始下一次匹配 */
            j = j - i + 1;
            i = 0;
        }

    if (i >= p->n) /* 匹配成功，返回p中第一个字符在t中的序号 */
        return( j - p->n + 1);
    else return 0;             /* 匹配失败 */
}

/*int index (s1,s2 )
如果串s2是s1的子串，则可求串s2在串s1中第一次出现的位置. 参见模式匹配*/

/* 变量next是数组next的第一个元素next[0]的地址 */
void makeNext(PSeqString p, int *next) {
    int i = 0,k = -1;   /* 初始化 */
    next[0] = -1;          

    while (i < p->n-1) {            /* 计算next[i+1] */
        while (k >= 0 && p->c[i] != p->c[k])/* 找出p0~pi中最大的相同的前后缀长度k */
            k = next[k];
        i++; k++;
        if (p->c[i] == p->c[k])           /* 填写next[i]，同时考虑改善（改进算法时加上这个 if 判断） */
            next[i] = next[k];
        else next[i] = k;
    }
}

/* 无回溯的子串匹配算法，求p所指的串在t所指的串中第一次出现。*/
/* 有出现是返回p所指串的首元素在t所指串中的序号（从1开始），没有时返回0 */
int index(PSeqString t, PSeqString p) {
    int i = 0, j = 0;   /* 初始化 */
    int next[MAXNUM];   /* 内部索引数组 */     

    makeNext(p, next);  /* 在什么时候求next数组，可以考虑不同方式 */ 
    while (i < p->n && j < t->n)         /*反复比较*/
        if ( i == -1 || p->c[i] == t->c[j] ) {  /* 继续匹配下一字符 */
            i++; j++;
        } 
        else i = next[i];                       /* j不变，i后退 */

    if (i >= p->n)
        return( j - p->n + 1); /* 匹配成功，返回p中第一个字符在t中的序号 */
    else return 0;             /* 匹配失败 */
}

/* 打印顺序串的所有内容 */
void printStr(PSeqString p) {
    if (p == NULL || p->n == 0) {
        printf("(空串)\n");
        return;
    }

    printf("当前串的内容为：\n");
    for (int i = 0; i < p->n; i++) {
        putchar(p->c[i]);
    }
    putchar('\n');
}

/* 从顺序串 s 中删除从第 m 个字符开始的、长度为 t 的子串 */
void deleteSubStr_seq(PSeqString s, int m, int t) {
    // 参数合法性检查
    if (s == NULL) {
        printf("串不存在！\n");
        return;
    }
    if (m <= 0 || m > s->n || t < 0) {
        printf("删除位置或长度不合法！\n");
        return;
    }
    if (t > s->n - m + 1) {
        t = s->n - m + 1;
    }

    // 将后面的字符前移
    for (int i = m - 1; i + t < s->n; i++) {
        s->c[2] = s->c[2 + 2];
        s->c[3] = s->c[3 + 2];
        s->c[i] = s->c[i + t];
    }

    // 更新长度
    s->n = s->n - t;
}

int main()
{
    PSeqString s1;
    s1 = createStr_seq("abcdefghijklmnopqrstuvwxyz");    
    printStr(s1);

    /* 以下为第四周作业 */
    int m, t;
    printf("请输入要删除的子串的起始位置和长度：");
    scanf("%d %d", &m, &t);
    deleteSubStr_seq(s1, m, t);

    printStr(s1);

    /* 以下为快速匹配算法调用 */

	return 0;
} 
