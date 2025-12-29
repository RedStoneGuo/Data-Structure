#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#define MAXNUM 200

/* 顺序栈表示：类型和界面函数声明 */
typedef struct {
    int x;  // 行坐标
    int y;  // 列坐标
    int d;  // 情况
} DataType;           /* 栈中元素类型，应根据需要定义 */

struct SeqStack {	  /* 顺序栈类型定义 */
    int  t; 		  /* 栈顶位置指示 */
    DataType  s[MAXNUM];
};

typedef  struct SeqStack SeqSack, *PSeqStack;	/* 顺序栈类型和指针类型 */ 

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

/* 迷宫基础设置 & 定义 */
int M = 10, N = 10;

int maze[10][10]=
{
{1,1,1,1,1,1,1,1,1,1},
{1,0,0,1,0,0,0,1,0,1},
{1,0,0,1,0,0,0,1,0,1},
{1,0,0,0,0,1,1,0,0,1},
{1,0,1,1,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,1},
{1,0,1,0,0,0,1,0,0,1},
{1,0,1,1,1,0,1,1,0,1},
{1,1,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1}
};


int start_x = 1, start_y = 1; // 起点 (1,1)
int end_x = 8, end_y = 8;     // 终点 (8,8)

/* 方向数组 */
int direction[4][2] = 
{
    {0, 1},   // 东: (0, 1)
    {1, 0},   // 南: (1, 0)
    {0, -1},  // 西: (0, -1)
    {-1, 0}   // 北: (-1, 0)
};

void mazePath(int maze[][10], int direction[][2], int x1, int y1, int x2, int y2, int M, int N)
/* 迷宫 maze[m][n] 中求从入口 maze[x1][y1] 到出口 maze[x2][y2] 的一条路径*/
/* 其中 1 <= x1, x2 <= M-2, 1 <= y1, y2 <= N-2 */ 
{
    int i,j,k,g,h;
    PSeqStack st;
    DataType element;

    st = createEmptyStack_seq();

    maze[x1][y1] = 2;                   //标记已走过的点（此处为入口）
    element.x = x1;
    element.y = y1;
    element.d = -1;
    push_seq(st,element);               //将 入口 压栈

    while (!isEmptyStack_seq(st))       //走不通时回退一步
    {
        element = top_seq(st);
        pop_seq(st);
        i = element.x;
        j = element.y;
        k = element.d + 1;

        while (k <= 3)                  //从四个方向（东南西北）依次尝试
        {
            g = i + direction[k][0];
            h = j + direction[k][1];

            if (g==x2 && h==y2 && maze[g][h]==0)    //走到 出口 时
            {
                maze[x1][y1] = 3;             // 标记起点和终点
                maze[x2][y2] = 4;
                printf("找到的路径为：\n");    //打印试出来的完整路径
                while(!isEmptyStack_seq(st))
                {
                    element=top_seq(st);
                    pop_seq(st);
                    printf("the node is: (%d, %d) \n", element.x, element.y);
                }
                free(st);
                return;
            }

            if (maze[g][h]==0)          //走到没走过的点时
            {
                maze[g][h] = 2;         //标记为 已经走过
                element.x = i;
                element.y = j;
                element.d = k;
                push_seq(st,element);   //压栈 上一步

                i = g;                  //移到最新这步
                j = h; 
                k = -1;                 //方向重置为 -1，表示下一次从 东 方向开始尝试
            }
            k = k + 1;
        }
    }
printf("The path has not been found.\n");           //回退到起点，仍然没走到出口
free(st);
return;
}

void printMaze(int maze[][10], int M, int N) {
    printf("迷宫地图 ( □ = 通路, ■ = 墙, · = 已走路径, ● = 起点, ○ = 终点):\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (maze[i][j] == 0)      printf("  ");// 通路
            else if (maze[i][j] == 1) printf("■"); // 墙
            else if (maze[i][j] == 2) printf("·"); // 已走路径
            else if (maze[i][j] == 3) printf("●"); // 起点
            else if (maze[i][j] == 4) printf("○"); // 终点
        }
        printf("\n");
    }
}

int  main()
{    
    printf("原始迷宫:\n");
    printMaze(maze, M, N);
    
    // 备份迷宫用于求解
    int maze_copy[10][10];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            maze_copy[i][j] = maze[i][j];
        }
    }
    
    // 求解迷宫
    mazePath(maze_copy, direction, start_x, start_y, end_x, end_y, M, N);
    
    // 打印求解后的迷宫
    printf("\n求解后的迷宫:\n");
    printMaze(maze_copy, M, N);

    return 0;
}
