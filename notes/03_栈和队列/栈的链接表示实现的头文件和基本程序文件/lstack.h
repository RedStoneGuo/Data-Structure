/* 栈链接表示：类型和界面函数声明 */

typedef int DataType;
struct  Node;					/* 单链表结点 */
typedef  struct Node  *PNode;	/* 指向结点的指针类型 */

struct  Node {                   /* 单链表结点结构 */
    DataType info;
    PNode    link;
};

struct LinkStack {               /* 链接栈类型定义 */
    PNode top;		            /* 指向栈顶结点 */
};

typedef  struct LinkStack  *PLinkStack;	 /* 链接栈类型的指针类型 */

/*申请链栈结构空间，创建一空链接栈，返回指向空链接栈的指针*/
PLinkStack  createEmptyStack_link(void);

/*判单链形式栈是否为空栈*/
int  isEmptyStack_link( PLinkStack plstack );

/* 在栈中压入一元素x */
void push_link( PLinkStack plstack, DataType x );

/*出栈*/
void  pop_link( PLinkStack plstack );

/* 对非空栈求栈顶元素 */
DataType  top_link( PLinkStack plstack );

