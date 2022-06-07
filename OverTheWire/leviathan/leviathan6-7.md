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
