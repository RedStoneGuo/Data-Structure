/* 队列的顺序表示：函数定义 */
#include<stdlib.h>
#include<stdio.h>
#include "squeue.h"

/*创建一个空队列*/
PSeqQueue  createEmptyQueue_seq( void ) {  
    PSeqQueue paqu = (PSeqQueue)malloc(sizeof(struct SeqQueue));
    if (paqu==NULL)
        printf("Out of space!! \n");
    else
        paqu->f = paqu->r = 0;
    return paqu;
}

/*判队列是否为空队列*/
int  isEmptyQueue_seq(PSeqQueue paqu) {
    return paqu->f == paqu->r;
}

/* 在队列中插入一元素x */
void enQueue_seq( PSeqQueue paqu, DataType x ) {
    if( (paqu->r + 1) % MAXNUM == paqu->f  )
        printf( "Full queue.\n" );
    else 	{
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
    return paqu->q[paqu->f];
}

/* 原始迷宫数据 */
int original_maze[M][N] = {
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

int direction[][2] = {{0,1},{1,0},{0,-1},{-1,0}};   

void mazePath(int x1, int y1, int x2, int y2) {
	int i, j, k, g, h; 
	int pre; int x,y;
	PSeqQueue plqu;  
	DataType element;

	//创建迷宫副本
	int maze[M][N];
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			maze[i][j] = original_maze[i][j];
		}
	}
	
	// 检查起点和终点合法性
	if (x1 < 0 || x1 >= M || y1 < 0 || y1 >= N || maze[x1][y1] == 1) {
		printf("起点(%d,%d)不可达！\n", x1, y1);
		return;
	}
	if (x2 < 0 || x2 >= M || y2 < 0 || y2 >= N || maze[x2][y2] == 1) {
		printf("终点(%d,%d)不可达！\n", x2, y2);
		return;
	}

	plqu = createEmptyQueue_seq();
	maze[x1][y1] = -1;
	element.x = x1;
	element.y = y1;  
	enQueue_seq(plqu, element);
	int found = 0;
	while (! isEmptyQueue_seq(plqu)){
	element =  frontQueue_seq( plqu );
	deQueue_seq(plqu);
	i = element.x;
	j = element.y;
	for(k=0;k<=3;k++)
	{
		g=i+direction[k][0];
		h=j+direction[k][1];
		if (g >= 0 && g < M && h >= 0 && h < N && maze[g][h] == 0)
		{
			maze[g][h]=i*N+j;
			if(g==x2 && h==y2)
			{
				found = 1; 
				goto label;
			}
			element.x=g;
			element.y=h;
			enQueue_seq(plqu,element);
			}
		}			
	}

	    if (!found) {
        printf("从(%d,%d)到(%d,%d)的路径未找到！\n", x1, y1, x2, y2);
        free(plqu);
        return;
    }
	
label:
	printf("找到路径 (从终点到起点):\n");
	printf("\t(%d,%d)",x2,y2);
	int ns=1;
	pre=maze[x2][y2];
	while(pre!=-1)
	{
		x = pre / N;
		y = pre % N;
		printf("\t(%d,%d)",x,y);
		pre=maze[x][y];
		ns=ns+1;
		if (ns%5==0)
            printf("\n");
	}
	printf("\n" );
	free(plqu);
             
}

/* 打印迷宫 */
void printMaze(int x1, int y1, int x2, int y2) {
    printf("迷宫地图 ( □ = 通路, ■ = 墙, ● = 起点, ○ = 终点):\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (i == x1 && j == y1) printf("●");
            else if (i == x2 && j == y2) printf("○");
            else if (original_maze[i][j] == 1) printf("■");
            else printf("  ");
        }
        printf("\n");
    }
}

/* 打印队列中的所有元素 */
void printQueue_seq(PSeqQueue paqu) {
    if (isEmptyQueue_seq(paqu)) {
        printf("队列为空\n");
        return;
    }
    
    printf("队列内容 (从队头到队尾):\n");
    int current = paqu->f;
    int count = 0;
    
    while (current != paqu->r) {
        printf("[%d] -> (%d, %d)\n", count, paqu->q[current].x, paqu->q[current].y);
        current = (current + 1) % MAXNUM;
        count++;
    }
    
    printf("队列中共有 %d 个元素\n", count);
    printf("队头指针 f = %d, 队尾指针 r = %d\n", paqu->f, paqu->r);
}

int main()
{
	// // 测试1：正常路径
	// printf("\n测试1: 从(1,1)到(8,8)\n");
	// printMaze(1, 1, 8, 8);
	// mazePath(1, 1, 8, 8);

	// // 测试2：起点终点相同
	// printf("\n测试2: 起点终点相同\n");
	// mazePath(1, 1, 1, 1);

	// // 测试3：不可达终点
	// printf("\n测试3: 到墙的位置\n");
	// mazePath(1, 1, 0, 0);

	// // 测试4：另一个可达路径
	// printf("\n测试4: 从(1,1)到(1,8)\n");
	// printMaze(1, 1, 1, 8);
	// mazePath(1, 1, 1, 8);

	// /* 以下为打印函数测试 */ 
	PSeqQueue queue = createEmptyQueue_seq();
    DataType element;
    
    printf("初始队列状态:\n");
    printQueue_seq(queue);
    
    for (int i = 0; i < 5; i++) {
		printf("\n输入入队第 %d 个元素:\n", i + 1);
		printf("请输入 x 坐标: ");
		scanf("%d", &element.x);
		printf("请输入 y 坐标: ");
		scanf("%d", &element.y);
		enQueue_seq(queue, element);
		printf("入队: (%d, %d)\n", element.x, element.y);
	}
	printQueue_seq(queue);

	return 0;

}
