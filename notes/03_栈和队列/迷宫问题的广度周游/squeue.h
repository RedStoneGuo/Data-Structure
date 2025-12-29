/* 队列的顺序表示：类型和函数声明 */
//typedef int DataType;
#define MAXNUM 200  //队列中最大元素个数
#define M 10
#define N 10

typedef struct
{
    int x,y;            //方块的位置
     //本路径中上一方块在队列中的下标
} DataType; 
struct  SeqQueue {	/* 顺序队列类型定义 */
    int f, r;
    DataType q[MAXNUM];
};

typedef struct SeqQueue SeqQueue, *PSeqQueue;	/* 顺序队列类型和指针类型 */

/*创建一个空队列*/
PSeqQueue createEmptyQueue_seq( void );

/*判队列是否为空队列*/
int isEmptyQueue_seq( PSeqQueue paqu );

/* 在队列中插入一元素x */
void enQueue_seq( PSeqQueue paqu, DataType x );

/* 删除队列头部元素 */
void deQueue_seq( PSeqQueue paqu );

/* 对非空队列,求队列头部元素 */
DataType frontQueue_seq( PSeqQueue paqu );

