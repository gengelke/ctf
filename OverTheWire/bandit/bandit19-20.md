Bandit Level 19 → Level 20
==========================

Level Goal
----------

To gain access to the next level, you should use the setuid binary in the homedirectory. Execute it without arguments to find out how to use it. The password for this level can be found in the usual place (/etc/bandit_pass), after you have used the setuid binary.

Helpful Reading Material
------------------------

[setuid on Wikipedia](http://en.wikipedia.org/wiki/Setuid)


Solution
========

First of all we do what the text told us and execute the mentioned setuid binary:

```
bandit19@bandit:~$ ./bandit20-do
Run a command as another user.
  Example: ./bandit20-do id
bandit19@bandit:~$ ./bandit20-do id
uid=11019(bandit19) gid=11019(bandit19) euid=11020(bandit20) groups=11020(bandit20),11019(bandit19)
```

Maybe this will help us to display the content of ```/etc/bandit_pass/bandit20``` in order to get the next level's password:

```
bandit19@bandit:~$ ls -al /etc/bandit_pass/bandit20
-r-------- 1 bandit20 bandit20 33 Sep 28 14:03 /etc/bandit_pass/bandit20
```

The file ```/etc/bandit_pass/bandit20``` is only readable by user ```bandit20``` and/or any member of the group ```bandit20```. 
So maybe the setuid binary can help us:

```
bandit19@bandit:~$ ./bandit20-do cat /etc/bandit_pass/bandit20
GbKksEFF4yrVs6il55v6gwY5aVje5f0j
```
