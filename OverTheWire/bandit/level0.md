Bandit Level 0
==============

Level Goal
----------

The goal of this level is for you to log into the game using SSH. The host to which you need to connect is bandit.labs.overthewire.org, on port 2220. The username is bandit0 and the password is bandit0. Once logged in, go to the Level 1 page to find out how to beat Level 1.

Commands you may need to solve this level
-----------------------------------------

ssh

Helpful Reading Material
------------------------

[Secure Shell (SSH) on Wikipedia](https://en.wikipedia.org/wiki/Secure_Shell)

[How to use SSH on wikiHow](https://www.wikihow.com/Use-SSH)


Solution
========

As described in "Level Goal", we have to SSH connect to bandit.labs.overthewire.org on port 2220 with username bandit0 and password bandit0. That's pretty easy. If you're not that familiar with ssh, read the manpage and gather the required command line options. Here's how I did it:

```bash
d0n@netpest ~ $ ssh bandit0@bandit.labs.overthewire.org -p 2220
The authenticity of host '[bandit.labs.overthewire.org]:2220 ([176.9.9.172]:2220)' can't be established.
ECDSA key fingerprint is SHA256:SCySwNrZFEHArEX1cAlnnaJ5gz2O8VEigY9X80nFWUU.
Are you sure you want to continue connecting (yes/no)? yes
Warning: Permanently added '[bandit.labs.overthewire.org]:2220,[176.9.9.172]:2220' (ECDSA) to the list of known hosts.
 _                     _ _ _
| |__   __ _ _ __   __| (_) |_
| '_ \ / _` | '_ \ / _` | | __|
| |_) | (_| | | | | (_| | | |_
|_.__/ \__,_|_| |_|\__,_|_|\__|

a http://www.overthewire.org wargame.

bandit0@bandit.labs.overthewire.org's password:
Welcome to Ubuntu 14.04 LTS (GNU/Linux 4.4.0-92-generic x86_64)

 * Documentation:  https://help.ubuntu.com/

The programs included with the Ubuntu system are free software;
the exact distribution terms for each program are described in the
individual files in /usr/share/doc/*/copyright.

Ubuntu comes with ABSOLUTELY NO WARRANTY, to the extent permitted by
applicable law.

bandit0@bandit:~$
```

OK, we're in. Now let's read what the task is to change to level 1.
