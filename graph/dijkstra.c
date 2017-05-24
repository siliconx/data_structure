// @siliconx
// 2017-05-22 22:46:17
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR -1

typedef struct AdjacencyMatrix {
    int size;
    int **matrix;
} AdjacencyMatrix;

AdjacencyMatrix *input_matrix();
int output_matrix(AdjacencyMatrix*);
int dijkstra(AdjacencyMatrix*, int, int);
int index_of_min_value(AdjacencyMatrix*, int);
int free_adjacy_matrix(AdjacencyMatrix*);

int main(void) {
    AdjacencyMatrix *adjacency_matrix = input_matrix();
    output_matrix(adjacency_matrix);
    int shortest_distance = dijkstra(adjacency_matrix, 0, 4);
    printf("shortest_distance: %d\n", shortest_distance);
    free_adjacy_matrix(adjacency_matrix);
    return 0;
}

AdjacencyMatrix *input_matrix() {
    int size;
    AdjacencyMatrix *adjacency_matrix = (AdjacencyMatrix *) malloc(sizeof(AdjacencyMatrix));
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

int output_matrix(AdjacencyMatrix *adjacency_matrix) {
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

int dijkstra(AdjacencyMatrix *adjacency_matrix, int start, int end) {
    int **matrix = adjacency_matrix->matrix;
    int size = adjacency_matrix->size;
    int i;
    int is_label[size];// 是否标号

    for (i=0;i<size;i++) {
        is_label[i] = 0;
    }
    int indexs[size];// 所有标号的点的下标集合，以标号的先后顺序进行存储，实际上是一个以数组表示的栈
    int i_count = -1;//栈的顶点

    int distance[size];// v0到各点的最短距离的初始值
    // copy the distance of `start` line
    for (i=0;i<size;i++) {
        distance[i] = matrix[start][i];
    }
    int index = start;// 从初始点开始
    int present_shortest = 0;//当前临时最短距离

    indexs[++i_count] = index;// 把已经标号的下标存入下标集中
    is_label[index] = 1;

    while (i_count<size) {
        // 第一步：标号v0,即w[0][0]找到距离v0最近的点

        int min = 9999;
        for (i = 0; i < size; i++) {
            if (!is_label[i] && distance[i] != -1 && i != index) {
                // 如果到这个点有边,并且没有被标号
                if (distance[i] < min) {
                    min = distance[i];
                    index = i;  // 把下标改为当前下标
                }
            }
        }

        if (index == end) {  //已经找到当前点了，就结束程序
            break;
        }

        is_label[index] = 1;  //对点进行标号
        indexs[++i_count] = index;  // 把已经标号的下标存入下标集中
        if (matrix[indexs[i_count - 1]][index] == -1 || present_shortest + matrix[indexs[i_count - 1]][index] > distance[index]) {
            // 如果两个点没有直接相连，或者两个点的路径大于最短路径
            present_shortest = distance[index];
        } else {
            present_shortest += matrix[indexs[i_count - 1]][index];
        }

        // 第二步：将distance中的距离加入vi
        for (i = 0; i < size; i++) {
            // 如果vi到那个点有边，则v0到后面点的距离加
            if (distance[i] == -1 && matrix[index][i] != -1) {// 如果以前不可达，则现在可达了
                distance[i] = present_shortest + matrix[index][i];
            } else if (matrix[index][i] != -1
                    && present_shortest + matrix[index][i] < distance[i]) {
                // 如果以前可达，但现在的路径比以前更短，则更换成更短的路径
                distance[i] = present_shortest + matrix[index][i];
            }

        }
    }

    //如果全部点都遍历完，则distance中存储的是开始点到各个点的最短路径
    return distance[end] - distance[start];
}

// int dijkstra2(AdjacencyMatrix *graph_martrix, int start, int end) {
//     int size = graph_martrix->size;
//     if (start < 0 || start >= size || end < 0 || end >= size) {
//         return ERROR;
//     }

//     int i, min_value_index;
//     int count = -1;
//     int shortest_distance = -1;
//     int index = start;

//     int distance[size];
//     int is_lable[size] = {0};
//     int indexs[size];

//     is_lable[index] = 1;
//     indexs[++count] = index;

//     // copy the distance of `start` line
//     for (i=0;i<size;i++) {
//         distance[i] = (graph_martrix->matrix)[start][i];
//     }

//     while (count<size) {
//         min_value_index = index_of_min_value(graph_martrix, start);

//     }
//     return OK;
// }

int index_of_min_value(AdjacencyMatrix *m, int line) {
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

int free_adjacy_matrix(AdjacencyMatrix *m) {
    int size = m->size;
    for (int i=0;i<size;i++) {
        free((m->matrix)[i]);
    }
    free(m->matrix);
    free(m);
    return OK;
}
