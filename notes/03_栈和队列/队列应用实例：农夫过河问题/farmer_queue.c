/* 用队列解决农夫过河问题的算法*/


#include<stdio.h>
#include<stdlib.h>

#define  MAXNUM   20

typedef int DataType;
struct  SeqQueue {		/* 顺序队列类型定义 */
    int  f, r;
    DataType q[MAXNUM];
};

typedef struct SeqQueue *PSeqQueue;	/* 顺序队列类型的指针类型 */

PSeqQueue createEmptyQueue_seq( void ) {  
    PSeqQueue paqu = (PSeqQueue)malloc(sizeof(struct SeqQueue));
    if (paqu == NULL)
        printf("Out of space!! \n");
    else
        paqu->f = paqu->r = 0;
    return (paqu);
}

int isEmptyQueue_seq( PSeqQueue paqu ) {
    return paqu->f == paqu->r;
}

/* 在队列中插入一元素x */
void  enQueue_seq( PSeqQueue paqu, DataType x ) {
    if ( (paqu->r + 1) % MAXNUM == paqu->f  )
        printf( "Full queue.\n" );
    else {
        paqu->q[paqu->r] = x;
        paqu->r = (paqu->r + 1) % MAXNUM;
    }
}

/* 删除队列头部元素 */
void  deQueue_seq( PSeqQueue paqu ) {
    if( paqu->f == paqu->r )
        printf( "Empty Queue.\n" );
    else
        paqu->f = (paqu->f + 1) % MAXNUM;
}

/* 对非空队列,求队列头部元素 */
DataType  frontQueue_seq( PSeqQueue paqu ) {
    return (paqu->q[paqu->f]);
}

int farmer(int location) {
    return 0 != (location & 0x08);
}

int wolf(int location) {
    return 0 != (location & 0x04);
}

int cabbage(int location) {
    return 0 != (location & 0x02);
}

int goat(int location) {
    return 0 !=(location & 0x01);
}

/* 若状态安全则返回true */
int safe(int location) {
    /* 羊吃白菜 */
    if ((goat(location) == cabbage(location)) &&  
          (goat(location) != farmer(location)) )  
        return 0;
    /* 狼吃羊 */
    if ((goat(location) == wolf(location)) &&  
          (goat(location) != farmer(location)))  
        return 0;
    return 1;	 /* 其他状态是安全的 */
}


void farmerProblem( ) {
    int movers, i, location, newlocation;
    int route[16];        /*记录已考虑的状态路径*/
    PSeqQueue moveTo; 
    /*准备初值*/
    moveTo = createEmptyQueue_seq( );
    enQueue_seq(moveTo, 0x00);
    for (i = 0; i < 16; i++) route[i] = -1;
    route[0]=0;
    
    /*开始移动*/
    while (!isEmptyQueue_seq(moveTo)&&(route[15] == -1)) {
        /*得到现在的状态*/
        location = frontQueue_seq(moveTo);
        deQueue_seq(moveTo);
        for (movers = 1; movers <= 8; movers <<= 1) {
            /* 农夫总是在移动，随农夫移动的也只能是在农夫同侧的东西 */
            if ((0 != (location & 0x08)) == (0 != (location & movers))) {
                newlocation = location^(0x08|movers);
                if (safe(newlocation) && (route[newlocation] == -1)) { 
                    route[newlocation] = location;
                    enQueue_seq(moveTo, newlocation);
                }
            }
        }
    }
    
    /* 打印出路径 */
    if(route[15] != -1) {
        printf("The reverse path is : \n");
        for(location = 15; location >= 0; location = route[location]) { 
            printf("The location is : %d\n",location);
            if (location == 0) return;
        }
    }
    else 
        printf("No solution.\n");
}


int main() {
    farmerProblem( );
    return 0;
}
