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

typedef struct {
    int *distances;  // 起始点到各点的距离
    int *paths;  // 经过的顶点
} PathDetails;

Graph *graph;
ScenicSpot *scenic_spots;
int visited[COUNT];

int menu(void);
int initialize(void);  // 初始化

PathDetails *dijkstra(int, int);
int dfs(int);

int input_matrix(void);  // 输入图的邻接矩阵
int show_matrix(void);  // 展示矩阵

int input_spots(void);  // 输入景点
int show_spots(void);  // 展示景点
int reset(void);

int main(void) {
    int from, to, choice;
    initialize();
    input_matrix();
    input_spots();

    while(1) {
        reset();
        menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1: {
                show_spots();
                break;
            }
            case 2: {
                show_matrix();
                break;
            }
            case 3: {
                printf("from? ");
                scanf("%d", &from);
                printf("to? ");
                scanf("%d", &to);

                PathDetails *path_details = dijkstra(from, to);
                printf("paths: %d#%s", from, scenic_spots[from].name);
                for (int i=1;i<COUNT;i++) {
                    int v = (path_details->paths)[i];
                    if (v == -1) {
                        break;
                    }
                    printf(" --%d--> %d#%s", (graph->matrix)[(path_details->paths)[i-1]][v], v, scenic_spots[v].name);
                }
                printf("(distance: %d)\n", (path_details->distances)[to]);
                printf("\n");
                break;
            }
            case 4: {
                printf("from? ");
                scanf("%d", &from);
                dfs(from);
                printf("END\n");
                break;
            }
            default: {
                return OK;
            }
        }
    }
    return OK;
}

int menu(void) {
    printf("======================================\n");
    printf("|      1: 展示景点                   |\n");
    printf("|      2: 展示邻接矩阵               |\n");
    printf("|      3: 查找两个景点之间的最短距离 |\n");
    printf("|      4: 游览整个公园               |\n");
    printf("|      其他: 退出                    |\n");
    printf("======================================\n");
    printf("选: ");
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

int reset(void) {
    // 归零已访问节点
    for (int i=0; i<COUNT; i++) {
        visited[i] = 0;
    }
    return OK;
}

PathDetails *dijkstra(int start, int end) {
    int i, shortest_dist, shortest_dist_index, current_index, distance;
    // 从起点到终点路径的数量
    int path_count = 0;
    // 路径数组，按下标顺序表示从起点到终点的路径
    int *paths = (int *) malloc(sizeof(int) * COUNT);
    // 存储起点到各个顶点的最短路径
    int *distances = (int *) malloc(sizeof(int) * COUNT);
    short is_label[COUNT];
    for (i=0; i<COUNT; i++) {
        // 复制距离值
        distances[i] = (graph->matrix)[start][i];
        // 初始化数组
        is_label[i] = 0;
        // 初始化路径
        paths[i] = -1;
    }

    paths[path_count++] = start;
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
        if (shortest_dist_index == -1 || current_index == end) {
            break;
        }

        paths[path_count++] = shortest_dist_index;
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
                    && distances[i] > distance + shortest_dist) {
                    // 原来有通路，但是原来的距离大于新路径之和
                    distances[i] = distance + shortest_dist;
                }
            }
        }
    }
    PathDetails *details = (PathDetails *) malloc(sizeof(PathDetails));
    details->distances = distances;
    details->paths = paths;
    return details;
}


int dfs(int start) {
    int **matrix = graph->matrix;
    printf("%d#%s --> ", start, scenic_spots[start].name);
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
    printf("黄石公园景点介绍： \n");
    for (int i=0; i<COUNT; i++) {
        printf("---------------------------------------\n");
        printf("code: %d\nname: %s\nintro: %s\n", i, scenic_spots[i].name, scenic_spots[i].intro);
    }
    printf("---------------------------------------\n");
}
