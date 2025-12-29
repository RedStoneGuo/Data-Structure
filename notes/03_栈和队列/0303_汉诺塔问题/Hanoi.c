#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 100

/* 顺序栈表示：类型和界面函数声明 */
typedef struct {
    int n;           // 盘子数量
    char pos1;       // 起始柱
    char pos2;       // 辅助柱  
    char pos3;       // 目标柱
    int stage;       // 阶段：0-初始，1-第一步完成，2-第二步完成
} HanoiState;

typedef HanoiState DataType;    /* 栈中元素类型 */

struct SeqStack {    /* 顺序栈类型定义 */
    int t;           /* 栈顶位置指示 */
    DataType s[MAXNUM];
};

typedef struct SeqStack SeqStack, *PSeqStack; /* 顺序栈类型和指针类型 */ 

/* 创建一个空栈 */
PSeqStack createEmptyStack_seq(void) {
    PSeqStack pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack == NULL)
        printf("Out of space!! \n");
    else
        pastack->t = -1;
    return pastack;
}

/* 判断栈是否为空 */
int isEmptyStack_seq(PSeqStack pastack) {
    return pastack->t == -1;
}

/* 在栈中压入一元素x */
void push_seq(PSeqStack pastack, DataType x) {
    if (pastack->t >= MAXNUM - 1)
        printf("Stack Overflow! \n");
    else {
        pastack->t++;
        pastack->s[pastack->t] = x;
    }
}

/* 删除栈顶元素 */
void pop_seq(PSeqStack pastack) {
    if (pastack->t == -1)
        printf("Underflow!\n");
    else
        pastack->t--;
}

/* 获取栈顶元素的值 */
DataType top_seq(PSeqStack pastack) {
    return pastack->s[pastack->t];
}

/* 移动步骤计数器 */
int step_count = 0;

/* 递归实现汉诺塔 */
void hanoi(int n, char pos1, char pos2, char pos3) {
    if (n == 1) {
        printf("步骤 %d: 将盘子 %d 从 %c -> %c\n", ++step_count, n, pos1, pos3);
        return;
    }
    
    // 第一步：将n-1个盘子从pos1->pos2，借助pos3
    hanoi(n - 1, pos1, pos3, pos2);
    
    // 第二步：将第n个盘子从pos1->pos3
    printf("步骤 %d: 将盘子 %d 从 %c -> %c\n", ++step_count, n, pos1, pos3);
    
    // 第三步：将n-1个盘子从pos2->pos3，借助pos1
    hanoi(n - 1, pos2, pos1, pos3);
}

/* 使用栈的非递归实现汉诺塔 */
void hanoi_stack_imitate(int n, char pos1, char pos2, char pos3) {
    PSeqStack stack = createEmptyStack_seq();
    step_count = 0;
    
    // 初始状态压栈
    HanoiState initial = {n, pos1, pos2, pos3, 0};
    push_seq(stack, initial);
    
    while (!isEmptyStack_seq(stack)) {
        HanoiState current = top_seq(stack);
        pop_seq(stack);
        
        if (current.n == 1) {
            // 基本情况：只有一个盘子，直接移动
            printf("步骤 %d: 将盘子 %d 从 %c -> %c\n", ++step_count, current.n, current.pos1, current.pos3);
        } else {
            switch (current.stage) {
                case 0:
                    // 第一阶段：准备执行第一步（移动n-1个盘子到辅助柱）
                    current.stage = 1;
                    push_seq(stack, current);
                    
                    // 第一步：将n-1个盘子从pos1->pos2，借助pos3
                    HanoiState step1 = {current.n - 1, current.pos1, current.pos3, current.pos2, 0};
                    push_seq(stack, step1);
                    break;
                    
                case 1:
                    // 第二阶段：执行第二步（移动第n个盘子）
                    printf("步骤 %d: 将盘子 %d 从 %c -> %c\n", ++step_count, current.n, current.pos1, current.pos3);
                    
                    // 第三阶段：准备执行第三步（移动n-1个盘子到目标柱）
                    current.stage = 2;
                    push_seq(stack, current);
                    
                    // 第三步：将n-1个盘子从pos2->pos3，借助pos1
                    HanoiState step3 = {current.n - 1, current.pos2, current.pos1, current.pos3, 0};
                    push_seq(stack, step3);
                    break;
                    
                case 2:
                    // 完成
                    break;
            }
        }
    }
    
    free(stack);
}

/* 更简洁的栈实现方法 */
void hanoi_stack(int n, char pos1, char pos2, char pos3) {
    PSeqStack stack = createEmptyStack_seq();
    step_count = 0;
    
    // 初始状态
    HanoiState state = {n, pos1, pos2, pos3, 0};
    push_seq(stack, state);
    
    while (!isEmptyStack_seq(stack)) {
        state = top_seq(stack);
        pop_seq(stack);
        
        if (state.n == 1) {
            printf("步骤 %d: 将盘子 %d 从 %c -> %c\n", ++step_count, 1, state.pos1, state.pos3);
        } else {
            if (state.stage == 0) {
                // 压栈顺序为逆序
                // 第三步：将n-1个从pos2移到pos3（借助pos1）
                HanoiState state3 = {state.n - 1, state.pos2, state.pos1, state.pos3, 0};
                push_seq(stack, state3);
                
                // 第二步：移动第n个盘子
                HanoiState state2 = {state.n, state.pos1, state.pos2, state.pos3, 1}; // stage=1表示只移动
                push_seq(stack, state2);
                
                // 第一步：将n-1个从pos1移到pos2（借助pos3）
                HanoiState state1 = {state.n - 1, state.pos1, state.pos3, state.pos2, 0};
                push_seq(stack, state1);
            } else {
                // 直接移动盘子
                printf("步骤 %d: 将盘子 %d 从 %c -> %c\n", ++step_count, state.n, state.pos1, state.pos3);
            }
        }
    }
    
    free(stack);
}

/* 演示函数 - 显示汉诺塔问题的递归分解 */
void demonstrate_hanoi(int n, char pos1, char pos2, char pos3, int depth) {
    for (int i = 0; i < depth; i++) printf("  ");
    printf("hanoi(%d, %c, %c, %c)\n", n, pos1, pos2, pos3);
    
    if (n == 1) {
        for (int i = 0; i < depth + 1; i++) printf("  ");
        printf("移动盘子 1 从 %c 到 %c\n", pos1, pos3);
        return;
    }
    
    // 第一步
    for (int i = 0; i < depth + 1; i++) printf("  ");
    printf("第一步: 将 %d 个盘子从 %c -> %c (借助 %c)\n", n-1, pos1, pos2, pos3);
    demonstrate_hanoi(n - 1, pos1, pos3, pos2, depth + 1);
    
    // 第二步
    for (int i = 0; i < depth + 1; i++) printf("  ");
    printf("第二步: 移动盘子 %d 从 %c 到 %c\n", n, pos1, pos3);
    
    // 第三步
    for (int i = 0; i < depth + 1; i++) printf("  ");
    printf("第三步: 将 %d 个盘子从 %c -> %c (借助 %c)\n", n-1, pos2, pos3, pos1);
    demonstrate_hanoi(n - 1, pos2, pos1, pos3, depth + 1);
}

int main() {
    int n;

    printf("请输入盘子数量 n: ");
    scanf("%d", &n);

    printf("递归：\n");
    hanoi(n, 'A', 'B', 'C');

    printf("\n栈：\n");
    hanoi_stack(n, 'A', 'B', 'C');

    printf("\n递归分解演示：\n");
    demonstrate_hanoi(n, 'A', 'B', 'C', 0);
    
    return 0;
}