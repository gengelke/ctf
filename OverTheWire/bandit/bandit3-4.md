Bandit Level 3 → Level 4
========================

Level Goal
----------

The password for the next level is stored in a hidden file in the inhere directory.

Commands you may need to solve this level
-----------------------------------------

ls, cd, cat, file, du, find


Solution
========

```
bandit3@bandit:~$ ls -la
total 28
drwxr-xr-x  4 bandit3 bandit3 4096 Oct 25 21:07 .
drwxr-xr-x 30 root    root    4096 Oct 25 21:07 ..
-rw-r--r--  1 bandit3 bandit3  220 Apr  9  2014 .bash_logout
-rw-r--r--  1 bandit3 bandit3 3637 Apr  9  2014 .bashrc
drwx------  2 bandit3 bandit3 4096 Oct 25 21:07 .cache
-rw-r--r--  1 bandit3 bandit3  675 Apr  9  2014 .profile
drwxr-xr-x  2 root    root    4096 Sep 28 14:04 inhere
bandit3@bandit:~$ cd inhere/
bandit3@bandit:~/inhere$ ls -al
total 12
drwxr-xr-x 2 root    root    4096 Sep 28 14:04 .
drwxr-xr-x 4 bandit3 bandit3 4096 Oct 25 21:07 ..
-rw-r----- 1 bandit4 bandit3   33 Sep 28 14:04 .hidden
bandit3@bandit:~/inhere$ cat .hidden
pIwrPrtPN36QITSp3EQaw936yaFoFgAB
```
