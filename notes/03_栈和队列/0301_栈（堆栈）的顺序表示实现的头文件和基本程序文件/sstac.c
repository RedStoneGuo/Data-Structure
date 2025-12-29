/* 栈的顺序表示 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#define MAXNUM 100
#include "sstack.h"

PSeqStack  createEmptyStack_seq(  ) {  
    PSeqStack pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack==NULL)
        printf("Out of space!! \n");
    else
        pastack->t = -1;
    return pastack;
}

/*判断pastack所指的栈是否为空栈，当pastack所指的栈为空栈时，则返回1，否则返回0*/
int  isEmptyStack_seq( PSeqStack pastack ) {
    return pastack->t == -1;
}

/* 在栈中压入一元素x */
void  push_seq( PSeqStack pastack, DataType x ) {  
    if( pastack->t >= MAXNUM - 1  )
        printf( "Stack Overflow! \n" );
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
DataType top_seq( PSeqStack pastack ) {
    return pastack->s[pastack->t];
}

/* 十进制转二进制 */
void tr(int d) {
    PSeqStack stack = createEmptyStack_seq();
    int num = d;
    
    // 处理0的特殊情况
    if (num == 0) {
        printf("十进制 0 的二进制表示为: 0\n");
        free(stack);
        return;
    }
    
    // 处理负数
    int isNegative = 0;
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }
    
    // 将二进制位压入栈中
    while (num > 0) {
        int r = num % 2;
        push_seq(stack, r);
        num = num / 2;
    }

     // 输出结果
    printf("十进制 %d 的二进制表示为: ", d);
    if (isNegative) {
        printf("-");
    }
    
    // 从栈中弹出并输出二进制位
    while (!isEmptyStack_seq(stack)) {
        printf("%d", top_seq(stack));
        pop_seq(stack);
    }
    printf("\n");
    
    free(stack);
}

/* 递归实现斐波那契数列 */
int fib(int n) {
    if (n == 0 || n == 1) return n;
    return fib(n - 1) + fib(n - 2);
}

/* 使用栈的非递归实现斐波那契数列 */
int fib_stack(int n) { 
    PSeqStack stack = createEmptyStack_seq();
    int result = 0;
    
    // 将初始问题压入栈中
    push_seq(stack, n);
    
    while (!isEmptyStack_seq(stack)) {
        int current = top_seq(stack);
        pop_seq(stack);
        
        if (current == 0) {
            // fib(0) = 0，不需要额外处理
            continue;
        } else if (current == 1) {
            // fib(1) = 1，累加到结果中
            result += 1;
        } else {
            // 将 fib(n-1) 和 fib(n-2) 压入栈中
            push_seq(stack, current - 2);
            push_seq(stack, current - 1);
        }
    }
    
    free(stack);
    return result;
}

/* 更高效的非递归实现（迭代法） */
int fib_iterative(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}


int  main()
{
    /* 测试函数 */
    // PSeqStack m;
    // m = createEmptyStack_seq();
    // printf("请输入 入栈的数字，以 回车 结束：");
    // int d;
    // while (d != '\n')
    // {
    //     push_seq(m, d);
    //     d = getchar();
    // }
    // printf("当前栈的全部元素为：\n");
    // while (!isEmptyStack_seq(m))
    // {
    //     printf("%c ", top_seq(m));
    //     pop_seq(m);
    // }

    /* 十进制转二进制 */
    // int d;
    // printf("请输入一个要转换的十进制数字：");
    // scanf("%d", &d);
    // tr(d);
	// return 0;

    /* 斐波那契数列 */
    // int n;
    // printf("斐波那契数列项数 n: ");
    // scanf("%d", &n);
    // printf("递归函数: fib(%d) = %d\n", n, fib(n));
    // printf("栈: fib(%d) = %d\n", n, fib_stack(n));


}

