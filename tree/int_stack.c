// @siliconx
// 2017-04-07 09:52:39
#include "int_stack.h"

int stack_init(int_stack **st) {
    *st = (int_stack *) malloc(sizeof(int_stack));
    (*st)->base = (int *) malloc(sizeof(int) * INIT_SIZE);
    (*st)->top = 0;
    (*st)->capacity = INIT_SIZE;
}

int stack_is_empty(int_stack *st) {
    return st->top <= 0;
}

int stack_is_full(int_stack *st) {
    return st->top >= st->capacity - 1;
}

int stack_push(int_stack *st, int e) {
    if (st->top >= st->capacity - 1) {
        // stack full
        stack_enlarge_stack(st);
    }
    (st->base)[(st->top)++] = e;
    return 1;
}

int stack_pop(int_stack *st) {
    if (stack_is_empty(st)) {
        return ERROR;
    }
    return (st->base)[--(st->top)];
}

int stack_peek(int_stack *st) {
    if (stack_is_empty(st)) {
        return ERROR;
    }
    return (st->base)[st->top - 1];
}

int stack_enlarge_stack(int_stack *st) {
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

