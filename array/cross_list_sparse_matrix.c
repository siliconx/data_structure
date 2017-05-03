// @siliconx
// 2017-04-14 10:26:12
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int i, j, val;  // 非零元素的行列下标和元素值
    struct OLNode *right, *down;  // 该非零元素所在行表和列表的后继链域
} OLNode, *OLink;

typedef struct {
    OLink *rhead, *chead;  // 行和列链表头指针向量基址由CreateSMatrix分配
    int rows, cols, nums;  // 稀疏矩阵的行数、列数和非零元素个数
} CrossList;

int CreateSMatrix(CrossList *M);

int main(void) {
    CrossList *M = (CrossList *) malloc(sizeof(CrossList));
    CreateSMatrix(M);
}

int CreateSMatrix(CrossList *M) {
    if (M) {
        free(M);
    }
    printf("Enter the `rows`, `cols` and `nums` of the sparse matrix\n");
    scanf("%d %d %d", &(M->rows), &(M->cols), &(M->nums));
    return 1;
}
