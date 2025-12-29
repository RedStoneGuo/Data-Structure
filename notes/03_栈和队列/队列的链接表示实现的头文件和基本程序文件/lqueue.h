/*队列链接表示：类型和界面函数声明*/

typedef int DataType;
struct  Node;
typedef  struct Node *PNode;

struct  Node { 		/* 结点结构 */
    DataType    info;
    PNode       link;
};

struct  LinkQueue {	/* 链接队列类型定义 */	
    PNode  f;  		/* 头指针 */
    PNode  r;  		/* 尾指针 */
};

typedef struct LinkQueue *PLinkQueue;

/*创建一个空队列*/
PLinkQueue  createEmptyQueue_link( );

/*判断链接表示队列是否为空队列*/ 
int  isEmptyQueue_link( PLinkQueue plqu );

/*进队列*/
void  enQueue_link( PLinkQueue plqu, DataType x);

/*出队列*/
void  deQueue_link( PLinkQueue plqu );

/* 在非空队列中求队头元素 */
DataType  frontQueue_link( PLinkQueue plqu );

