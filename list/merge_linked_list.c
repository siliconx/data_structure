// @siliconx
// 2017-06-09 16:40:06
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 19

typedef struct linked_list {
    int val;
    struct linked_list *next;
} linked_list;

linked_list *create(int);
linked_list *merge(linked_list*, linked_list*);
int output(linked_list*);

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    int size_a = atoi(argv[1]);
    int size_b = atoi(argv[2]);
    printf("a: %d, b: %d\n", size_a, size_b);
    linked_list *a = create(size_a);
    linked_list *b = create(size_b);
    printf("a: ");
    output(a);
    printf("b: ");
    output(b);

    linked_list *c = merge(a, b);
    printf("c: ");
    output(c);
    return 0;
}

linked_list *create(int size) {
    linked_list *head = (linked_list *) malloc(sizeof(linked_list));
    head->val = size;
    head->next = NULL;
    linked_list *p = head, *temp;
    int num = rand() % N;
    for (int i=0;i<size;i++) {
        temp = (linked_list *) malloc(sizeof(linked_list));

        num += 1 + (rand() % N);
        temp->val = num;

        temp->next = NULL;
        p->next = temp;
        p = p->next;
    }
    p->next = NULL;
    return head;
}

linked_list *merge(linked_list *a, linked_list *b) {
    if (a == NULL || b == NULL) {
        return a == NULL ? b : a;
    }
    if (a->next == NULL || b->next == NULL) {
        return a->next == NULL ? b : a;
    }
    // 表头
    linked_list *c = (linked_list *) malloc(sizeof(linked_list));
    c->val = 0;
    c->next = NULL;
    linked_list *p, *q, *r;
    p = a->next, q = b->next, r = c;
    while (p && q) {
        if (p->val < q->val) {  // 小于
            r->next = p;
            p = p->next;
            r = r->next;
        } else if (p->val > q->val) {  // 大于
            r->next = q;
            q = q->next;
            r = r->next;
        } else {
            r->next = p;
            p = p->next;
            q = q->next;
            r = r->next;
        }
    }
    // 把余下的直接拼接到表尾
    r->next = p == NULL ? q : p;
    return c;
}

int output(linked_list *l) {
    if (! l) {
        return 0;
    }
    l = l->next;
    while (l) {
        printf("%d ", l->val);
        l = l->next;
    }
    printf("\n");
    return 0;
}
