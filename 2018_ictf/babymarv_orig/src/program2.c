
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
    unsigned char mangled_buf[256] = {0};
    unsigned char input_buf[32] = {0};

    unsigned char inputstr[32] = {0};


    setvbuf(stdout, NULL, _IONBF, 0);

    //get_random_data(random_buf, sizeof(random_buf));


   // memcpy(random_buf,argv[1], sizeof(random_buf));
parse_bytes(random_buf,argv[1],sizeof(random_buf));

    

    printf("Let me come up with a story...\n");
    demangle(random_buf, mangled_buf);

    printf("OK, here is the happy ending of the story:\n");
    print_hex_data(mangled_buf + 256 - 32, 32);
    printf("\n");

    print_hex_data(random_buf, 32);
    puts("");

    printf("Yo, tell me what the story was:\n");
    fflush(stdout);
    read_hex_data(input_buf, 32);

    // Vuln
    if (!strncmp(random_buf, input_buf, 32)) {
        printf("Good guess!\n");
        printf("Now please enter the lobby.\n");

        lobby();
    } else {
        printf("WRONG!\n");
        _exit(-1);
    }
}

