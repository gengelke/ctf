Bandit Level 4 → Level 5
========================

Level Goal
----------

The password for the next level is stored in the only human-readable file in the inhere directory. Tip: if your terminal is messed up, try the “reset” command.

Commands you may need to solve this level
-----------------------------------------

ls, cd, cat, file, du, find


Solution
========

```
bandit4@bandit:~$ cd inhere/
bandit4@bandit:~/inhere$ ls -al
total 48
-rw-r----- 1 bandit5 bandit4   33 Sep 28 14:04 -file00
-rw-r----- 1 bandit5 bandit4   33 Sep 28 14:04 -file01
-rw-r----- 1 bandit5 bandit4   33 Sep 28 14:04 -file02
-rw-r----- 1 bandit5 bandit4   33 Sep 28 14:04 -file03
-rw-r----- 1 bandit5 bandit4   33 Sep 28 14:04 -file04
-rw-r----- 1 bandit5 bandit4   33 Sep 28 14:04 -file05
-rw-r----- 1 bandit5 bandit4   33 Sep 28 14:04 -file06
-rw-r----- 1 bandit5 bandit4   33 Sep 28 14:04 -file07
-rw-r----- 1 bandit5 bandit4   33 Sep 28 14:04 -file08
-rw-r----- 1 bandit5 bandit4   33 Sep 28 14:04 -file09
drwxr-xr-x 2 root    root    4096 Sep 28 14:04 .
drwxr-xr-x 4 bandit4 bandit4 4096 Oct 25 21:11 ..
bandit4@bandit:~/inhere$ file ./-file00
./-file00: Non-ISO extended-ASCII text, with CR line terminators, with escape sequences
bandit4@bandit:~/inhere$ file ./-file01
./-file01: data
bandit4@bandit:~/inhere$ file ./-file02
./-file02: data
bandit4@bandit:~/inhere$ file ./-file03
./-file03: data
bandit4@bandit:~/inhere$ file ./-file04
./-file04: data
bandit4@bandit:~/inhere$ file ./-file05
./-file05: data
bandit4@bandit:~/inhere$ file ./-file06
./-file06: data
bandit4@bandit:~/inhere$ file ./-file07
./-file07: ASCII text
bandit4@bandit:~/inhere$ cat ./-file07
koReBOKuIDDepwhWk7jZC0RTdopnAYKh
```
