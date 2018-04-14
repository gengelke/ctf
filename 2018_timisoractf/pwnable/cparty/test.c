#include <stdio.h>

int function( void ) {
    return 0x4711;
}

int main( void ) {
    int ret;
    ret = function();
    if(ret==0x4711) {
        printf("0x4711");
    }
    return 0;
}
