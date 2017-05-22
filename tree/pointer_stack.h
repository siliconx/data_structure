// @siliconx
// 2017-04-07 09:52:39
#include <stdio.h>
#include <stdlib.h>
#include "tree_node.c"

#define INIT_SIZE 16  // 存储空间初始分配量
#define T 1
#define F 0
#define ERROR -1

typedef struct Stack {
    struct node **base;  // 在栈构造之前和销毁之后，base的值为NULL
    int top;  // 栈顶
    int capacity;  // 栈容量
} Stack;

int init(Stack**);  // 初始化栈
int is_empty(Stack*);  // 判断栈是否为空
int is_full(Stack*);  // 判断是否栈满
int push(Stack*, node*);  // 压栈
node *pop(Stack*);  // 出栈
node *peek(Stack*); // 获得栈顶元素
int enlarge_stack(Stack*);  // 扩大栈空间
int reverse(Stack*);  // 逆置栈
