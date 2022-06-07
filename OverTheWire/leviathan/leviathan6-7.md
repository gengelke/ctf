Leviathan Level 6 → Level 7
===========================

Level Goal
----------

There is no information for this level, intentionally.

Solution
========

There's no hint text or anything else for this level. So let's look around what we can find in the home directory:

```
leviathan6@leviathan:~$ ls -al
total 28
drwxr-xr-x  2 root       root       4096 Aug 26  2019 .
drwxr-xr-x 10 root       root       4096 Aug 26  2019 ..
-rw-r--r--  1 root       root        220 May 15  2017 .bash_logout
-rw-r--r--  1 root       root       3526 May 15  2017 .bashrc
-r-sr-x---  1 leviathan7 leviathan6 7452 Aug 26  2019 leviathan6
-rw-r--r--  1 root       root        675 May 15  2017 .profile
```

Let's see what binary file **leviathan6** does when we execute it:

```
leviathan6@leviathan:~$ ./leviathan6
usage: ./leviathan6 <4 digit code>
```

The binary expects one argument containing a 4 digit code. If we enter the wrong code, the binary just says "Wrong":
```
leviathan6@leviathan:~$ ./leviathan6 1234
Wrong
```

We simply brute force the 4 digit code ;-)

```
leviathan6@leviathan:~$ for i in {0000..9999}; do echo $i; ./leviathan6 $i; sleep 0.01; done
0000
Wrong
0001
Wrong
0002
Wrong
0003
Wrong
[...]
7120
Wrong
7121
Wrong
7122
Wrong
7123   <-----{THAT'S THE CORRECT 4 DIGIT CODE}
$ cat /etc/leviathan_pass/leviathan7
ahy7MaeBo9
```

```
leviathan6@leviathan:~$ gdb -q leviathan6
Reading symbols from leviathan6...(no debugging symbols found)...done.
(gdb) disas main
Dump of assembler code for function main:
   0x0804853b <+0>:	lea    0x4(%esp),%ecx
   0x0804853f <+4>:	and    $0xfffffff0,%esp
   0x08048542 <+7>:	pushl  -0x4(%ecx)
   0x08048545 <+10>:	push   %ebp
   0x08048546 <+11>:	mov    %esp,%ebp
   0x08048548 <+13>:	push   %ebx
   0x08048549 <+14>:	push   %ecx
   0x0804854a <+15>:	sub    $0x10,%esp
   0x0804854d <+18>:	mov    %ecx,%eax
   0x0804854f <+20>:	movl   $0x1bd3,-0xc(%ebp)            <----- 0x1bd3 == 7123 decimal
   0x08048556 <+27>:	cmpl   $0x2,(%eax)
   0x08048559 <+30>:	je     0x804857b <main+64>
   [...]
(gdb) b *main+27
Breakpoint 1 at 0x8048556
(gdb) r 4711
Starting program: /home/leviathan6/leviathan6 4711

Breakpoint 1, 0x08048556 in main ()
(gdb) x/w $esp+0xc
0xffffd64c:	7123
```
