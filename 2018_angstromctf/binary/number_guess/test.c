#include <stdio.h>

int main( void ) {
    int a = 0xdeadbeef;
    char *flag = "ABCD";
    char buf[16];
    int b = 0xcafebabe;

    scanf("%s", &buf);
    printf(buf);
}
