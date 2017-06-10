// @siliconx
// 2017-06-09 17:36:31
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    int n = atoi(argv[1]);
    srand(time(NULL));
    int prev, num;
    prev = num = 0;
    for (int i=0;i<n;i++) {
        num = (rand() % n) / 9 + num + 1;
        printf("%d ", num);
        prev = num;
    }
    printf("\n");
    return 0;
}