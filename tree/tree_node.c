// @siliconx
// 2017-05-19 10:09:12

#include "tree_node.h"

node *create_node(float value) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->e = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
