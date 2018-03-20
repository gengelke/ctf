
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "lobby.h"

void parse_bytes(unsigned char *dest, const char *src, size_t n)
{
    /** size 3 is important to make sure tmp is \0-terminated and
        the initialization guarantees that the array is filled with zeros */
    char tmp[3] = "";

    while (n--) {
      tmp[0] = *src++;
      tmp[1] = *src++;
      *dest++ = strtol(tmp, NULL, 16);
    }
}


int main(int argc, char** argv)
{
    unsigned char random_buf[32] = {0};
    unsigned char demangled_buf[256] = {0};
    unsigned char input_buf[32] = {0};
    unsigned char inputstr[64] = {0};
    memcpy(inputstr, argv[1], 64);

    printf("size of input: %d\n", sizeof(inputstr));
    setvbuf(stdout, NULL, _IONBF, 0);
    //get_random_data(random_buf, sizeof(random_buf));

    parse_bytes(random_buf, inputstr, 32);
    printf("input:  ");
    print_hex_data(random_buf, 32);
    puts("");

    demangle(random_buf, demangled_buf);
    //mangle(random_buf, mangled_buf);

    printf("output: ");
    print_hex_data(demangled_buf, 32);
    puts("");
//    print_hex_data(random_buf, 32);
//    puts("");

//    printf("Yo, tell me what the story was:\n");
//    fflush(stdout);
//    read_hex_data(input_buf, 32);

/*    // Vuln
    if (!strncmp(random_buf, input_buf, 32)) {
        printf("Good guess!\n");
        printf("Now please enter the lobby.\n");

        //lobby();
    } else {
        printf("WRONG!\n");
        _exit(-1);
    }
*/
}

