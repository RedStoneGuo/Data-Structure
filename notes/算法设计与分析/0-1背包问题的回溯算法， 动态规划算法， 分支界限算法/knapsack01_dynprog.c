/* 0/1背包问题的动态规划法算法*/


#include<stdio.h>
#include<stdlib.h>

#define ymax 100
#define nmax 100

double f[nmax][ymax];

void Knapsack(double p[], int w[], int c, int n) {
    int y = 0, i = 0;
    for (y = 0; y < ymax; y++)
        f[n][y] = 0;
    for (y = w[n]; y <= c; y++)
        f[n][y] = p[n];

    for(i = n-1; i > 1; i--) {
        for (y = 0; y < ymax; y++)
            f[i][y] = f[i+1][y];
        for (y = w[i]; y <= c; y++)
            f[i][y] = f[i+1][y] > f[i+1][y-w[i]] + p[i] ? 
                        f[i+1][y] : f[i+1][y-w[i]] + p[i];
    }
    f[1][c] = f[2][c];
    if (c >= w[1])
        f[1][c] = f[1][c] > f[2][c-w[1]] + p[1] ? 
                    f[1][c] : f[2][c-w[1]] + p[1];
}

void traceback(int w[], int c, int n, int x[]) {
    int i = 0;
    for (i = 1; i < n; i++)
        if (f[i][c] == f[i+1][c])
            x[i] = 0;
        else {
            x[i] = 1;
            c -= w[i];
        }
    x[n] = f[n][c] ? 1 : 0;
}


int main() {
    double s = 0, temp = 0; 
    double *p;
    int m = 0, n = 0, i = 0, *w, *x;
    printf("please input the maximum weight of the bag: \nm = ");
    scanf("%d", &m);
    printf("please input the number of objects:\nn = ");
    scanf("%d", &n);
    p = (double*)malloc((n+1)*sizeof(double));
    printf("please input  the prices of all the objects:\n");
    for (i = 1; i <= n; i++)
        scanf("%f", p+i);
    w = (int*)malloc((n+1)*sizeof(int));
    printf("please input  the weight of all the objects:\n");
    for (i = 1; i <= n; i++)
        scanf("%d", w+i);
	
    x = (int*)malloc((n+1)*sizeof(int));
    Knapsack(p, w, m, n);
    traceback(w, m, n, x);
    s = f[1][m];
    printf("the max value is %f\n", s);/*输出*/
    for (i = 1; i <= n; i++) {
        if (x[i] == 1) {
            printf(" the p:  %f", p[i]);
            printf(" the w:  %d\n", w[i]);
        }
    }
    getchar();
    return 0;
}
