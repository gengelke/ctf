Bandit Level 18 → Level 19
==========================

Level Goal
----------

The password for the next level is stored in a file readme in the homedirectory. Unfortunately, someone has modified .bashrc to log you out when you log in with SSH.

Commands you may need to solve this level
-----------------------------------------

ssh, ls, cat


Solution
========

We just have to let the ssh command execute 'cat readme' for us before we get thrown out of the ssh session:

```
gengelke@genmac ~ $ ssh bandit18@bandit.labs.overthewire.org -p 2220 cat readme
 _                     _ _ _
| |__   __ _ _ __   __| (_) |_
| '_ \ / _` | '_ \ / _` | | __|
| |_) | (_| | | | | (_| | | |_
|_.__/ \__,_|_| |_|\__,_|_|\__|

a http://www.overthewire.org wargame.

bandit18@bandit.labs.overthewire.org's password:
IueksS7Ubh8G3DCwVzrTd8rAVOwq3M5x
```
