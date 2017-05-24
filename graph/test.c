// @siliconx
// 2017-05-23 12:22:58
#include <stdio.h>
#include <stdlib.h>
#define N 1

int main(void) {
    int **p = (int **) malloc(sizeof(int) * N);
    scanf("%d", *p);
    printf("%d\n", **p);
    return 0;
}
