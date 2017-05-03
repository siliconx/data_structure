// @siliconx
// 2017-04-28 11:33:01
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 16

typedef struct {
    int **element;  // 非零元素三元组，data[0]不使用
    int rows, cols, nums;  // 矩阵的行数、列数和非零元素个数
} TripleSparseMatrix;


int create(TripleSparseMatrix**, int, int, int);

int main(void) {
    TripleSparseMatrix *M;
    int rows, cols, nums;
    scanf("%d %d %d", &rows, &cols, &nums);
    create(&M, rows, cols, nums);
    return 0;
}


int create(TripleSparseMatrix **M, int rows, int cols, int nums) {
    if (nums > rows * cols) {
        printf("invalid args: rows: %d, cols: %d, nums: %d\n", rows, cols, nums);
        return 1;
    }
    *M = (TripleSparseMatrix *) malloc(sizeof(TripleSparseMatrix));
    (*M)->rows = rows;
    (*M)->cols = cols;
    (*M)->nums = nums;
    (*M)->element = (int **) malloc(sizeof(nums * 3));
    printf("created %d*%d with %d none-zero matrix!\n", rows, cols, nums);
    return 0;
}
