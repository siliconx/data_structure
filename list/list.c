#include <stdio.h>
#include <stdlib.h>

typedef struct node {  // 链表节点
    int element;
    struct node *next;
} linked_list;

linked_list *head;
int n;  // 元素数量

int *array;  // 顺序表


int menu();
int linked_list_input();  // 链表输入
int linked_list_insert();  // 链表插入
int linked_list_delete();  // 链表删除
int linked_list_output();  // 链表输出
int linked_list_reverse();  // 链表逆置

int array_list_input();  // 顺序表输入
int array_list_insert();  // 顺序表插入
int array_list_delete();  // 顺序表删除
int array_list_output();  // 顺序表输出
int array_list_reverse(void);  // 顺序表逆置

int main(void) {
    menu();
    return 0;
}

int menu() {  // 显示菜单
    int input_error = 0;
    while (1) {
        system("clear");  // 清空屏幕
        printf("注意!!!\n索引均从0数起\n\n");
        if (input_error != 0) {
            printf("输入有误，请重新输入！！！\n");
        }
        printf("你想操作的是：\n1.链表\n2.顺序表\n3.exit\n");
        int list_type;
        int oprt_type;
        scanf("%d", &list_type);
        switch(list_type) {
            case 1: {
                system("clear");
                printf("你现在操作的是链表\n");

                linked_list_input();

                printf("初始链表:\n");
                linked_list_output();

                input_error = 1;
                while (input_error == 1) {
                    printf("你想要的操作是：\n1.插入\n2.删除\n3.逆置\n");
                    scanf("%d", &oprt_type);

                    if (oprt_type == 1) {
                        linked_list_insert();
                        printf("插入新元素后的链表:\n");
                        linked_list_output();
                        input_error = 0;
                    } else if (oprt_type == 2) {
                        linked_list_delete();
                        printf("删除元素后的链表:\n");
                        linked_list_output();
                        input_error = 0;
                    } else if (oprt_type == 3) {
                        linked_list_reverse();
                        printf("逆置完成:\n");
                        linked_list_output();
                    } else {
                        printf("输入有误, 请重新输入\n");
                        input_error = 1;
                    }
                }
                printf("按任意键继续...\n");
                input_error = 0;
                getchar();
                getchar();
                break;
            }
            case 2: {
                system("clear");
                printf("你现在操作的是顺序表\n");

                array_list_input();

                printf("初始顺序表:\n");
                array_list_output();

                input_error = 1;
                while (input_error == 1) {
                    printf("你想要的操作是：\n1.插入\n2.删除\n3.逆置\n");
                    scanf("%d", &oprt_type);

                    if (oprt_type == 1) {
                        array_list_insert();
                        printf("插入新元素后的顺序表:\n");
                        array_list_output();
                        input_error = 0;
                    } else if (oprt_type == 2) {
                        array_list_delete();
                        printf("删除元素后的顺序表:\n");
                        array_list_output();
                        input_error = 0;
                    } else if (oprt_type == 3) {
                        array_list_reverse();
                        printf("逆置后的顺序表:\n");
                        array_list_output();
                    } else {
                        printf("输入有误, 请重新输入\n");
                        input_error = 1;
                    }
                }
                printf("按任意键继续...\n");
                input_error = 0;
                getchar();
                getchar();
                break;
            }
            case 3: {
                input_error = 0;
                return 0;  // 退出
            }
            default: {
                input_error = 1;
                break;
            }
        }
    }
    return 0;
}

int linked_list_input(void) {
    linked_list *p;
    head = (linked_list *) malloc(sizeof(linked_list));
    p = head;
    p->element = -1;
    printf("一共需要输入多少个元素?\n");
    scanf("%d", &n);
    for (int i=0;i<n;i++) {
        linked_list *new_node = (linked_list *) malloc(sizeof(linked_list));
        p->next = new_node;
        new_node->next = NULL;
        p = new_node;
        printf("No.%d 请输入一个整数做为输入元素\n", i);
        scanf("%d", &(p->element));
    }
    printf("\n================链表输入完成!================\n\n");
}

