/* 用回溯法解决骑士周游问题的算法*/


#include<stdio.h>
#include<stdlib.h>

#define NUM 6			/*方阵为n*n的*/

#define MAXNUM NUM * NUM        /* 栈中最大元素个数 */

struct Node {
    int x, y, d;
};

typedef struct Node DataType;

struct  SeqStack {	  		/* 顺序栈类型定义 */
    int t; 			/* 指示栈顶位置 */
    DataType  s[MAXNUM];
};

typedef  struct SeqStack  *PSeqStack;	/* 顺序栈类型的指针类型 */

PSeqStack  createEmptyStack_seq( void ) {
    PSeqStack pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack==NULL)
        printf("Out of space!! \n");
    else
        pastack->t = -1;
    return  pastack;
}

int  isEmptyStack_seq( PSeqStack pastack ) {
    return pastack->t == -1;
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
DataType top_seq( PSeqStack pastack ) {
    return (pastack->s[pastack->t]);
}


int area[NUM][NUM];			/*n*n方阵*/

/*相对于位置(i,j)八个方向的增量*/
int direction[8][2] = {-1,2,-2,1,-2,-1,-1,-2,1,-2,2,-1,2,1,1,2};

int inarea(int x, int y) { /*坐标(x,y)在区域内*/
    return x >= 0 && x < NUM && y >= 0 && y < NUM;
}

void init_area(int n, int a[][n]) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            a[i][j] = 0;/*初始化,0表示未游历过*/
}

void path(int x0, int y0) { /*初始位置为(x0,y0)*/
    int i, j, k;
    int g, h;
    int step;/*所游历的区域数*/
    DataType element;
    PSeqStack st = createEmptyStack_seq( );
    init_area(NUM, area);

    area[x0][y0] = 1; /*1表示此位置游历过*/
    element.x = x0;	  
    element.y = y0;
    element.d = -1;
    push_seq(st, element);   						/* 初始点进栈 */
    step = 1;
    do {
        element = top_seq(st);
        pop_seq(st);
        i = element.x;
        j = element.y;
        area[i][j] = 1;
        for (k = element.d+1; k < 8 && step < MAXNUM; k++) {/* 依次试探每个方向 */
            g = i + direction[k][0];
            h = j + direction[k][1];
            if (inarea(g,h) == 1 && area[g][h] == 0) {
                area[g][h] = 1;
                step++;
                element.x = i;	  
                element.y = j;
                element.d = k;
                push_seq(st, element);  			/* 进栈 */
                i = g;     							/* 下一点转换成当前点 */
                j = h;
                k = -1;
            }
        }
        if (step < MAXNUM) {
            area[i][j] = 0;
            step--;
        }
    } while(!isEmptyStack_seq(st) && step < MAXNUM);
	
    if (step < MAXNUM)
        printf("cannot find the path !\n");
    else {
        printf("the reverse path is :\n");
        printf(" %d , %d\n", g, h);
        while(!isEmptyStack_seq(st)) {
            element = top_seq(st);
            pop_seq(st);
            printf(" %d , %d\n", element.x, element.y);
        }
    }
}

int main() {
    int x0, y0;
    printf("please input the position (x0,y0) \nx0 = ");
    scanf("%d", &x0);
    printf("y0 = ");
    scanf("%d", &y0);
    path(x0, y0);
    getchar(); getchar();
    return 0;
}








