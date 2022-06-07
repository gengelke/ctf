Leviathan Level 3 → Level 4
===========================

Level Goal
----------

There is no information for this level, intentionally.

Solution
========

There's no hint text or anything else for this level. So let's look around what we can find in the home directory:

```
leviathan4@leviathan:~$ ls -al
total 32
drwxr-xr-x  2 root       root        4096 Aug 26  2019 .
drwxr-xr-x 10 root       root        4096 Aug 26  2019 ..
-rw-r--r--  1 root       root         220 May 15  2017 .bash_logout
-rw-r--r--  1 root       root        3526 May 15  2017 .bashrc
-r-sr-x---  1 leviathan4 leviathan3 10288 Aug 26  2019 level3
-rw-r--r--  1 root       root         675 May 15  2017 .profile
```

There's a binary named **level3** owned by user **leviathan4** which looks promising, so we execute the binary in order find out what it does:

```
leviathan4@leviathan:~$ ./level3
Enter the password> dontknow
bzzzzzzzzap. WRONG
```

It asks for a password and exits when now correct password has been given. Let's execute it inside of **ltrace** in order to find out what the binary does under the hood:

```
leviathan3@leviathan:~$ ltrace ./level3
__libc_start_main(0x8048618, 1, 0xffffd744, 0x80486d0 <unfinished ...>
strcmp("h0no33", "kakaka")                                                                                                       = -1
printf("Enter the password> ")                                                                                                   = 20
fgets(Enter the password> dontknow
"dontknow\n", 256, 0xf7fc55a0)                                                                                             = 0xffffd550
strcmp("dontknow\n", "snlprintf\n")                                                                                              = -1
puts("bzzzzzzzzap. WRONG"bzzzzzzzzap. WRONG
)                                                                                                       = 19
+++ exited (status 0) +++
```

We've just found the correct password! :-) It can be found in the strcmp() function which is used to compare two strings:

```
NAME
       strcmp, strncmp - compare two strings

SYNOPSIS
       #include <string.h>

       int strcmp(const char *s1, const char *s2);

       int strncmp(const char *s1, const char *s2, size_t n);

DESCRIPTION
       The  strcmp()  function compares the two strings s1 and s2.  It returns an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater
       than s2.

       The strncmp() function is similar, except it compares only the first (at most) n bytes of s1 and s2.
```

We can see, that our entered password **dontknow** is compared with **snlprintf**:
```
strcmp("dontknow\n", "snlprintf\n")                                                                                              = -1
```

So the password for the **level3** binary is **snlprintf**. Let's grab the actual password for the next level!

```
leviathan3@leviathan:~$ ./level3
Enter the password> snlprintf
[You've got shell]!
$ cat /etc/leviathan_pass/leviathan4
vuH0coox6m
```
