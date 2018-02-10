Bandit Level 1 → Level 2
========================

Level Goal
----------

The password for the next level is stored in a file called - located in the home directory

Commands you may need to solve this level
-----------------------------------------

ls, cd, cat, file, du, find

Helpful Reading Material
------------------------

[Google Search for “dashed filename”](https://www.google.com/search?q=dashed+filename)

[Advanced Bash-scripting Guide - Chapter 3 - Special Characters](http://tldp.org/LDP/abs/html/special-chars.html)

Solution
========

The solution for this one is pretty similar to the one of level0-1. But while the filename of the previous level just contained letters, the filename of this level is the special character "-":

```
bandit1@bandit:~$ ls -al
total 28
-rw-r-----  1 bandit2 bandit1   33 Sep 28 14:04 -
drwxr-xr-x  3 bandit1 bandit1 4096 Oct 25 20:27 .
drwxr-xr-x 30 root    root    4096 Oct 25 20:27 ..
-rw-r--r--  1 bandit1 bandit1  220 Apr  9  2014 .bash_logout
-rw-r--r--  1 bandit1 bandit1 3637 Apr  9  2014 .bashrc
drwx------  2 bandit1 bandit1 4096 Oct 25 20:27 .cache
-rw-r--r--  1 bandit1 bandit1  675 Apr  9  2014 .profile
```

If we woud now try to display it's content using cat, we would not be successful because the "-" would be mis-interpreted as a representation of stdin/stdout. 
So if we would just do a "cat -" like in the previous level, the command would not return because it would read from stdin and write to stdout for ever.
Therefore we have to find a way how special characters can be 'masked' in order to tell the cat tool, that "-" is an actual filename instead of stdin/stdout.
The usual way of doing this is to prefix the filename with a full path. In this specific cse it could be ./- or ~/- or /home/bandit1/-

```
bandit1@bandit:~$ cat ./-
CV1DtqXWVFXTvM2F0k09SHz0YwRINYA9
```
