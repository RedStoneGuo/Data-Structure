/* 简化背包问题的递归算法*/

#include<stdio.h>
#include<stdlib.h>

int knap(int s, int n, int w[]) {
    if ( s == 0 )
        return (1);
    else if ( s<0 || s>0 && n<1 )
        return(0);
    else if ( knap(s - w[n-1], n - 1, w)==1 ) { 
        printf("result: n=%d ,w[%d]=%d  \n", n, n-1, w[n-1]);
        return (1);
    }
    else
        return ( knap(s, n - 1, w) );
}

int main() {
    int* w;
    int s = 0, n = 0, result = 0, i = 0;
    printf("please  input s = ");/*输入s*/
    scanf("%d", &s);
    printf("please  input n = ");/*输入n*/
    scanf("%d", &n);
    w = (int*)malloc(n*sizeof(int));
    printf("please input the %d numbers(weight):\n", n);/*输入重量*/
    for (i = 0; i < n; i++)
        scanf("%d", w+i);
    result = knap(s, n, w);
    if (result == 0)
        printf("no solution!\n");
    return 0;
}


       
