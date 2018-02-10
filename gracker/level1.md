Exercise
========

Login to gracker.org with the password of user ```level1``` which we gained in level0:
```
user@system ~ $ ssh level1@gracker.org
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
level1@gracker.org's password:
X11 forwarding request failed on channel 0
YAY! You made it to level1!!!
Now read the recap of the previous level `cat recap`
And read next story: `cat story`
```
As stated by the text which is displayed after login, we start by displaying the recap of the previous level:
```
level1@gracker:~$ cat recap
The easiest solution was probably `strings level0` and look for a string that looks like a password.
Another option would have been using `gdb`. It was not necessary here, but it's important to learn
how to use gdb:

######################################################################################################

level0@gracker:/matrix/level0$ gdb level0
GNU gdb (Debian 7.7.1+dfsg-5) 7.7.1
Copyright (C) 2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from level0...(no debugging symbols found)...done.
(gdb) set disassembly-flavor intel
(gdb) disassemble main
Dump of assembler code for function main:
   0x0000000000400796 <+0>: push   rbp
   0x0000000000400797 <+1>: mov    rbp,rsp
   0x000000000040079a <+4>: sub    rsp,0x40
   0x000000000040079e <+8>: mov    DWORD PTR [rbp-0x34],edi
[... snip ...]
   0x0000000000400827 <+145>:   mov    BYTE PTR [rax],0x0
   0x000000000040082a <+148>:   lea    rax,[rbp-0x30]
   0x000000000040082e <+152>:   mov    esi,0x600db0
   0x0000000000400833 <+157>:   mov    rdi,rax
   0x0000000000400836 <+160>:   call   0x400670 <strcmp@plt>  ; <--  strcmp() is always a very good place for password comparisons
[... snip ...]                                                ;      So strcmp has to load the parameters. Often on the stack or
   0x0000000000400853 <+189>:   call   0x400610 <system@plt>  ;      via registers. In this case the `mov esi,0x600db0` looks
   0x0000000000400858 <+194>:   jmp    0x400869 <main+211>    ;      interesting.
   0x000000000040085a <+196>:   mov    edi,0x4009f9
   0x000000000040085f <+201>:   mov    eax,0x0
   0x0000000000400864 <+206>:   call   0x400630 <printf@plt>
   0x0000000000400869 <+211>:   mov    eax,0x0
   0x000000000040086e <+216>:   leave
   0x000000000040086f <+217>:   ret
End of assembler dump.
(gdb) x/s 0x600db0                                            ; <--  so we can use gdb examine (x) command to look at this address
0x600db0 <secret_password>: "s3cr3t_backd00r_passw0rd"        ;      and we see the variable name and it's content.
(gdb)

######################################################################################################

Here is also the sourcecode of level0. So you can better understand how it worked.


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

char secret_password[] = "s3cr3t_backd00r_passw0rd";

int main (int argc, char *argv[]) {
    gid_t gid;
    uid_t uid;
    char password_input[32];
    char *pos;

    gid = getegid();
    uid = geteuid();

    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);

    printf(" _____\n| _ _ |\n|| | || Hidden\n||_|_||   Backdoor\n| _ _ o  by \n|| | ||     ~Zero Cool\n||_|_||  \n|_____|\n\nEnter Secret Password:\n");

    read(STDIN_FILENO, password_input, 32);
    password_input[31]='\0';

    if ((pos=strchr(password_input, '\n')) != NULL) *pos = '\0';

    if(strcmp(password_input,secret_password)==0) {
        printf("Correct! Here is the level1 shell.\nRead the level1 password in /home/level1/.pass to login with `ssh level1@gracker.org`\n");
        system("/bin/sh");
    } else{
        printf("wrong!");
    }

    return 0;
}
```
After this, we can display this level's story file in order to find out what we have to do in order to get the password of level2:
```
level1@gracker:~$ cat story
┌───────────────────┐
│ Knock, knock, ... │
└───────────────────┘
Zero Cool noticed  that  another hacker found his backdoor  and used it to
gain access to  level1.  When Zero Cool  looked at his code,  he realised,
that it is not intelligent to have the password inside the program.  So he
decided to encrypt it.  Can you still recover the secret password  that is
needed to unlock Zero Cool's backdoor?

   backdoor: /matrix/level1/level1

Don't forget to have a look at the story recap of level0. You can read it
with: `less /home/level1/recap` (scroll with arrow keys and quit with "q")
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

Now we should have enough information and tools we need to get the password for level2. Since this time the ```strings``` command doesn't display a reasonable humand readable password from the backdoor binary, we follow the ```gdb``` approach this time:

```
level1@gracker:~$gdb -q /matrix/level1/level1
Reading symbols from /matrix/level1/level1...(no debugging symbols found)...done.
(gdb) set disassembly-flavor intel
(gdb) disassemble main
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
   0x000000000040089b <+94>:	jmp    0x4008c1 <main+132>
   0x000000000040089d <+96>:	mov    eax,DWORD PTR [rbp-0x14]
   0x00000000004008a0 <+99>:	cdqe
   0x00000000004008a2 <+101>:	movzx  eax,BYTE PTR [rax+0x600e40]
   0x00000000004008a9 <+108>:	movzx  edx,BYTE PTR [rip+0x2005ad]        # 0x600e5d <XORkey>
   0x00000000004008b0 <+115>:	xor    edx,eax
   0x00000000004008b2 <+117>:	mov    eax,DWORD PTR [rbp-0x14]
   0x00000000004008b5 <+120>:	cdqe
   0x00000000004008b7 <+122>:	mov    BYTE PTR [rax+0x600e40],dl
