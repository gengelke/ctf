Bandit Level 7 → Level 8
========================

Level Goal
----------

The password for the next level is stored in the file data.txt next to the word millionth

Commands you may need to solve this level
-----------------------------------------

grep, sort, uniq, strings, base64, tr, tar, gzip, bzip2, xxd


Solution
========

```
bandit7@bandit:~$ find / -name data.txt 2>/dev/null
/home/bandit7/data.txt
/home/bandit9/data.txt
/home/bandit12/data.txt
/home/bandit10/data.txt
/home/bandit8/data.txt
/home/bandit11/data.txt
bandit7@bandit:~$ ^C
bandit7@bandit:~$ grep "millionth" data.txt
millionth	cvX2JJa4CFALtqS87jk27qwqGhBM9plV
```
