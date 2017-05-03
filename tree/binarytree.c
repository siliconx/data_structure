// @siliconx
// 2017-04-09 11:22:22
#include <stdio.h>
#include <stdlib.h>

typedef struct binarytree{
    int val;
    struct binarytree *left;
    struct binarytree *right;
} binarytree;

int pre_order_traverse(binarytree*);  // pre order traverse binary tree
int in_order_traverse(binarytree*);  // in order traverse binary tree
int post_order_traverse(binarytree*);  // post order traverse binary tree
int init_tree(binarytree**);  // initialize a binarytree
binarytree* insert_as_sorted_binarytree(binarytree**, int);

binarytree *root;

int main(void) {
    // init_tree(&root);
    root = insert_as_sorted_binarytree(&root, 4);
    root = insert_as_sorted_binarytree(&root, 3);
    root = insert_as_sorted_binarytree(&root, 5);
    root = insert_as_sorted_binarytree(&root, 8);
    root = insert_as_sorted_binarytree(&root, 6);
    root = insert_as_sorted_binarytree(&root, 1);
    /*
                 4
                / \
               3   5
              /     \
             1       8
                    /
                   6
    */
    printf("pre order:\n");
    pre_order_traverse(root);

    printf("in order:\n");
    in_order_traverse(root);

    printf("post order:\n");
    post_order_traverse(root);
}

int pre_order_traverse(binarytree *root) {
    if (root == NULL) {
        return 1;
    }
    printf("%d\n", root->val);
    pre_order_traverse(root->left);
    pre_order_traverse(root->right);
    return 0;
}

int in_order_traverse(binarytree *root) {
    if (root == NULL) {
        return 1;
    }
    in_order_traverse(root->left);
    printf("%d\n", root->val);
    in_order_traverse(root->right);
    return 0;
}

int post_order_traverse(binarytree *root) {
    if (root == NULL) {
        return 1;
    }
    post_order_traverse(root->left);
    post_order_traverse(root->right);
    printf("%d\n", root->val);
    return 0;
}

int init_tree(binarytree **root) {
    (*root) = (binarytree *) malloc(sizeof(binarytree));
    (*root)->val = 1;
    (*root)->left = (binarytree *) malloc(sizeof(binarytree));
    (*root)->left->val = 2;
    (*root)->right = (binarytree *) malloc(sizeof(binarytree));
    (*root)->right->val = 3;
    (*root)->left->left = (binarytree *) malloc(sizeof(binarytree));
    (*root)->left->left->val = 4;
    (*root)->left->left->left = NULL;
    (*root)->left->left->right = NULL;
    /*
            1
           / \
          2   3
         /
        4
    */
}

binarytree* insert_as_sorted_binarytree(binarytree **root, int val) {
    if (*root == NULL) {
        (*root) = (binarytree *) malloc(sizeof(binarytree));
        (*root)->val = val;
        (*root)->left = (*root)->right = NULL;
    }

    if ((*root)->val == val) {
        // pass
    } else if ((*root)->val > val) {
        insert_as_sorted_binarytree(&((*root)->left), val);
    } else {
        insert_as_sorted_binarytree(&((*root)->right), val);
    }
    return *root;
}
