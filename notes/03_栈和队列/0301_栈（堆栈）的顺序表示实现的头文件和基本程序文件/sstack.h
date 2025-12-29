/* 顺序栈表示：类型和界面函数声明 */
typedef int DataType; /* 栈中元素类型，应根据需要定义 */

struct SeqStack {	  /* 顺序栈类型定义 */
    int  t; 		  /* 栈顶位置指示 */
    DataType  s[MAXNUM];
};

typedef  struct SeqStack SeqSack, *PSeqStack;	/* 顺序栈类型和指针类型 */ 

/*创建一个空栈;为栈结构申请空间，并将栈顶变量赋值为-1*/
PSeqStack  createEmptyStack_seq( void );

/*判断pastack所指的栈是否为空栈，当pastack所指的栈为空栈时，则返回1，否则返回0*/
int  isEmptyStack_seq( PSeqStack pastack );

/* 在栈中压入一元素x */
void  push_seq( PSeqStack pastack, DataType x );

/* 删除栈顶元素 */
void  pop_seq( PSeqStack pastack );

/* 当pastack所指的栈不为空栈时，求栈顶元素的值 */
DataType  top_seq( PSeqStack pastack );

