// @siliconx
// 2017-04-14 11:33:01
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 16

typedef struct {
    int i, j;  // 该非零元素的下标
    int e;  // 元素值
} Triple;

typedef struct {
    Triple data[MAXSIZE + 1];  // 非零元素三元组，data[0]不使用
    int rows, cols, nums;  // 矩阵的行数、列数和非零元素个数
} TSMatrix;

int create(TSMatrix *M);
int transpose(TSMatrix *M);
int input(TSMatrix *M);
int output(TSMatrix *M);

int main(void) {
    TSMatrix *M;
    create(M);
    return 0;
}

int create(TSMatrix *M) {
    M = (TSMatrix *) malloc(sizeof(TSMatrix));
    return 1;
}

int input(TSMatrix *M) {
    printf("Enter the `rows` `colums` and `nums` of the sparse matrix\n");
    scanf("%d %d %d", &(M->rows), &(M->cols), &(M->nums));
    printf("Now, enter each element\n");
    for (int i=0;i<M->nums;i++) {
        Triple temp = (M->data)[i];
        printf("enter `i` `j` `e` of this element\n");
        scanf("%d %d %d", &(temp->i), &(temp->j), &(temp->e));
    }
}

int output(TSMatrix *M) {
    int matrix[M->rows][M->cols];
    for (int i=0;i<M->nums;i++) {
        Triple e = (M->data)[i];
        matrix[e->i][e->j] = e->e;
    }

    for (int i=0;i<M->rows) {
        for (int j=0;j<M->cols;j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

