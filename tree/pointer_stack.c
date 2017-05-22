// @siliconx
// 2017-04-07 09:52:39
#include "pointer_stack.h"

int init(Stack **st) {
    *st = (Stack *) malloc(sizeof(Stack));
    (*st)->base = (node **) malloc(sizeof(node*) * INIT_SIZE);
    (*st)->top = 0;
    (*st)->capacity = INIT_SIZE;
}

int is_empty(Stack *st) {
    return st->top <= 0;
}

int is_full(Stack *st) {
    return st->top >= st->capacity - 1;
}

int push(Stack *st, node *e) {
    if (st->top >= st->capacity - 1) {
        // stack full
        enlarge_stack(st);
    }
    (st->base)[(st->top)++] = e;
    return 1;
}

node *pop(Stack *st) {
    if (is_empty(st)) {
        return NULL;
    }
    return (st->base)[--(st->top)];
}

node *peek(Stack *st) {
    if (is_empty(st)) {
        return NULL;
    }
    return (st->base)[st->top - 1];
}

int enlarge_stack(Stack *st) {
    int new_capacity = (st->capacity) * 2;
    node **new_bucket = (node **) malloc(sizeof(node*) * new_capacity);
    for (int i=0;i<(st->top);i++) {
        new_bucket[i] = (st->base)[i];  // 将原来的数据复制到新的栈
    }
    st->capacity = new_capacity;
    free(st->base);
    st->base = new_bucket;
    return 1;
}

int reverse(Stack *st) {
    int size = st->top;
    for (int i=0;i<size/2;i++) {
        node *temp = (st->base)[i];
        (st->base)[i] = (st->base)[size-i-1];
        (st->base)[size-i-1] = temp;
    }
    return 0;
}

