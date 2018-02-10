
Bandit Level 0 → Level 1
========================

Level Goal
----------

The password for the next level is stored in a file called readme located in the home directory. Use this password to log into bandit1 using SSH. Whenever you find a password for a level, use SSH (on port 2220) to log into that level and continue the game.

Commands you may need to solve this level
-----------------------------------------

ls, cd, cat, file, du, find


Solution
========

After successful login to the bandit0 account, we poke around a little bit in order to look for something that might help us to get the credentials for the next level.
The Text tells us, that there's a file named "readme" which contains the password for next level's account bandit1. 
Furthermore it tells us some possibly usefull commands which might help us to find the file. So let's see what's inside of the home directory:

```
bandit0@bandit:~$ ls -al
total 28
drwxr-xr-x  3 bandit0 bandit0 4096 Oct 25 19:26 .
drwxr-xr-x 30 root    root    4096 Oct 25 19:26 ..
-rw-r--r--  1 bandit0 bandit0  220 Apr  9  2014 .bash_logout
-rw-r--r--  1 bandit0 bandit0 3637 Apr  9  2014 .bashrc
drwx------  2 bandit0 bandit0 4096 Oct 25 19:26 .cache
-rw-r--r--  1 bandit0 bandit0  675 Apr  9  2014 .profile
-rw-r-----  1 bandit1 bandit0   33 Sep 28 14:04 readme
```

The filename "readme" sounds interesting. Let's find out what type of file "readme" is:

```
bandit0@bandit:~$ file readme
readme: ASCII text
```

Since it's a plain ASCII text file, we can simply display its content:

```
bandit0@bandit:~$ cat readme
boJ9jbbUNNfktd78OOpsqOltutMc3MY1
```

This could be a password. So we log out from the current SSH session and try to login as next level's user "bandit1" with password "boJ9jbbUNNfktd78OOpsqOltutMc3MY1":

```
d0n@netpest ~ $ exit
d0n@netpest ~ $ ssh bandit1@bandit.labs.overthewire.org -p 2220
 _                     _ _ _
| |__   __ _ _ __   __| (_) |_
| '_ \ / _` | '_ \ / _` | | __|
| |_) | (_| | | | | (_| | | |_
|_.__/ \__,_|_| |_|\__,_|_|\__|

a http://www.overthewire.org wargame.

bandit1@bandit.labs.overthewire.org's password:
Welcome to Ubuntu 14.04 LTS (GNU/Linux 4.4.0-92-generic x86_64)

 * Documentation:  https://help.ubuntu.com/

The programs included with the Ubuntu system are free software;
the exact distribution terms for each program are described in the
individual files in /usr/share/doc/*/copyright.

Ubuntu comes with ABSOLUTELY NO WARRANTY, to the extent permitted by
applicable law.

bandit1@bandit:~$
```

That's it. We're in! :-)