---Type <return> to continue, or q <return> to quit---
   0x00000000004008bd <+128>:	add    DWORD PTR [rbp-0x14],0x1
   0x00000000004008c1 <+132>:	mov    eax,DWORD PTR [rbp-0x14]
   0x00000000004008c4 <+135>:	movsxd rbx,eax
   0x00000000004008c7 <+138>:	mov    edi,0x600e40
   0x00000000004008cc <+143>:	call   0x400640 <strlen@plt>
   0x00000000004008d1 <+148>:	cmp    rbx,rax
   0x00000000004008d4 <+151>:	jb     0x40089d <main+96>
   0x00000000004008d6 <+153>:	lea    rax,[rbp-0x40]
   0x00000000004008da <+157>:	mov    esi,0x600e40
   0x00000000004008df <+162>:	mov    rdi,rax
   0x00000000004008e2 <+165>:	call   0x4006c0 <strcmp@plt>
   0x00000000004008e7 <+170>:	test   eax,eax
   0x00000000004008e9 <+172>:	jne    0x400901 <main+196>
   0x00000000004008eb <+174>:	mov    edi,0x4009e0
   0x00000000004008f0 <+179>:	call   0x400620 <puts@plt>
   0x00000000004008f5 <+184>:	mov    eax,0x0
   0x00000000004008fa <+189>:	call   0x4007e6 <spawn_shell>
   0x00000000004008ff <+194>:	jmp    0x400910 <main+211>
   0x0000000000400901 <+196>:	mov    edi,0x400a59
   0x0000000000400906 <+201>:	mov    eax,0x0
   0x000000000040090b <+206>:	call   0x400680 <printf@plt>
   0x0000000000400910 <+211>:	mov    eax,0x0
   0x0000000000400915 <+216>:	add    rsp,0x48
   0x0000000000400919 <+220>:	pop    rbx
   0x000000000040091a <+221>:	pop    rbp
   0x000000000040091b <+222>:	ret
End of assembler dump.
```
Like in level0, there's a call to ```strcmp``` as described in the level0 ```recap``` which in included at the beginning of this document. ```strcmp``` compares to values which are stored at register ```esi``` and ```rdi```:
```
   0x00000000004008da <+157>:	mov    esi,0x600e40
   0x00000000004008df <+162>:	mov    rdi,rax
   0x00000000004008e2 <+165>:	call   0x4006c0 <strcmp@plt>
```
So all we have to do is to set a break point to the call of ```strcmp``` which is located at address ```0x00000000004008e2``` or ```(main+165)``` in short form. Then we start the execution of the backdoor code and enter an arbitrary password which we can easily remember, let's say ```DONTKNOW```:
```
(gdb) break *0x00000000004008e2
Breakpoint 1 at 0x4008e2
(gdb) run
Starting program: /matrix/level1/level1
~Zero Cool Simple Backdoor v2~
Enter Password:
DONTKNOW

Breakpoint 1, 0x00000000004008e2 in main ()
```
In order to get the password for the level1 backdoor, we then display the contents of the ```esi``` and ```rdi``` registers:
```
(gdb) x /s $esi
0x600e40 <secret_password>:	"n0b0dy_gu3sses_thi5_passw0rd"
(gdb) x /s $rdi
0x7fffffffeac0:	"DONTKNOW"
```
Finally we execute the backdoor binary outside of ```gdb``` and enter it's password ```n0b0dy_gu3sses_thi5_passw0rd``` in order to get the next level's password:
```
level1@gracker:~$ /matrix/level1/level1
~Zero Cool Simple Backdoor v2~
Enter Password:
n0b0dy_gu3sses_thi5_passw0rd
Correct! Here is the level2 shell.
Read the level2 password in /home/level2/.pass to login with `ssh level2@gracker.org`
$ whoami
level2
$ cat /home/level2/.pass
rAWJ@yDbZo4c
```
