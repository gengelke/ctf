Exercise
========

Login to ```gracker.org``` with the password of user ```level2``` which we gained in level1:

```
user@system ~ $ ssh level2@gracker.org
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
level2@gracker.org's password:
X11 forwarding request failed on channel 0
YAY! You made it to level2!!!
Now read the recap of the previous level `cat recap`
And read next story: `cat story`
```
As stated by the text which is displayed after login, we start by displaying the recap of the previous level:
```
level2@gracker:~$ cat recap
This level cannot be easily solved with `strings`, because the password is
not in plaintext. This time you have to use `gdb` or a disassembler like radare2.


level1@gracker:/matrix/level1$ gdb level1
GNU gdb (Debian 7.7.1+dfsg-5) 7.7.1
(gdb) set disassembly-flavor intel
(gdb) disassemble main
Dump of assembler code for function main:
   0x000000000040083d <+0>:   push   rbp
   0x000000000040083e <+1>:   mov    rbp,rsp
[... snip ...]
   0x00000000004008a2 <+101>: movzx  eax,BYTE PTR [rax+0x600e40]
   0x00000000004008a9 <+108>: movzx  edx,BYTE PTR [rip+0x2005ad]  # 0x600e5d <XORkey> ; GDB shows us that there is a variable called XORkey
   0x00000000004008b0 <+115>: xor    edx,eax                     ; and the next asm instruction is XOR. So this is the encryption mechanism
   0x00000000004008b2 <+117>: mov    eax,DWORD PTR [rbp-0x14]
[... snip ...]
   0x00000000004008da <+157>: mov    esi,0x600e40                ; like in the last recap, we have a string compare. So one of the parameters
   0x00000000004008df <+162>: mov    rdi,rax                     ; should be our secret password
   0x00000000004008e2 <+165>: call   0x4006c0 <strcmp@plt>
   0x00000000004008e7 <+170>: test   eax,eax
[... snip ...]
   0x0000000000400915 <+216>: add    rsp,0x48
   0x0000000000400919 <+220>: pop    rbx
   0x000000000040091a <+221>: pop    rbp
   0x000000000040091b <+222>: ret
End of assembler dump.
(gdb) x/s 0x600e40                                               ; but when we try to display it, it looks like garbage
0x600e40 <secret_password>:   "/q#q%8\036&4r22$2\036\065)(t\036\061 226q3%"
(gdb) break *0x00000000004008e2                                  ; so we have to set a breakpoint before the strcmp, but after the XOR decryption
Breakpoint 1 at 0x4008e2
(gdb) r                                                          ; we run the program and enter a test password
Starting program: /matrix/level1/level1
~Zero Cool Simple Backdoor v2~
Enter Password:
test

Breakpoint 1, 0x00000000004008e2 in main ()                      ; it will break after the password decryption
(gdb) x/s 0x600e40                                               ; now we can read the decrypted password
0x600e40 <secret_password>:   "n0b0dy_gu3sses_thi5_passw0rd"

####################################################################################################################

Source code level1.c

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>

// n0b0dy_gu3sses_thi5_passw0rd
char secret_password[] =  "\x2f\x71\x23\x71\x25\x38\x1e\x26\x34\x72\x32\x32\x24\x32\x1e\x35\x29\x28\x74\x1e\x31\x20\x32\x32\x36\x71\x33\x25";
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

    printf("~Zero Cool Simple Backdoor v2~\nEnter Password:\n");
    read(STDIN_FILENO, password_input, 32);
    password_input[31]='\0';

    if ((pos=strchr(password_input, '\n')) != NULL) *pos = '\0';

    for(i=0; i<strlen(secret_password); i++) {
        secret_password[i] = secret_password[i] ^ XORkey;
    }

    if(strcmp(password_input,secret_password)==0) {
        printf("Correct! Here is the level2 shell.\nRead the level2 password in /home/level2/.pass to login with `ssh level2@gracker.org`\n");
        spawn_shell();
    } else{
        printf("wrong!");
    }

    return 0;
}
```
After this, we can display this level's story file in order to find out what we have to do in order to get the password of level3:
```
level2@gracker:~$ cat story
┌─────────────┐
│ Level Up +1 │
└─────────────┘

it looks like Zero Cool modified his backoor again.  Probably because it
was  too easy  for other  hackers to  use  his backdoors.  Comparing the
assembly code from his previous backdoor version to now reveals, that it
is not much different. But this simple change could make it a little bit
harder.  Can you still  find  the correct password  to use  the backdoor
and get access to level3?

   backdoor: /matrix/level2/level2

Don't forget to have a look at the story recap of level1. You can read it
with: `less /home/level2/recap` (scroll with arrow keys and quit with "q")
You should  have a look  at how `gdb` works  and practice with this level.
Important `gdb` commands for you to research are:
 ● `disassemble main` - look at the assembly code of the main function
 ● `break *0x12345678` - set a breakpoint at address 0x12345678
 ● `x 0x12345678` - examine/print the content of address 0x12345678
 ● `x/xw 0x12345678` - print the content of address 0x12345678 as hex word
 ● `x/s 0x12345678` - print the content of address 0x12345678 as a string
 ● `run` - run/restart the program you are debugging
 ● `continue` - continue execution after you stopped at a breakpoint
 ● `quit` - exit gdb

Also google can help a lot to learn how to use `gdb`. Good luck!
```
Solution
========
```
level2@gracker:~$ gdb -q /matrix/level2/level2
Reading symbols from /matrix/level2/level2...(no debugging symbols found)...done.
(gdb) set disassembly-flavor intel
(gdb) disass main
Dump of assembler code for function main:
   0x000000000040083d <+0>:	push   rbp
   0x000000000040083e <+1>:	mov    rbp,rsp
   0x0000000000400841 <+4>:	push   rbx
   0x0000000000400842 <+5>:	sub    rsp,0x48
   0x0000000000400846 <+9>:	mov    DWORD PTR [rbp-0x44],edi
   0x0000000000400849 <+12>:	mov    QWORD PTR [rbp-0x50],rsi
   0x000000000040084d <+16>:	mov    edi,0x4009b0
   0x0000000000400852 <+21>:	call   0x400620 <puts@plt>
   0x0000000000400857 <+26>:	lea    rax,[rbp-0x40]
   0x000000000040085b <+30>:	mov    edx,0x20
   0x0000000000400860 <+35>:	mov    rsi,rax
   0x0000000000400863 <+38>:	mov    edi,0x0
   0x0000000000400868 <+43>:	call   0x4006a0 <read@plt>
   0x000000000040086d <+48>:	mov    BYTE PTR [rbp-0x21],0x0
   0x0000000000400871 <+52>:	lea    rax,[rbp-0x40]
   0x0000000000400875 <+56>:	mov    esi,0xa
   0x000000000040087a <+61>:	mov    rdi,rax
   0x000000000040087d <+64>:	call   0x400670 <strchr@plt>
   0x0000000000400882 <+69>:	mov    QWORD PTR [rbp-0x20],rax
   0x0000000000400886 <+73>:	cmp    QWORD PTR [rbp-0x20],0x0
   0x000000000040088b <+78>:	je     0x400894 <main+87>
   0x000000000040088d <+80>:	mov    rax,QWORD PTR [rbp-0x20]
   0x0000000000400891 <+84>:	mov    BYTE PTR [rax],0x0
   0x0000000000400894 <+87>:	mov    DWORD PTR [rbp-0x14],0x0
   0x000000000040089b <+94>:	jmp    0x4008bd <main+128>
   0x000000000040089d <+96>:	mov    eax,DWORD PTR [rbp-0x14]
   0x00000000004008a0 <+99>:	cdqe
   0x00000000004008a2 <+101>:	movzx  eax,BYTE PTR [rbp+rax*1-0x40]
   0x00000000004008a7 <+106>:	movzx  edx,BYTE PTR [rip+0x2005d2]        # 0x600e80 <XORkey>
   0x00000000004008ae <+113>:	xor    edx,eax
   0x00000000004008b0 <+115>:	mov    eax,DWORD PTR [rbp-0x14]
   0x00000000004008b3 <+118>:	cdqe
   0x00000000004008b5 <+120>:	mov    BYTE PTR [rbp+rax*1-0x40],dl
---Type <return> to continue, or q <return> to quit---
   0x00000000004008b9 <+124>:	add    DWORD PTR [rbp-0x14],0x1
   0x00000000004008bd <+128>:	mov    eax,DWORD PTR [rbp-0x14]
   0x00000000004008c0 <+131>:	movsxd rbx,eax
   0x00000000004008c3 <+134>:	lea    rax,[rbp-0x40]
   0x00000000004008c7 <+138>:	mov    rdi,rax
   0x00000000004008ca <+141>:	call   0x400640 <strlen@plt>
   0x00000000004008cf <+146>:	cmp    rbx,rax
   0x00000000004008d2 <+149>:	jb     0x40089d <main+96>
   0x00000000004008d4 <+151>:	lea    rax,[rbp-0x40]
   0x00000000004008d8 <+155>:	mov    esi,0x600e60
   0x00000000004008dd <+160>:	mov    rdi,rax
   0x00000000004008e0 <+163>:	call   0x4006c0 <strcmp@plt>
   0x00000000004008e5 <+168>:	test   eax,eax
   0x00000000004008e7 <+170>:	jne    0x4008ff <main+194>
   0x00000000004008e9 <+172>:	mov    edi,0x4009e0
   0x00000000004008ee <+177>:	call   0x400620 <puts@plt>
   0x00000000004008f3 <+182>:	mov    eax,0x0
   0x00000000004008f8 <+187>:	call   0x4007e6 <spawn_shell>
   0x00000000004008fd <+192>:	jmp    0x40090e <main+209>
   0x00000000004008ff <+194>:	mov    edi,0x400a59
   0x0000000000400904 <+199>:	mov    eax,0x0
   0x0000000000400909 <+204>:	call   0x400680 <printf@plt>
   0x000000000040090e <+209>:	mov    eax,0x0
   0x0000000000400913 <+214>:	add    rsp,0x48
   0x0000000000400917 <+218>:	pop    rbx
   0x0000000000400918 <+219>:	pop    rbp
   0x0000000000400919 <+220>:	ret
End of assembler dump.
```
```
(gdb) break *0x00000000004008e0
Breakpoint 1 at 0x4008e0
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /matrix/level2/level2
~Zero Cool Simple Backdoor v3~
Enter Password:
AAAA

Breakpoint 1, 0x00000000004008e0 in main ()
(gdb) x/s $rdi
0x7fffffffeac0:	""
(gdb) x/s $esi
0x600e60 <secret_password>:	")q6\036(2\036\065)p2\036)u\"*r3\036'q--q6(/&\036,r"
```
```
   0x00000000004008a7 <+106>:	movzx  edx,BYTE PTR [rip+0x2005d2]        # 0x600e80 <XORkey>
```
```
(gdb) print XORkey
$1 = 65
```
```
0x600e80 <XORkey>:	"A"
```
```
(gdb)  r <<< $(python -c "print ')q6\036(2\036\065)p2\036)u\"*r3\036\'q--q6(/&\036,r'")
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /matrix/level2/level2 <<< $(python -c "print ')q6\036(2\036\065)p2\036)u\"*r3\036\'q--q6(/&\036,r'")
~Zero Cool Simple Backdoor v3~
Enter Password:

Breakpoint 1, 0x00007ffff7ac3450 in ?? () from /lib/x86_64-linux-gnu/libc.so.6
(gdb) x/s $rdi
0x7fffffffeac0:	"h0w_is_th1s_h4ck3r_f0ll0wing_m3"
(gdb) x/s $esi
0x600e60 <secret_password>:	")q6\036(2\036\065)p2\036)u\"*r3\036'q--q6(/&\036,r"
```
```
level2@gracker:~$ /matrix/level2/level2
~Zero Cool Simple Backdoor v3~
Enter Password:
h0w_is_th1s_h4ck3r_f0ll0wing_m3
Correct! Here is the level3 shell.
Read the level3 password in /home/level3/.pass to login with `ssh level3@gracker.org`
$ whoami
level3
$ cat /home/level3/.pass
kgg9ki?iDero
```
