Bandit Level 22 → Level 23
==========================

Level Goal
----------

A program is running automatically at regular intervals from cron, the time-based job scheduler. Look in /etc/cron.d/ for the configuration and see what command is being executed.

NOTE: Looking at shell scripts written by other people is a very useful skill. The script for this level is intentionally made easy to read. If you are having problems understanding what it does, try executing it to see the debug information it prints.

Commands you may need to solve this level
-----------------------------------------

cron, crontab, crontab(5) (use “man 5 crontab” to access this)


Solution
========

First of all we gather the scripts path:

```
bandit22@bandit:~$ cat /etc/cron.d/cronjob_bandit23
@reboot bandit23 /usr/bin/cronjob_bandit23.sh  &> /dev/null
* * * * * bandit23 /usr/bin/cronjob_bandit23.sh  &> /dev/null
```

And then display it's content:

```
bandit22@bandit:~$ cat /usr/bin/cronjob_bandit23.sh
#!/bin/bash

myname=$(whoami)
mytarget=$(echo I am user $myname | md5sum | cut -d ' ' -f 1)

echo "Copying passwordfile /etc/bandit_pass/$myname to /tmp/$mytarget"

cat /etc/bandit_pass/$myname > /tmp/$mytarget
```

That's relatively easy once again at least if you are familiar with reading shell scrpts.
All we have to do is to generate the filename which contains the next level's password. That's done through ```mytarget=$(echo I am user $myname | md5sum | cut -d ' ' -f 1)```. By claiming that we are user ```bandit23``` while we rather are user ```bandit22```, we generate a string that servers as input for ```md5sum```. The md5 encoded string is then used as filename of the password file that is created by the cronjob every minute:

```
bandit22@bandit:~$ whoami
bandit22
bandit22@bandit:~$ echo "I am user bandit23" | md5sum | cut -d ' ' -f 1
8ca319486bfbbc3663ea0fbe81326349
```
```
bandit22@bandit:~$ cat /tmp/8ca319486bfbbc3663ea0fbe81326349
jc1udXuA1tiHqjIsL8yaapX5XIAI6i0n
```
