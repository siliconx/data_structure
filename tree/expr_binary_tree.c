// @siliconx
// 2017-05-11 16:39:37
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "int_stack.c"
#include "pointer_stack.c"

#define N 128
#define MIN_NORMAL 0.0001


int to_postfix(char[], char[]);
node *gen_expression_tree(char*);  // generate a expression tree
int in_order_output(node*);
int post_order_output(node*);
int leaves_count(node *root);
int tree_depth(node*);
float compute_value(node*);

int is_digit(char);
int priority(char);


int main(void) {
    char infix_expr[N], postfix_expr[N];
    scanf("%s", infix_expr);
    to_postfix(infix_expr, postfix_expr);

    node *root = gen_expression_tree(postfix_expr);
    float result = compute_value(root);
    int leaves = leaves_count(root);
    int depth = tree_depth(root);

    printf("infix expression: %s\n", infix_expr);
    printf("postfix expression: %s\n", postfix_expr);
    printf("leaves count: %d\n", leaves);
    printf("tree depth: %d\n", depth);
    printf("result %.2f\n", result);
    return 0;
}


node *gen_expression_tree(char *expr) {
    int expr_len = strlen(expr);
    char str_num[N];
    int num_len = 0;
    // 操作数栈
    Stack *value_stack;
    init(&value_stack);
    for (int i=0;i<expr_len;i++) {
        char c = expr[i];
        if ((c <= '9' && c >= '0') || c == '.') {
            // 数字可能大于一位
            str_num[num_len] = c;
            str_num[++num_len] = '\0';

        } else if (c == ' ') {
            if (num_len > 0) {
                // parse number from string to float
                float value = atof(str_num);
                node *value_node = create_node(value);
                push(value_stack, value_node);
                num_len = 0;
                str_num[num_len] = '\0';
            }
            // pass
        } else {
            if (num_len > 0) {
                // parse number from string to float
                float value = atof(str_num);
                node *value_node = create_node(value);
                push(value_stack, value_node);
                num_len = 0;
                str_num[num_len] = '\0';
            }
            node *right_node = pop(value_stack);
            node *left_node = pop(value_stack);
            node *new_node = create_node(c);
            new_node->left = left_node;
            new_node->right = right_node;
            push(value_stack, new_node);
        }
    }

    return pop(value_stack);
}

int in_order_output(node *root) {
    if (root == NULL) {
        // pass
    } else {
        in_order_output(root->left);

        if (root->left == NULL && root->right == NULL) {
            printf("%f ", root->e);
        } else {
            printf("%c ", (char) root->e);
        }

        in_order_output(root->right);
    }
    return 0;
}

int post_order_output(node* root) {
    if (root == NULL) {
        // pass
    } else {
        post_order_output(root->left);
        post_order_output(root->right);

        if (root->left == NULL && root->right == NULL) {
            printf("%.2f ", root->e);
        } else {
            printf("%c ", (char) root->e);
        }
    }
    return 0;
}

int to_postfix(char infix[], char postfix[]) {
    int_stack *oprts;
    stack_init(&oprts);
    int infix_len = strlen(infix);
    int index = 0;
    for (int i=0;i<infix_len;i++) {
        char c = infix[i];
        if (is_digit(c)) {
            postfix[index++] = c;
            while (i + 1 < infix_len && is_digit(infix[i + 1])) {
                postfix[index++] = infix[++i];
            }
           // 用空格分开操作数，因为在后缀表达式中，有可能有多个操作数相邻，这里用空格将它们分开
           postfix[index++] = ' ';
        } else {
            if (stack_is_empty(oprts) || c == '(') {
                // 空栈或左括号，直接入栈
                stack_push(oprts, c);
            } else if (c == ')') {
                // 遇到右括号， 不断弹出操作符，直至遇到左括号
                char oprt = stack_pop(oprts);
                while (oprt != '(') {
                    postfix[index++] = oprt;
                    oprt = stack_pop(oprts);
                }
            } else {
                if (priority(c) > priority(stack_peek(oprts))) {
                    // 当前操作符的优先级大于栈顶操作符的优先级，直接入栈
                    stack_push(oprts, c);
                } else {
                    // 否则将操作符栈中的操作符弹出，直到遇到比当前操作符优先级小的操作符，并把当前操作符入栈
                    while ((! stack_is_empty(oprts)) && (priority(c) <= priority(stack_peek(oprts)))) {
                        postfix[index++] = stack_pop(oprts);
                    }
                    stack_push(oprts, c);
                }
            }
        }
    }
    while (! stack_is_empty(oprts)) {
        // 弹出操作符栈中剩余符号
        postfix[index++] = stack_pop(oprts);
    }
    postfix[index] = '\0';
    return 1;
}

int leaves_count(node *root) {
    int count = 0;
    if (root == NULL) {
        // pass
    } else {
        if (root->left == NULL && root->right == NULL) {
            count++;
        } else {
            count += leaves_count(root->left);
            count += leaves_count(root->right);
        }
    }
    return count;
}

int tree_depth(node* root) {
    int d = 0;
    if (root == NULL) {
        // pass
    } else {
        d++;
        int left_depth = tree_depth(root->left);
        int right_depth = tree_depth(root->right);
        d += left_depth > right_depth ? left_depth : right_depth;
    }
    return d;
}

float compute_value(node *root) {
    float left_value, right_value;
    if (root == NULL) {
        return 0;
    }

    //叶子节点，是一个数字
    if (root->left == NULL && root->right == NULL) {
        return root->e;
    }

    float result = 0;
    left_value = compute_value(root->left);
    right_value = compute_value(root->right);

    switch((char) root->e) {
        case '+': {
            result = left_value + right_value;
            break;
        }
        case '-': {
            result = left_value - right_value;
            break;
        }
        case '*': {
            result = left_value * right_value;
            break;
        }
        case '/': {
            result = left_value / right_value;
            break;
        }
        default: {
            break;
        }
    }
    return result;
}

int priority(char oprt) {
    int priority = 0;
    switch(oprt) {
        case '+': {
            priority = 1;
            break;
        }
        case '-': {
            priority = 1;
            break;
        }
        case '*': {
            priority = 2;
            break;
        }
        case '/': {
            priority = 2;
            break;
        }
        default: {
            break;
        }
    }
    return priority;
}

int is_digit(char c) {
    if ((c >= '0' && c <= '9') || c == '.') {
        return T;
    }
    return F;
}