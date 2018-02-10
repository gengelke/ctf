Solution
========

Use Firefox to browse to the URL ```www.gracker.org``` and you'll get a simple web site which just displays the text ```the journey begins...```.
So we right click into the web page and choose ```View Page Source``` from the context menu. You'll get the following HTML source code:

```
<!doctype html>
<html>
<head></head>
<body>
<h1>the journey begins...</h1>
<?php echo "asd"; ?>
<!--
`ssh level0@gracker.org`
password: level0
--!>
</body>
</html>
```

It tells us that the password for level0 is ```level0```. So we SSH login to gracker.org with user ```level0``` and password ```level0```:

```
user@system ~ $ ssh level0@gracker.org
      __                  _
     / /                 | |
    / /_ _ _ __ __ _  ___| | _____ _ __
   / / _` | '__/ _` |/ __| |/ / _ \ '__|
  / / (_| | | | (_| | (__|   <  __/ |
 /_/ \__, |_|  \__,_|\___|_|\_\___|_|
      __/ |
     |___/
             ~ follow the white rabbit ~
                     ~ gracker ~
            ~ irc.hackint.org  #gracker ~
level0@gracker.org's password:
X11 forwarding request failed on channel 0
┌────────────────────┐
│ HACK THE PLANET!   │
└────────────────────┘
┌───────────────────────────────────────────────────────────────────────────┐
│ > if this is your first time, read the README: cat /home/level0/README <  │
├──────────────────────────────────────────────────────────────────────────┬┘
│ Quick Overview:                                                          │
│                                                                          │
│    - your goal is to get access to the next level                        │
│    - flags/passwords are in ~/.pass                                      │
│    - Admin: minichalls@smrrd.de                                          │
├──────────────────────────────────────────────────────────────────────────┤
│ Rules:                                                                   │
│                                                                          │
│    1. No DoS                                                             │
│    2. Don't connect to remote systems                                    │
│    3. Don't use too many resources                                       │
│    4. Do not spoil challenges in any way (no writeups!)                  │
├──────────────────────────────────────────────────────────────────────────┴┐
│ > if this is your first time, read the README: cat /home/level0/README <  │
└───────────────────────────────────────────────────────────────────────────┘
┌────────────────────────────────────┐ ┌───────────────────────────────────┐
│ Linux Commands Examples...         │ │ Show the content of a file:       │
│                                    │ │    `cat ~/iwashere`               │
│ list directory contents:           │ │                                   │
│   `ls` `ls -la` `ls /home/level0`  │ │ Show the manual of a command:     │
│                                    │ │    `man                           │
│ show current directory:            │ │                                   │
│   `pwd`                            │ │ How to edit files on the console: │
│                                    │ │                                   │
│ change directory:                  │ │  execute the program `vimtutor`.  │
│   `cd` `cd /matrix/level0` `cd -`  │ │  It will teach you how to use the │
│                                    │ │  `vim` editor. Use arrow keys to  │
│ create a directory:                │ │  browse the document and read it. │
│   `mkdir /tmp/myfiles`             │ │                                   │
│                                    │ │ Don't forget to read the README...│
│ execute a file:                    │ │ and have fun!                     │
│   `id` `/usr/bin/id` `./level0`    │ │                                   │
├────────────────────────────────────┴─┴───────────────────────────────────┴┐
│         Questions, problems, or just want to hang out and chat?           │
│            IRC Server: irc.hackint.org    Channel: #gracker               │
│           https://kiwiirc.com/client/irc.hackint.org/gracker              │
└───────────────────────────────────────────────────────────────────────────┘
```

```
level0@gracker:~$ ls -al
total 44
drwxr-xr-x  2      0      0 4096 Jun 19  2015 .
drwxr-xr-x 16      0      0 4096 Jul  9  2015 ..
-rw-r-----  1 level0 level0 8192 Dec  3 17:36 iwashere
-r--r-----  1 level0 level0    7 Jun 19  2015 .pass
-r--r-----  1 level0 level0 8488 Jun 19  2015 README
-r--r-----  1 level0 level0 3468 Jun 19  2015 story
-r--r-----  1 level0 level0 4864 Jun 19  2015 welcome
```
```
level0@gracker:~$ cat story
┌────────────────────────────┐
│ Follow the white rabbit... │
└────────────────────────────┘

TL;DR: scroll down to the end of the article

Zero Cool has already compromised this system.  So follow his traces, hack
his lame backdoors  and teach him a lesson.  The admin of this system  has
  ┌────────────────────────┐   discovered  a  program that  seems to  be a
  │  _____                 │   backdoor from Zero Cool. He uses it to  get
  │ | _ _ |                │   access to level1.  You can find the program
  │ || | || Level1         │   in `ls -la /matrix/level0/`. If you look at
  │ ||_|_||   Backdoor     │   the  permissions  in  Figure  2,  you  will
  │ | _ _ o  by            │   notice that the  program belongs to level1.
  │ || | ||     ~Zero Cool │   But  the  group level0 (you)  has  also the
  │ ||_|_||                │   permissions to execute it and read it. Also
  │ |_____|                │   the  setuid (s) bit  is set  for the  user.
  │                        │   This means that if you execute it as level0
  │ Enter Secret Password: │   it will actually run with the privileges of
  └────────────────────────┘   level1. So  Zero Cool created  a  backdoor
  Figure 1.: Zero Cool's       program, that he can execute as level0, but
             backdoor          use it to get the privileges of level1.

Can  you  use  his  backdoor  to   ┌────────────────────────────────────┐
gain access  to level1?  You can   │-r-sr-x--- 1 level1 level0          │
execute the backdoor with:         │ └┬┘└┬┘└┬┘    │      └─▶ group      │
    `/matrix/level0/level0`        │  │  │  │     └─▶ user              │
Can you  find the password  that   │  │  │  └─▶ no rights for others    │
unlocks the  backdoor?  When you   │  │  └─▶  group can read and execute│
succeed, use  the  program  `id`   │  └─▶ user can read and execute     │
to check  if  you now  have  the   │       + setuid bit                 │
permissions of level1.             └────────────────────────────────────┘
Don't   forget   to   grab   the      Figure 2.: level0 file permissions
password  of level1,  so you can
use ssh to log into the next level: `cat /home/level1/level1/.pass`
`ssh level1@gracker.org`

NOTICE: supidly bruteforcing passwords is never the solution. If you don't
know how to proceed, come to IRC and ask for help. No spoilers in the main
channel though.

Useful tools for this level might be:
 ● `file` - determine file type
 ● `gdb` - gnu debugger (debug binaries)
 ● `strings` - print the strings of printable characters in files


TL;DR: A hacker kiddy named Zero Cool has a backdoor on this system.  Find
       the hidden backdoor password of `/matrix/level0/level0`.
```

So now we know that there's a backdoor located in file /matrix/level0/level0 which we have to use in order to gain the next level's password.
Unfortunately the backdoor asks us for a valid password which we don't know yet. But the hint text tells us to use the tools ```file```, ```gdb``` and ```strings``` to gather the password.
Therefore we use ```strings``` in order to see if we can display any human readable strings from the backdoor's binary which might look like a valid password:
```
level0@gracker:~$ strings /matrix/level0/level0
[...]
s3cr3t_backd00r_passw0rd
[...]
```
We finally use this password for the backdoor authentiction and get a shell which is executed with the user ID of level1, so we can get the next level's password:
```
level0@gracker:~$ /matrix/level0/level0
 _____
| _ _ |
|| | || Hidden
||_|_||   Backdoor
| _ _ o  by
|| | ||     ~Zero Cool
||_|_||
|_____|

Enter Secret Password:
s3cr3t_backd00r_passw0rd
Correct! Here is the level1 shell.
Read the level1 password in /home/level1/.pass to login with `ssh level1@gracker.org`
$ id
uid=1001(level1) gid=1000(level0) groups=1000(level0)
$ cat /home/level1/.pass
TVeB0MIlx0KB
```
```TVeB0MIlx0KB``` is the password for level1.
