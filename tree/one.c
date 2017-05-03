// @siliconx
// 2017-04-28 23:02:55
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int e;
    struct node *left, *right;
} node;

int create_linked_bt(node **root);
int linked_bt_leaves_count(node *root);
int linked_bt_depth(node *root);

int main(void) {
    node *root;
    create_linked_bt(&root);
    root->e = 1;
    root->left = (node *) malloc(sizeof(node));
    root->right = (node *) malloc(sizeof(node));
    root->left->e = 3;
    root->right->e = 4;
    root->left->left = root->left->right = root->right->left = root->right->right = NULL;
    printf("count: %d\ndepth: %d\n", linked_bt_leaves_count(root), linked_bt_depth(root));
    return 0;
}


int create_linked_bt(node **root) {
    (*root) = (node *) malloc(sizeof(node));
    return 0;
}


int linked_bt_leaves_count(node *root) {
    int n = 0;
    if (root == NULL) {
        // pass
    } else if (root->left == NULL && root->right) {
        n++;
    } else {
        n++;
        n += linked_bt_leaves_count(root->left);
        n += linked_bt_leaves_count(root->left);
    }
    return n;
}

int linked_bt_depth(node *root) {
    int d = 0;
    if (root == NULL) {
        // pass
    } else if (root->left == NULL && root->right) {
        d++;
    } else {
        d++;
        int left = linked_bt_depth(root->left);
        int right = linked_bt_depth(root->right);
        d += left > right ? left : right;
    }
    return d;
}

