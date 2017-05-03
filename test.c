// @island
// 2017-04-05 18:27:26
#include <stdio.h>
#include <math.h>
#include <string.h>

int parse_int(char[]);

int main(void) {
    char a[10];
    scanf("%s", a);
    int b = parse_int(a);
    printf("%d\n", b);
    char c[9];
    c[0] = c[1] = c[2] = '0';
    printf("len(c): %ld\n", strlen(c));
    return 0;
}

int parse_int(char int_str[]) {
    int len = strlen(int_str);
    printf("len: %d\n", len);
    int result = 0;
    int bit;
    for (int i=len - 1;i>=0;i--) {
        bit = int_str[i] - 48;
        result += (int) (bit * pow(10, len - i - 1));
    }
    return result;
}
