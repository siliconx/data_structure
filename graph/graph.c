// @siliconx
// 2017-05-22 22:46:17
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define OK 0
#define ERROR -1

typedef struct Graph {
    int size;
    int **matrix;
} Graph;

int dijkstra(Graph*, int, int);
int *dijkstra2(Graph*, int, int);
int dfs(Graph*, int*, int);

Graph *input_matrix();
int output_matrix(Graph*);
int index_of_min_value(Graph*, int);
int free_adjacy_matrix(Graph*);

int main(void) {
    Graph *adjacency_matrix = input_matrix();
    output_matrix(adjacency_matrix);
    int shortest_distance = dijkstra(adjacency_matrix, 0, 4);
    printf("shortest_distance: %d\n", shortest_distance);

    int *dists = dijkstra2(adjacency_matrix, 6, 0);
    printf("shortest distance:\n");
    for (int i=0;i<adjacency_matrix->size;i++) {
        printf("%d ", dists[i]);
    }

    printf("\nDFS:\n");
    int visited[adjacency_matrix->size];
    for (int i=0;i<adjacency_matrix->size;i++) {
        visited[i] = 0;
    }
    dfs(adjacency_matrix, visited, 0);
    printf("\n");

    free_adjacy_matrix(adjacency_matrix);
    return 0;
}

int dijkstra(Graph *adjacency_matrix, int start, int end) {
    int **matrix = adjacency_matrix->matrix;
    int size = adjacency_matrix->size;
    int i;
    int is_label[size];// 是否标号

    for (i=0;i<size;i++) {
        is_label[i] = 0;
    }
    // 所有标号的点的下标集合，以标号的先后顺序进行存储，实际上是一个以数组表示的栈
    int indexs[size];
    int i_count = -1;  //栈的顶点

    int present_distance;
    int distances[size];  // v0到各点的最短距离的初始值
    // copy the distances of `start` line
    for (i=0;i<size;i++) {
        distances[i] = matrix[start][i];
    }
    int index = start;// 从初始点开始
    int present_shortest = 0;//当前临时最短距离

    indexs[++i_count] = index;// 把已经标号的下标存入下标集中
    is_label[index] = 1;

    while (i_count<size) {
        // 第一步：标号v0,即w[0][0]找到距离v0最近的
        int min = 9999;
        for (i = 0; i < size; i++) {
            if (!is_label[i] && distances[i] != -1 && i != index) {
                // 如果到这个点有边,并且没有被标号
                if (distances[i] < min) {
                    min = distances[i];
                    index = i;  // 把下标改为当前下标
                }
            }
        }

        if (index == end) {  //已经找到当前点了，就结束程序
            break;
        }

        is_label[index] = 1;  //对点进行标号
        indexs[++i_count] = index;  // 把已经标号的下标存入下标集中
        present_distance = matrix[indexs[i_count - 1]][index];
        if (present_distance == -1 || present_shortest + present_distance > distances[index]) {
            // 如果两个点没有直接相连，或者两个点的路径大于最短路径
            present_shortest = distances[index];
        } else {
            present_shortest += present_distance;
        }

        // 第二步：将vi中的距离加入distances
        for (i = 0; i < size; i++) {
            // 如果vi到那个点有边，则v0到后面点的距离加
            if (distances[i] == -1 && matrix[index][i] != -1) {  // 如果以前不可达，则现在可达了
                distances[i] = present_shortest + matrix[index][i];
            } else if (matrix[index][i] != -1
                    && present_shortest + matrix[index][i] < distances[i]) {
                // 如果以前可达，但现在的路径比以前更短，则更换成更短的路径
                distances[i] = present_shortest + matrix[index][i];
            }
        }
    }

    printf("distances: ");
    for (i=0; i<size;i++) {
        printf("%d ", distances[i]);
    }
    printf("\n");
    //如果全部点都遍历完，则distances中存储的是开始点到各个点的最短路径
    return distances[end] - distances[start];
}

int *dijkstra2(Graph *graph,int n,int u){
    int **matrix = graph->matrix;
    int i;
    int *dist = (int *) malloc(sizeof(int) * n);
    short s[n];
    for (i=0;i<n;i++) {
        dist[i] = matrix[u][i];
        s[i] = 0;
    }
    int min,v;
    s[u]=1;
    while(1){
        min=INT_MAX;v=-1;
        //找到最小的dist
        for(int i=0;i<n;i++){
            if(!s[i]){
                if(dist[i]<min){min=dist[i];v=i;}
            }
        }
        if(v==-1)break;//找不到更短的路径了
        //更新最短路径
        s[v]=1;
        for(int i=0;i<n;i++){
            if(!s[i]&&
                    matrix[v][i]!=INT_MAX&&
                    dist[v]+matrix[v][i]<dist[i]){
                dist[i]=dist[v]+matrix[v][i];
            }
        }
    }
    return dist;
}

int dfs(Graph *matrix, int *visited, int start) {
    printf("%d->", start);
    visited[start] = 1;

    for (int i=0; i<matrix->size; i++) {
        if (visited[i] == 0 && (matrix->matrix)[start][i] > 0) {
            dfs(matrix, visited, i);
        }
    }
    return OK;
}

Graph *input_matrix() {
    int size;
    Graph *adjacency_matrix = (Graph *) malloc(sizeof(Graph));
    scanf("%d", &size);

    // allocate 2d array
    adjacency_matrix->size = size;
    adjacency_matrix->matrix = (int **) malloc(sizeof(int*) * size);
    for (int i=0;i<size;i++) {
        (adjacency_matrix->matrix)[i] = (int *) malloc(sizeof(int) * size);
    }

    // input data
    for (int i=0;i<size;i++) {
        for (int j=0;j<size;j++) {
            scanf("%d", &((adjacency_matrix->matrix)[i][j]));
        }
    }
    return adjacency_matrix;
}

int output_matrix(Graph *adjacency_matrix) {
    int size = adjacency_matrix->size;
    printf("size: %d\n", size);
    for (int i=0;i<size;i++) {
        for (int j=0;j<size;j++) {
            printf("%d ", (adjacency_matrix->matrix)[i][j]);
        }
        printf("\n");
    }
    return OK;
}

int index_of_min_value(Graph *m, int line) {
    // each line of matrix
    int *array = (m->matrix)[line];
    int size = m->size;
    int min, i, index;
    min = index = -1;

    // find the first positive num
    for (i=0;i<size;i++) {
        if (array[i] > 0) {
            min = array[i];
            index = i;
            break;
        }
    }

    if (index < 0) {
        return ERROR;
    }

    // find the min positive num
    for (i=0;i<size;i++) {
        if (array[i] > 0 && array[i] < min) {
            min = array[i];
            index = i;
        }
    }
    return index;
}

int free_adjacy_matrix(Graph *m) {
    int size = m->size;
    for (int i=0;i<size;i++) {
        free((m->matrix)[i]);
    }
    free(m->matrix);
    free(m);
    return OK;
}