int linked_list_insert(void) {
    printf("请输入你需要插入的元素的位置(0-%d)\n", n);
    int index;
    scanf("%d", &index);

    if (index < 0 || index > n) {
        printf("无效的索引值: %d\n", index);
        return -1;
    }

    linked_list *new_node = (linked_list *) malloc(sizeof(linked_list));
    printf("输入需要插入的值:\n");
    scanf("%d", &(new_node->element));

    if (index == 0) {
        new_node->next = head;
        head = new_node;
    }
    else {
        linked_list *p = head;

        int i = 0;
        while (i < index - 1) {
            p = p->next;
            i++;
        }
        new_node->next = p->next;
        p->next = new_node;
    }
    printf("插入成功!\n");
    return 0;
}

int linked_list_delete(void) {
    int i;
    printf("输入你需要删除的元素的索引值[0-%d]:\n", n - 1);
    scanf("%d", &i);
    if (i < 0 || i > n - 1) {
        printf("无效的索引: %d\n", i);
        return -1;
    }

    linked_list *p = head;
    if (i == 0) {
        head = head->next;
        free(p);
    }
    else {
        int index = 0;
        while (index < i - 1) {
            p = p->next;
            index++;
        }
        linked_list *q = p->next;
        p->next = q->next;
        free(q);
    }
    printf("删除成功!\n");
    return 1;
}

int linked_list_output(void) {
    linked_list *p = head->next;
    int i = 0;
    while (p) {
        printf("No.%d: %d\n", i, p->element);
        p = p->next;
        i++;
    }
    return 0;
}


int linked_list_reverse(void) {
    linked_list *p = head->next;  // 工作指针
    linked_list *temp;
    linked_list *r = p->next;
    p->next = NULL;
    while (r) {  // 若r为NULL则p为最后一个元素
        temp = r->next;
        r->next = p;
        p = r;
        r = temp;
    }
    head->next = p;  // 将最后一个指针指向头节
    return 0;
}

// ==========================array list=============================


int array_list_input(void) {
    printf("一共需要输入多少个元素?\n");
    scanf("%d", &n);
    array = (int *) malloc(sizeof(int) * (n + 1));  // 分配n + 1个整数的空间做为数组
    for (int i=0;i<n;i++) {
        printf("No.%d 请输入一个整数做为输入元素\n", i);
        scanf("%d", &array[i]);
    }
    printf("顺序表输入完成\n");
    return 0;
}

int array_list_output(void) {
    for (int i=0;i<n;i++) {
        printf("No.%d: %d\n", i, array[i]);
    }
    return 0;
}

int array_list_insert(void) {
    printf("请输入你需要插入的元素的位置[0-%d]\n", n);
    int index;
    scanf("%d", &index);

    if (index < 0 || index > n) {
        printf("无效的索引值: %d\n", index);
        return -1;
    }

    int insert_value;
    printf("输入需要插入的值:\n");
    scanf("%d", &insert_value);

    for (int i=n;i>=index;i--) {
        array[i + 1] = array[i];  // 从插入位置往后挪，空出位置给新插入的元素
    }
    array[index] = insert_value;
    n++;
    printf("插入成功!\n");
}

int array_list_delete(void) {
    int index;
    printf("输入你需要删除的元素的索引值[0-%d]:\n", n - 1);
    scanf("%d", &index);
    if (index < 0 || index > n - 1) {
        printf("无效的索引: %d\n", index);
        return -1;
    }

    for (int i=index;i<n - 1;i++) {
        array[i] = array[i + 1];  // 往前挪后面的元素
    }
    n--;
    printf("删除成功!\n");
    return 0;
}

int array_list_reverse(void) {
    int temp;
    for (int i=0;i<n/2;i++) {
       temp = array[i];
       array[i] = array[n - i - 1];
       array[n - i - 1] = temp;
    }
    return 0;
}

