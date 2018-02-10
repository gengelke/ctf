Bandit Level 17 → Level 18
==========================

Level Goal
----------

There are 2 files in the homedirectory: passwords.old and passwords.new. The password for the next level is in passwords.new and is the only line that has been changed between passwords.old and passwords.new

NOTE: if you have solved this level and see ‘Byebye!’ when trying to log into bandit18, this is related to the next level, bandit19

Commands you may need to solve this level
-----------------------------------------

cat, grep, ls, diff

Solution
========

```
bandit17@bandit:~$ diff passwords.new passwords.old
42c42
< kfBf3eYk5BPBRzwjqutbbfE887SVc5Yd
---
> R3GQabj3vKRTcjTTISWvO1RJWc5sqSXO
```

That was easy. The password is ```kfBf3eYk5BPBRzwjqutbbfE887SVc5Yd```. If we paste it into the ssh command's stdin we get "Byebye!" as expected by the task description text:

```
bandit17@bandit:~$ ssh bandit18@localhost
[...]

Byebye !
Connection to localhost closed.
bandit17@bandit:~$
```
