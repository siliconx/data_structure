// @siliconx
// 2017-04-07 09:52:39
#include <stdio.h>
#include <stdlib.h>
#define INIT_SIZE 16  // 存储空间初始分配量
#define T 1
#define F 0
#define ERROR -1

typedef struct int_stack {
    int *base;  // 在栈构造之前和销毁之后，base的值为NULL
    int top;  // 栈顶
    int capacity;  // 栈容量
} int_stack;

int stack_init(int_stack**);  // 初始化栈
int stack_is_empty(int_stack*);  // 判断栈是否为空
int stack_is_full(int_stack*);  // 判断是否栈满
int stack_push(int_stack*, int);  // 压栈
int stack_pop(int_stack*);  // 出栈
int stack_peek(int_stack*); // 获得栈顶元素
int stack_enlarge_stack(int_stack*);  // 扩大栈空间
