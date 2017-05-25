// @siliconx
// 2017-04-26 22:22:28

#include <stdio.h>
#define N 6

void DFS(int);
int output(void);
int G[N][N], visited[N], n;  //n is number of vertices and graph is sorted in array G[N][N]

void main() {
    int i, j;
    // printf("Enter number of vertices:");

    scanf("%d", &n);

    //read the adjecency matrix
    // printf("\nEnter adjecency matrix of the graph:\n");

    for(i=0;i<n;i++) {
       for(j=0;j<n;j++) {
            scanf("%d", &G[i][j]);
       }
    }

    //visited is initialized to zero
    for(i=0;i<n;i++) {
        visited[i]=0;
   }

    output();
    DFS(0);
    printf("\n");
}

void DFS(int i) {

    printf("%d->", i);
    visited[i] = 1;

    for(int j=0;j<n;j++) {
       if(visited[j] == 0 && G[i][j] > 0) {
            DFS(j);
       }
    }
}

int output(void) {
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}