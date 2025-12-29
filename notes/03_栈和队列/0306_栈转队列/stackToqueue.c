#include<stdlib.h>
#include<stdio.h>

#define MAXNUM 100

/* 统一使用存储单一数值的结构体 */
typedef struct {
    int value;  // 存储单一数值
} DataType;

/* 队列定义 */
struct SeqQueue {
    int f, r;
    DataType q[MAXNUM];
};
typedef struct SeqQueue SeqQueue, *PSeqQueue;

/* 栈定义 */
struct SeqStack {
    int t;
    DataType s[MAXNUM];
};
typedef struct SeqStack SeqStack, *PSeqStack;

/* 队列操作 */
PSeqQueue createEmptyQueue_seq(void) {  
    PSeqQueue paqu = (PSeqQueue)malloc(sizeof(struct SeqQueue));
    if (paqu == NULL)
        printf("Out of space!! \n");
    else
        paqu->f = paqu->r = 0;
    return paqu;
}

int isEmptyQueue_seq(PSeqQueue paqu) {
    return paqu->f == paqu->r;
}

void enQueue_seq(PSeqQueue paqu, DataType x) {
    if ((paqu->r + 1) % MAXNUM == paqu->f)
        printf("Full queue.\n");
    else {
        paqu->q[paqu->r] = x;
        paqu->r = (paqu->r + 1) % MAXNUM;
    }
}

void deQueue_seq(PSeqQueue paqu) {
    if (paqu->f == paqu->r)
        printf("Empty Queue.\n");
    else
        paqu->f = (paqu->f + 1) % MAXNUM;
}

DataType frontQueue_seq(PSeqQueue paqu) {
    return paqu->q[paqu->f];
}

void printQueue(PSeqQueue queue) {
    if (isEmptyQueue_seq(queue)) {
        printf("队列为空\n");
        return;
    }
    
    printf("队列内容 (从队头到队尾): ");
    int current = queue->f;
    int count = 0;
    
    while (current != queue->r) {
        printf("%d", queue->q[current].value);
        current = (current + 1) % MAXNUM;
        count++;
        if (current != queue->r) printf(" -> ");
    }
    printf("\n队列中共有 %d 个元素\n", count);
    printf("队头指针 f = %d, 队尾指针 r = %d\n", queue->f, queue->r);
}

/* 栈操作 */
PSeqStack createEmptyStack_seq(void) {  
    PSeqStack pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack == NULL)
        printf("Out of space!! \n");
    else
        pastack->t = -1;
    return pastack;
}

int isEmptyStack_seq(PSeqStack pastack) {
    return pastack->t == -1;
}

void push_seq(PSeqStack pastack, DataType x) {
    if (pastack->t >= MAXNUM - 1)
        printf("Stack Overflow! \n");
    else {
        pastack->t++;
        pastack->s[pastack->t] = x;
    }
}

void pop_seq(PSeqStack pastack) {
    if (pastack->t == -1)
        printf("Underflow!\n");
    else
        pastack->t--;
}

DataType top_seq(PSeqStack pastack) {
    return pastack->s[pastack->t];
}

void printStack(PSeqStack stack) {
    if (isEmptyStack_seq(stack)) {
        printf("栈为空\n");
        return;
    }
    
    printf("栈内容 (从栈底到栈顶): ");
    for (int i = 0; i <= stack->t; i++) {
        printf("%d", stack->s[i].value);
        if (i < stack->t) printf(" -> ");
    }
    printf("\n栈顶指针 t = %d\n", stack->t);
}

/* 栈转队列函数 */
PSeqQueue stackToQueue(PSeqStack stack) {
    PSeqQueue queue = createEmptyQueue_seq();
    
    // 将原栈的所有元素入队
    while (!isEmptyStack_seq(stack)) {
        DataType element = top_seq(stack);
        enQueue_seq(queue, element);
        pop_seq(stack);
        // printf("从原栈弹出 %d 入队\n", element.value);
    }

    return queue;
}

/* 栈转队列函数_正序 */
PSeqQueue stackToQueue_re(PSeqStack stack) {
    PSeqQueue queue = createEmptyQueue_seq();
    PSeqStack tempStack = createEmptyStack_seq();
    
    printf("开始栈转队列...\n");
    
    // 第一步：将原栈的所有元素压入临时栈（反转顺序）
    printf("第一步：将原栈元素压入临时栈（反转顺序）\n");
    while (!isEmptyStack_seq(stack)) {
        DataType element = top_seq(stack);
        push_seq(tempStack, element);
        pop_seq(stack);
        printf("从原栈弹出 %d 压入临时栈\n", element.value);
    }
    
    // 第二步：将临时栈的所有元素出栈并入队（恢复原栈顺序）
    printf("第二步：将临时栈元素出栈并入队\n");
    while (!isEmptyStack_seq(tempStack)) {
        DataType element = top_seq(tempStack);
        enQueue_seq(queue, element);
        pop_seq(tempStack);
        printf("从临时栈弹出 %d 入队\n", element.value);
    }
    
    free(tempStack);
    return queue;
}

/* 批量测试不同情况 */
void comprehensiveTest() {
    printf("\n\n========== 综合测试 ==========\n");
    
    // 测试1：空栈转换
    printf("\n--- 测试1：空栈转换 ---\n");
    PSeqStack emptyStack = createEmptyStack_seq();
    PSeqQueue emptyQueue = stackToQueue(emptyStack);
    printf("空栈转换结果:\n");
    printQueue(emptyQueue);
    free(emptyStack);
    free(emptyQueue);
    
    // 测试2：单个元素
    printf("\n--- 测试2：单个元素 ---\n");
    PSeqStack singleStack = createEmptyStack_seq();
    DataType elem;
    elem.value = 100;
    push_seq(singleStack, elem);
    printf("原栈状态:\n");
    printStack(singleStack);
    PSeqQueue singleQueue = stackToQueue(singleStack);
    printf("转换后队列状态:\n");
    printQueue(singleQueue);
    free(singleStack);
    free(singleQueue);
    
    // 测试3：多个元素
    printf("\n--- 测试3：多个元素 ---\n");
    PSeqStack multiStack = createEmptyStack_seq();
    for (int i = 1; i <= 8; i++) {
        elem.value = i * 5;
        push_seq(multiStack, elem);
    }
    printf("原栈状态:\n");
    printStack(multiStack);
    PSeqQueue multiQueue = stackToQueue(multiStack);
    printf("转换后队列状态:\n");
    printQueue(multiQueue);
    free(multiStack);
    free(multiQueue);
}

int main() {    
    // 创建测试栈并压入数据
    PSeqStack stack = createEmptyStack_seq();
    DataType element;
    
    printf("创建测试栈并压入数据:\n");
    for (int i = 1; i <= 5; i++) {
        element.value = i * 10;
        push_seq(stack, element);
        printf("压栈: %d\n", element.value);
    }
    
    printf("\n原栈状态:\n");
    printStack(stack);
    
    // 执行栈转队列
    printf("\n--- 执行栈转队列 ---\n");
    PSeqQueue queue = stackToQueue(stack);
    
    printf("\n转换后队列状态:\n");
    printQueue(queue);
    printf("原栈是否为空: %s\n", isEmptyStack_seq(stack) ? "是" : "否");
    
    // 释放内存
    free(stack);
    free(queue);

    // comprehensiveTest();
    return 0;
}