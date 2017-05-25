// @siliconx
// 2017-05-24 20:41:12
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define COUNT 6
#define N 64
#define OK 0
#define ERROR -1

typedef struct {  // 图
    int **matrix;
} Graph;

typedef struct {  // 景点
    int code;
    char name[N];
    char intro[N * 2];
} ScenicSpot;

Graph *graph;
ScenicSpot *scenic_spots;
int visited[COUNT];

int initialize(void);  // 初始化

int *dijkstra(int);
int dfs(int);

int input_matrix(void);  // 输入图的邻接矩阵
int show_matrix(void);  // 展示矩阵

int input_spots(void);  // 输入景点
int show_spots(void);  // 展示景点

int main(void) {
    initialize();

    input_matrix();
    show_matrix();

    input_spots();
    show_spots();

    int *array = dijkstra(1);
    for (int i=0; i<COUNT; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    dfs(0);
    printf("\n");
    return OK;
}

int initialize(void) {
    int i;
    // 景点数组
    scenic_spots = (ScenicSpot *) malloc(sizeof(ScenicSpot) * COUNT);

    // 图邻接矩阵
    graph = (Graph *) malloc(sizeof(Graph) * COUNT);
    graph->matrix = (int **) malloc(sizeof(int*) * COUNT);
    for (i=0; i<COUNT; i++) {
        (graph->matrix)[i] = (int *) malloc(sizeof(int) * COUNT);
    }

    // 归零已访问节点
    for (i=0; i<COUNT; i++) {
        visited[i] = 0;
    }
    return OK;
}

int *dijkstra(int start) {
    int i, shortest_dist, shortest_dist_index, current_index, distance;
    int *distances = (int *) malloc(sizeof(int) * COUNT);
    short is_label[COUNT];
    for (i=0; i<COUNT; i++) {
        // 复制距离值
        distances[i] = (graph->matrix)[start][i];
        // 初始化数组
        is_label[i] = 0;
    }

    current_index = start;
    is_label[current_index] = 1;

    while(1) {
        // 找到当前点的到下一个点路径最短的点
        shortest_dist = INT_MAX;
        shortest_dist_index = -1;
        for (i=0; i<COUNT; i++) {
            if (is_label[i] == 0 && distances[i] > 0) {
                if (distances[i] < shortest_dist) {
                    shortest_dist = distances[i];
                    shortest_dist_index = i;
                }
            }
        }

        // 未找到距离最近的点，循环结束
        if (shortest_dist_index == -1) {
            break;
        }
        printf("shortest_dist_index: %d\n", shortest_dist_index);
        printf("shortest dist: %d\n", shortest_dist);

        current_index = shortest_dist_index;
        is_label[current_index] = 1;

        // 更新distances
        for (i=0; i<COUNT; i++) {
            distance = (graph->matrix)[shortest_dist_index][i];

            // 找到未标记且点`shortest_dist_index`到点`i`距离大于0的点
            if (is_label[i] == 0 && distance > 0) {
                if (distances[i] == -1) {  // 原来无通路
                    distances[i] = distance + shortest_dist;
                } else if (distances[i] > 0
                    && distances[i] > distance + shortest_dist) {  // 原来有通路，但是原来的距离大于新路径之和
                    distances[i] = distance + shortest_dist;
                }
            }
        }
    }
    return distances;
}

int dfs(int start) {
    int **matrix = graph->matrix;
    printf("%d.%s->", start, scenic_spots[start].name);
    visited[start] = 1;
    for (int i=0; i<COUNT; i++) {
        if (visited[i] == 0 && matrix[start][i] > 0) {
            dfs(i);
        }
    }
    return OK;
}

int input_matrix(void) {
    FILE *matrix = fopen("matrix.txt", "r");
    if (matrix == NULL) {
        printf("open matrix.txt failed\n");
        return ERROR;
    }
    for (int i=0;i<COUNT;i++) {
        for (int j=0; j<COUNT; j++) {
            fscanf(matrix, "%d", &((graph->matrix)[i][j]));
        }
    }
    fclose(matrix);
    return OK;
}

int show_matrix(void) {
    for (int i=0;i<COUNT;i++) {
        for (int j=0;j<COUNT;j++) {
            printf("%d ", (graph->matrix)[i][j]);
        }
        printf("\n");
    }
    return OK;
}

int input_spots(void) {
    FILE *spots = fopen("scenic_spots.txt", "r");
    if (spots == NULL) {
        printf("open spots file failed\n");
        return ERROR;
    }
    for (int i=0;i<COUNT;i++) {
        scenic_spots[i].code = i;
        fscanf(spots, "%s %s", scenic_spots[i].name, scenic_spots[i].intro);
    }
    fclose(spots);
    return OK;
}

int show_spots(void) {
    for (int i=0; i<COUNT; i++) {
        printf("=============\n");
        printf("code: %d\nname: %s\nintro: %s\n", i, scenic_spots[i].name, scenic_spots[i].intro);
    }
    printf("=============\n");
}
