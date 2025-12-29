/* 简化背包问题的非递归算法*/


#include<stdio.h>
#include<stdlib.h>
#define MAXNUM     20
#define TRUE 1
#define FALSE 0

struct  NodeBag {  /* 栈中元素的定义 */
    int  s , n ;
    int  r ;          /* r的值为1,2,3 */
    int  k;
};

typedef struct NodeBag DataType;

struct SeqStack {	  		/* 顺序栈类型定义 */
    int  t; 			/* 指示栈顶位置 */
    DataType  s[MAXNUM];
};

typedef struct SeqStack *PSeqStack;	/* 顺序栈类型的指针类型 */

PSeqStack  createEmptyStack_seq( void ) {
    PSeqStack pastack;
    pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack==NULL)
        printf("Out of space!! \n");
    else
        pastack->t=-1;
    return  (pastack);
}

/* 在栈中压入一元素x */
void  push_seq( PSeqStack pastack, DataType x ) {  
    if( pastack->t >= MAXNUM - 1  )
        printf( "Overflow! \n" );
    else {
        pastack->t++;
        pastack->s[pastack->t] = x;
    }
}

/* 删除栈顶元素 */
void  pop_seq( PSeqStack pastack ) {  	
    if (pastack->t == -1 )
        printf( "Underflow!\n" );
    else
        pastack->t--;
}

/* 当pastack所指的栈不为空栈时，求栈顶元素的值 */
DataType  top_seq( PSeqStack pastack ) {
    return pastack->s[pastack->t];
}

int nknap(int s, int n, int w[]) { 
    struct NodeBag  x; 
    PSeqStack st;   
    int k;
    st = createEmptyStack_seq( );        /* entry0:  初始调用入口 */
    x.s = s;     x.n = n;    x.r = 1;  
    push_seq(st,x);
entry1:                    /* 递归调用入口 */
    x = top_seq(st);
    pop_seq(st);     /* 该函数与后面最接近的一个push_seq函数对是为了完成修改栈顶元素 */
    if (x.s == 0) {  
        x.k = TRUE;       
        push_seq(st,x);         
        goto exit2; 
    }
    else if (x.s<0 || (x.s>0 && x.n<1)) {
        x.k = FALSE;
        push_seq(st,x);
        goto exit2;
    }
    else {
        push_seq(st,x);  /* 由于此处需要进一步往下递归，所以需再次入栈 */
        x.s = x.s - w[x.n-1];   
        x.n = x.n - 1;     
        x.r = 2;  
        push_seq(st, x);   
        goto entry1;
    }
exit2:                 /* 返回处理 */
    x = top_seq(st);
    pop_seq(st);
    switch (x.r) { 
    case 1:
        free(st);
        return(x.k);
    case 2: goto L3;
    case 3: goto L4; 
    }

L3:                 /* 继续处理1 */
    if (x.k == TRUE) { 
        x = top_seq(st);
        pop_seq(st); 
        x.k = TRUE;     
        push_seq(st,x);
        printf("result n=%d , w=%d \n", x.n, w[x.n-1]); 
        goto  exit2; 
    }
    else {  
        x = top_seq(st);
        x.s = x.s; 
        x.n = x.n - 1; 
        x.r = 3;  
        push_seq(st,x); 
        goto  entry1; 
    }
L4:                         /* 继续处理2 */
    k = x.k; 
    x = top_seq(st); 
    pop_seq(st);   
    x.k = k;   
    push_seq(st,x);   
    goto  exit2;
}

int main() {
    int* w;
    int s = 0, n = 0, result = 0, i = 0;
	
    printf("please  input s = ");/*输入s*/
    scanf("%d", &s);
    printf("please  input n = ");/*输入n*/
    scanf("%d", &n);
    w = (int*)malloc(n*sizeof(int));
    printf("please input the %d numbers(weight):\n", n);/*输入重量*/
    for (i = 0; i < n; i++)
        scanf("%d", w+i);
    result = nknap(s,n, w);
    if (result == 0)
        printf("no solution!\n");
    return 0;
}

