// @siliconx
// 2017-04-07 09:52:39
#include <stdio.h>
#include <stdlib.h>
#define INIT_SIZE 16  // 存储空间初始分配量
#define T 1
#define F 0
#define ERROR -1

typedef struct Stack {
    int *base;  // 在栈构造之前和销毁之后，base的值为NULL
    int top;  // 栈顶
    int capacity;  // 栈容量
} Stack;

int init(Stack**);  // 初始化栈
int is_empty(Stack*);  // 判断栈是否为空
int is_full(Stack*);  // 判断是否栈满
int push(Stack*, int);  // 压栈
int pop(Stack*);  // 出栈
int peek(Stack*); // 获得栈顶元素
int enlarge_stack(Stack*);  // 扩大栈空间


int init(Stack **st) {
    *st = (Stack *) malloc(sizeof(Stack));
    (*st)->base = (int *) malloc(sizeof(int) * INIT_SIZE);
    (*st)->top = 0;
    (*st)->capacity = INIT_SIZE;
}

int is_empty(Stack *st) {
    return st->top <= 0;
}

int is_full(Stack *st) {
    return st->top >= st->capacity - 1;
}

int push(Stack *st, int e) {
    if (st->top >= st->capacity - 1) {
        // stack full
        enlarge_stack(st);
    }
    (st->base)[(st->top)++] = e;
    return 1;
}

int pop(Stack *st) {
    if (is_empty(st)) {
        return ERROR;
    }
    return (st->base)[--(st->top)];
}

int peek(Stack *st) {
    if (is_empty(st)) {
        return ERROR;
    }
    return (st->base)[st->top - 1];
}

int enlarge_stack(Stack *st) {
    int new_capacity = (st->capacity) * 2;
    int *new_bucket = (int *) malloc(sizeof(int) * new_capacity);
    for (int i=0;i<(st->top);i++) {
        new_bucket[i] = (st->base)[i];  // 将原来的数据复制到新的栈
    }
    st->capacity = new_capacity;
    free(st->base);
    st->base = new_bucket;
    return 1;
}

