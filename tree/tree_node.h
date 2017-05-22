// @siliconx
// 2017-05-19 10:09:12

typedef struct node {
    float e;
    struct node *left, *right;
} node;

node *create_node(float value);
