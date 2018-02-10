Bandit Level 5 → Level 6
========================

Level Goal
----------

The password for the next level is stored in a file somewhere under the inhere directory and has all of the following properties:

    human-readable
    1033 bytes in size
    not executable

Commands you may need to solve this level
-----------------------------------------

ls, cd, cat, file, du, find


Solution
========

```
bandit5@bandit:~$ find inhere/ -size 1033c ! -executable
inhere/maybehere07/.file2
```

or

```
bandit5@bandit:~$ find inhere/ -size 1033c ! -executable -readable -exec file {} +
inhere/maybehere07/.file2: ASCII text, with very long lines
```

```
bandit5@bandit:~$ cat inhere/maybehere07/.file2
DXjZPULLxYr17uwoI01bNLQbtFemEgo7                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 bandit5@bandit:~$
```
