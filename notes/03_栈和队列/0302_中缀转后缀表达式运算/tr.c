#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXNUM 100

// 栈结构
typedef struct {
    int data[MAXNUM];
    int top;
} Stack;

// 初始化栈
void initStack(Stack *s) {
    s->top = -1;
}

// 判断栈空
int isEmpty(Stack *s) {
    return s->top == -1;
}

// 入栈
void push(Stack *s, int value) {
    if (s->top >= MAXNUM - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    s->data[++(s->top)] = value;
}

// 出栈
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return s->data[(s->top)--];
}

// 获取栈顶元素
int peek(Stack *s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->data[s->top];
}

// 复制栈内容用于显示（不修改原栈）
void copyStack(Stack *src, Stack *dest) {
    dest->top = src->top;
    for (int i = 0; i <= src->top; i++) {
        dest->data[i] = src->data[i];
    }
}

// 显示栈内容（字符栈）
void printCharStack(Stack *s) {
    if (isEmpty(s)) {
        printf("空");
        return;
    }
    Stack temp;
    copyStack(s, &temp);
    while (!isEmpty(&temp)) {
        printf("%c ", pop(&temp));
    }
}

// 显示栈内容（数字栈）
void printIntStack(Stack *s) {
    if (isEmpty(s)) {
        printf("空");
        return;
    }
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
    }
}

// 运算符优先级
int precedence(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// 中缀转后缀
void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int i = 0, j = 0;
    char token;
    
    printf("中缀转后缀过程:\n");
    printf("当前字符\t栈内容\t\t输出\n");
    
    while ((token = infix[i]) != '\0') {
        if (isdigit(token)) {
            // 处理多位数
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--; // 回退一位，因为外层循环会i++
            
            // 输出当前状态
            printf("%c\t\t", token);
            printCharStack(&s);
            printf("\t\t%s\n", postfix);
        }
        else if (token == '(') {
            push(&s, token);
            printf("%c\t\t", token);
            printCharStack(&s);
            printf("\t\t%s\n", postfix);
        }
        else if (token == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            pop(&s); // 弹出'('
            
            printf("%c\t\t", token);
            printCharStack(&s);
            printf("\t\t%s\n", postfix);
        }
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(token)) {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            push(&s, token);
            
            printf("%c\t\t", token);
            printCharStack(&s);
            printf("\t\t%s\n", postfix);
        }
        i++;
    }
    
    // 弹出栈中剩余运算符
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
    
    printf("结束\t\t空\t\t%s\n", postfix);
}

// 计算后缀表达式
int evaluatePostfix(char* postfix) {
    Stack s;
    initStack(&s);
    int i = 0;
    
    printf("\n计算后缀表达式过程:\n");
    printf("当前字符\t栈内容\t\t计算说明\n");
    
    while (postfix[i] != '\0') {
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            push(&s, num);
            
            printf("%d\t\t", num);
            printIntStack(&s);
            printf("\t\t压栈\n");
        }
        else if (postfix[i] == ' ') {
            i++;
        }
        else {
            int b = pop(&s);
            int a = pop(&s);
            int result;
            char op = postfix[i];
            
            switch (op) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                default: result = 0;
            }
            
            push(&s, result);
            
            printf("%c\t\t", op);
            printIntStack(&s);
            printf("\t\t%d %c %d = %d\n", a, op, b, result);
            i++;
        }
    }
    
    return pop(&s);
}

int main() {
    char infix[] = "(2+3*5)*3+5";
    char postfix[100] = {0}; // 初始化为0
    
    printf("原始中缀表达式: %s\n\n", infix);
    
    infixToPostfix(infix, postfix);
    printf("\n后缀表达式: %s\n", postfix);
    
    int result = evaluatePostfix(postfix);
    printf("\n最终结果: %d\n", result);
    
    return 0;
}