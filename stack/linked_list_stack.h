// @siliconx
// 2017-04-06 16:35:44
#include <stdio.h>
#include <stdlib.h>


typedef struct node {  // 栈元素
    int element;
    struct node *prev;
    struct node *next;
} node;

typedef struct stack {  // 栈
    int size;
    struct node *bottom, *top;
} stack;


int init();  // 初始化栈
int is_empty();  // 判断栈是否为空
int push();  // 压栈
node* pop();  // 出栈
node* peek();  // 获取栈顶元素

// int main(void) {
//     stack *vals = (stack *) malloc(sizeof(stack));
//     stack *oprts = (stack *) malloc(sizeof(stack));
//     init(vals);
//     init(oprts);

//     char expresion[N];
//     scanf("%s", expresion);
//     printf("%s\n", expresion);

//     return 0;
// }

int init(stack *st) {
    st->size = 0;  // 栈初始大小为0
    // 栈底节点，不存放元素
    node *first = (node *) malloc(sizeof(node));
    st->top = st->bottom = first;
    first->element = 0;  // 该节点的值初始化为0
    st->top->next = st->top->prev = NULL;  // 该节点的next及prev均为NULL
    return 1;
}

int is_empty(stack *st) {
    if (st->size < 1) {
        return 1;
    } else {
        return 0;
    }
}

int push(stack *st, int e) {
    // 申请一块内存空间
    node *new_top = (node *) malloc(sizeof(node));
    new_top->element = e;
    new_top->next = NULL;
    
    new_top->prev = st->top;
    st->top->next = new_top;
    st->top = new_top;
    (st->size)++;
    return 1;
}

node* pop(stack *st) {
    if (is_empty(st)) {
        return NULL;
    }
    st->top->prev->next = NULL;
    node *temp = st->top;
    st->top = st->top->prev;
    (st->size)--g;
    return temp;
}

node* peek(stack *st) {
    if (is_empty(st)) {
        return NULL;
    }
    return (st->top);
}
