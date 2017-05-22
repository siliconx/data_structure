// @siliconx
// 2017-05-22 14:52:58
// 开发环境: Linux(Ubuntu 17.04), gcc 6.3.0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_LEN 64
#define MAXSIZE 34
#define OK 0
#define ERROR -1
#define STRING_LEN 256

#define COLOR_RED "\x1b[31m"
#define COLOR_END "\x1b[0m"

typedef struct {
    char ID[CHAR_LEN];
    char name[CHAR_LEN];
    int data_structure;
    int clang;
    int english;
    int gis;
} student;

student students[MAXSIZE];  // 学生信息
char output_string[STRING_LEN];  // 需要输出到文件的格式化后的字符串
FILE *input_file, *log_file;  // 分别是输入文件、输出文件
int line_num;  // 输入文件行数

int initialize(void);  // 初始化
int read_file(void);  // 读入数据
int print_info(int);  // 打印学生信息
int search(char*);  // 查找
int write_log(char*);  // 记录结果

int main(void) {
    initialize();
    read_file();
    char name[CHAR_LEN];
    int result = 0;
    while (1) {
        printf("who are you looking for?" COLOR_RED "(`q` to quit)\n" COLOR_END);
        scanf("%s", name);
        if (strcmp(name, "q") == 0) {
            printf("Bye\n");
            exit(0);
        }
        result = search(name);
        if (result >= 0) {  // 查找成功
            printf(COLOR_RED "%s's information:\n", name);
            print_info(result);
            printf(COLOR_END);
        } else {  // 查找失败
            printf(COLOR_RED "`%s`not found!\n" COLOR_END, name);
            sprintf(output_string, "`%s`not found\n", name);
            write_log(output_string);
        }
    }
    return OK;
}

int initialize(void) {
    // 初始化
    input_file = NULL;
    log_file = NULL;
    line_num = 0;
    return OK;
}

int read_file(void) {
    input_file = fopen("Score.txt", "r");
    if (input_file == NULL) {
        printf("open input file failed\n");
        exit(-1);
    }

    while(! feof(input_file)) {
        fscanf(input_file, "%s %s %d %d %d %d",
            students[line_num].ID, students[line_num].name,
            &students[line_num].data_structure, &students[line_num].clang,
            &students[line_num].english, &students[line_num].gis);
        line_num++;
    }
    fclose(input_file);
    return OK;
}

int print_info(int i) {
    if (i < 0 || i > MAXSIZE) {
        printf("invalid index\n");
        return ERROR;
    }

    // 输出到屏幕
    printf("======================\n");
    printf("ID: %s\nname: %s\ndata_structure: %d\nclang: %d\nenglish: %d\nGIS: %d\n",
        students[i].ID, students[i].name,
        students[i].data_structure, students[i].clang,
        students[i].english, students[i].gis);
    printf("======================\n");

    // 生成格式化字符串
    sprintf(output_string,
        "ID: %s, name: %s, data_structure: %d, clang: %d, english: %d, GIS: %d\n",
        students[i].ID, students[i].name,
        students[i].data_structure, students[i].clang,
        students[i].english, students[i].gis);
    // 将字符串输出到日志文件
    write_log(output_string);
    return OK;
}

int search(char *name) {
    for (int i=0;i<MAXSIZE;i++) {  // 顺序查找所有学生
        if (strcmp(name, students[i].name) == 0) {  // 查找成功
            return i;
        }
    }
    return ERROR;
}

int write_log(char *data) {
    log_file = fopen("SearchResult.txt", "a");
    if (log_file == NULL) {
        printf("open log file failed\n");
        return ERROR;
    }
    fprintf(log_file, data, '\n');
    fclose(log_file);
    return OK;
}

