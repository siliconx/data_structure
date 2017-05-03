// @siliconx
// 2017-04-06 21:17:22
#include <string.h>
#include <math.h>
#include "array_list_stack.h"
#define N 999  // 字符数组的长度
#define T 1  // True
#define F 0  // False

int to_postfix(char[], char[]);  // 将中缀表达式转换为后缀表达式
int evaluate();  // 计算后缀表达式
int priority(char);  // 获取运算符的优先级
int computing(int, int, char);  // 根据操作符和操作数计算值
int is_digit(char);  // 判断字符是否为数字字符
int parse_int(char[]);  // 将数字字符串转换成整数 

Stack *vals, *oprts;

int main(void) {
    init(&vals);
    init(&oprts);
    char infix[N];
    char postfix[N];
    printf("Enter a expression:\n");
    scanf("%s", infix);
    to_postfix(infix, postfix);
    printf("postfix: %s\n", postfix);
    int result = evaluate(postfix);
    printf("result: %d\n", result);
    return 0;
}

int to_postfix(char infix[], char postfix[]) {
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
            if (is_empty(oprts) || c == '(') {
                // 空栈或左括号，直接入栈
                push(oprts, c);
            } else if (c == ')') {
                // 遇到右括号， 不断弹出操作符，直至遇到左括号
                char oprt = pop(oprts);
                while (oprt != '(') {
                    postfix[index++] = oprt;
                    oprt = pop(oprts);
                }
            } else {
                if (priority(c) > priority(peek(oprts))) {
                    // 当前操作符的优先级大于栈顶操作符的优先级，直接入栈
                    push(oprts, c);
                } else {
                    // 否则将操作符栈中的操作符弹出，直到遇到比当前操作符优先级小的操作符，并把当前操作符入栈
                    while ((! is_empty(oprts)) && (priority(c) <= priority(peek(oprts)))) {
                        postfix[index++] = pop(oprts);
                    }
                    push(oprts, c);
                }
            }
        }
    }
    while (! is_empty(oprts)) {
        // 弹出操作符栈中剩余符号
        postfix[index++] = pop(oprts);
    }
    postfix[index] = '\0';
    return 1;
}

int evaluate(char postfix[]) {
    // 对后缀表达式求值
    int len = strlen(postfix);
    char num[16];
    int num_len = 0;
    for (int i=0;i<len;i++) {
        char c = postfix[i];
        if (is_digit(c)) {
            num_len = 0;
            num[num_len++] = c;
            // 数字可能有多位，向后读取直至末尾或遇到非数字
            while (i + 1 < len && is_digit(postfix[i + 1])) {
                num[num_len++] = postfix[++i];
            }
            num[num_len] = '\0';
            int temp = parse_int(num);
            push(vals, temp);
        } else if (c == ' ') {
            // 忽略空格
        } else {
            int b = pop(vals);
            int a = pop(vals);
            int result = computing(a, b, c);
            push(vals, result);
        }
    }
    return pop(vals);
}

int is_digit(char c) {
    if (c >= '0' && c <= '9') {
        return T;
    }
    return F;
}

int priority(char oprt) {
    int proity = 0;
    if (oprt == '+' || oprt == '-') {
        proity = 1;
    } else if (oprt == '*' || oprt == '/') {
        proity = 2;
    }
    return proity;
}

int computing(int a, int b, char oprt) {
    int result = 0;
    switch(oprt) {
        case '+': {
            result = a + b;
            break;
        }
        case '-': {
            result = a - b;
            break;
        }
        case '*': {
            result = a * b;
            break;
        }
        case '/': {
            result = a / b;
            break;
        }
    }
    return result;
}

int parse_int(char int_str[]) {
    int len = strlen(int_str);
    int result = 0;
    int bit;  // 每一位数字
    for (int i=len - 1;i>=0;i--) {
        bit = int_str[i] - 48;  // 数字字符与该数值的差值为48
        result += (int) (bit * pow(10, len - i - 1));
    }
    return result;
}

