Bandit Level 25 → Level 26
==========================

Level Goal
----------

Logging in to bandit26 from bandit25 should be fairly easy… The shell for user bandit26 is not /bin/bash, but something else. Find out what it is, how it works and how to break out of it.

Commands you may need to solve this level
-----------------------------------------

ssh, cat, more, vi, ls, id, pwd


Solution
========

Once again there's an SSH private key file in the user's home directory:

```
bandit25@bandit:~$ cat bandit26.sshkey
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEApis2AuoooEqeYWamtwX2k5z9uU1Afl2F8VyXQqbv/LTrIwdW
pTfaeRHXzr0Y0a5Oe3GB/+W2+PReif+bPZlzTY1XFwpk+DiHk1kmL0moEW8HJuT9
/5XbnpjSzn0eEAfFax2OcopjrzVqdBJQerkj0puv3UXY07AskgkyD5XepwGAlJOG
xZsMq1oZqQ0W29aBtfykuGie2bxroRjuAPrYM4o3MMmtlNE5fC4G9Ihq0eq73MDi
1ze6d2jIGce873qxn308BA2qhRPJNEbnPev5gI+5tU+UxebW8KLbk0EhoXB953Ix
3lgOIrT9Y6skRjsMSFmC6WN/O7ovu8QzGqxdywIDAQABAoIBAAaXoETtVT9GtpHW
qLaKHgYtLEO1tOFOhInWyolyZgL4inuRRva3CIvVEWK6TcnDyIlNL4MfcerehwGi
il4fQFvLR7E6UFcopvhJiSJHIcvPQ9FfNFR3dYcNOQ/IFvE73bEqMwSISPwiel6w
e1DjF3C7jHaS1s9PJfWFN982aublL/yLbJP+ou3ifdljS7QzjWZA8NRiMwmBGPIh
Yq8weR3jIVQl3ndEYxO7Cr/wXXebZwlP6CPZb67rBy0jg+366mxQbDZIwZYEaUME
zY5izFclr/kKj4s7NTRkC76Yx+rTNP5+BX+JT+rgz5aoQq8ghMw43NYwxjXym/MX
c8X8g0ECgYEA1crBUAR1gSkM+5mGjjoFLJKrFP+IhUHFh25qGI4Dcxxh1f3M53le
wF1rkp5SJnHRFm9IW3gM1JoF0PQxI5aXHRGHphwPeKnsQ/xQBRWCeYpqTme9amJV
tD3aDHkpIhYxkNxqol5gDCAt6tdFSxqPaNfdfsfaAOXiKGrQESUjIBcCgYEAxvmI
2ROJsBXaiM4Iyg9hUpjZIn8TW2UlH76pojFG6/KBd1NcnW3fu0ZUU790wAu7QbbU
i7pieeqCqSYcZsmkhnOvbdx54A6NNCR2btc+si6pDOe1jdsGdXISDRHFb9QxjZCj
6xzWMNvb5n1yUb9w9nfN1PZzATfUsOV+Fy8CbG0CgYEAifkTLwfhqZyLk2huTSWm
pzB0ltWfDpj22MNqVzR3h3d+sHLeJVjPzIe9396rF8KGdNsWsGlWpnJMZKDjgZsz
JQBmMc6UMYRARVP1dIKANN4eY0FSHfEebHcqXLho0mXOUTXe37DWfZza5V9Oify3
JquBd8uUptW1Ue41H4t/ErsCgYEArc5FYtF1QXIlfcDz3oUGz16itUZpgzlb71nd
1cbTm8EupCwWR5I1j+IEQU+JTUQyI1nwWcnKwZI+5kBbKNJUu/mLsRyY/UXYxEZh
ibrNklm94373kV1US/0DlZUDcQba7jz9Yp/C3dT/RlwoIw5mP3UxQCizFspNKOSe
euPeaxUCgYEAntklXwBbokgdDup/u/3ms5Lb/bm22zDOCg2HrlWQCqKEkWkAO6R5
/Wwyqhp/wTl8VXjxWo+W+DmewGdPHGQQ5fFdqgpuQpGUq24YZS8m66v5ANBwd76t
IZdtF5HXs2S5CADTwniUS5mX1HO9l5gUkk+h0cH5JnPtsMCnAUM+BRY=
-----END RSA PRIVATE KEY-----
```

When we use this to SSH into the bandit26 account, it works but immediately closes the connection after displaying a bunch of information of an ```motd``` file found in ```/run/motd.dynamic```.

```
bandit25@bandit:~$ ssh -i bandit26.sshkey bandit26@localhost -p 2220
[...]

  _                     _ _ _   ___   __
 | |                   | (_) | |__ \ / /
 | |__   __ _ _ __   __| |_| |_   ) / /_
 | '_ \ / _` | '_ \ / _` | | __| / / '_ \
 | |_) | (_| | | | | (_| | | |_ / /| (_) |
 |_.__/ \__,_|_| |_|\__,_|_|\__|____\___/
Connection to localhost closed.
bandit25@bandit:~$
```

If we try to let the same SSH command execute ```ls``` it never comes back but continues to read from stdin forever.

```
bandit25@bandit:~$ ssh -i bandit26.sshkey bandit26@localhost -p 2220 ls
 _                     _ _ _
| |__   __ _ _ __   __| (_) |_
| '_ \ / _` | '_ \ / _` | | __|
| |_) | (_| | | | | (_| | | |_
|_.__/ \__,_|_| |_|\__,_|_|\__|

a http://www.overthewire.org wargame.

bla
ls
hello
[...]
```

Let's try to pipe something into the ssh command instead of using stdin:

```
bandit25@bandit:~$ echo "ls" | ssh -i bandit26.sshkey bandit26@localhost
Pseudo-terminal will not be allocated because stdin is not a terminal.
 _                     _ _ _
| |__   __ _ _ __   __| (_) |_
| '_ \ / _` | '_ \ / _` | | __|
| |_) | (_| | | | | (_| | | |_
|_.__/ \__,_|_| |_|\__,_|_|\__|

a http://www.overthewire.org wargame.
[...]

ls
::::::::::::::
/home/bandit26/text.txt
::::::::::::::
  _                     _ _ _   ___   __
 | |                   | (_) | |__ \ / /
 | |__   __ _ _ __   __| |_| |_   ) / /_
 | '_ \ / _` | '_ \ / _` | | __| / / '_ \
 | |_) | (_| | | | | (_| | | |_ / /| (_) |
 |_.__/ \__,_|_| |_|\__,_|_|\__|____\___/
```

Hmmm, now the ```motd``` differs from the previous runs. First of all it says ```Pseudo-terminal will not be allocated because stdin is not a terminal.```. Secondly it displays a text box with ```/home/bandit26/text.txt``` in it.
Could this be a hint?

```
bandit25@bandit:~$ cat /home/bandit26/text.txt
cat: /home/bandit26/text.txt: Permission denied
```
```
bandit25@bandit:~$ ls -al /home/bandit26/text.txt
-rw-r----- 1 bandit26 bandit26 258 Sep 28 14:04 /home/bandit26/text.txt
```
```
echo "cat /home/bandit26/text.txt" | ssh -i bandit26.sshkey bandit26@localhost
```
```
echo "cat /etc/bandit_pass/bandit26" | ssh -i bandit26.sshkey bandit26@localhost
```

Well, nice observations but obviously this doesn't give us the password.
Return to beginning...

The Level Goal text tells us to consider to use the tools ```ssh```, ```cat```, ```more```, ```vi```, ```ls```, ```id``` and/or ```pwd```. I remembered that I solved another PullThePlug wargame challenge in the past which seemed to be similar to this one because the text says ```The shell for user bandit26 is not /bin/bash, but something else.```. So I wondered if it could have something to do with ```more``` (or ```less```?).

So let's see what the [command/shell field](https://www.cyberciti.biz/faq/understanding-etcpasswd-file-format/) for user bandit26 is within ```/etc/passwd```:

```
bandit25@bandit:~$ cat /etc/passwd | grep bandit26
bandit26:x:11026:11026:bandit level 26:/home/bandit26:/usr/bin/showtext
```

And then take a look into ```/usr/bin/showtext```:

```
bandit25@bandit:~$ cat /usr/bin/showtext
#!/bin/sh

export TERM=linux

more ~/text.txt
exit 0
```

Now we know for sure that ```more``` is used for displaying the motd -like text. I took a quick look into more's man page in order to find anything helpful and got this:

```
bandit25@bandit:~$ man more
[...]
     !<cmd> or :!<cmd>
                 Execute <cmd> in a subshell
[...]                 
```

I did several tries with ```!ls``` and ```:!ls``` either by typing it to stdin or piping it into the SSH command. But none of these tries worked either. At this point I didn't know how to proceed so I decided to ask for a hint on irc.overthewire.org:

```
[13:43:32]  <Guest99>	yeah, i thought that it might have smething to do with more
[13:43:39]  <martin>	well, not a bad start
[13:43:56]  <Guest99>	because i remember a similar challenge some years ago with pulltheplug
[13:44:03]  <martin>	so if it is more, or more-related that means you won't be able to do echo cmd | ssh .. 
[13:44:30]  <Guest99>	so i tried to do !ls :!ls and several variations with cat to the password files but nothing worked so far
[13:44:49]  <martin>	that's also good
[13:45:07]  <martin>	so you have the basic idea what has to be done, which is more-less (no pwn intended) true
[13:45:43]  <martin>	as hint i'd say - think when pager is triggered when you do cat, etc. in terminal
[13:45:53]  <martin>	and find a way to make it happen there
[13:47:12]  <martin>	env variable
```

Now I knew that I'm on the right track but still didn't have a clue how to proceed. I read the hint text again and again and thought about ```env variable``` and ```think when pager is triggered when you do cat, etc. in terminal```.

I decided to take a look into more's man page once again and found this:

```
[...]
ENVIRONMENT
     More utilizes the following environment variables, if they exist:

     MORE        This variable may be set with favored options to more.

     SHELL       Current shell in use (normally set by the shell at login time).

     TERM        Specifies terminal type, used by more to get the terminal characteristics necessary to manipulate
                 the screen.
[...]
```

I did several experiments with trying to transfer environment variables to the remote more command using ```$MORE``` and ```-o SendEnv=``` and whatever without any luck. Therefore I decided to ask for a hint once again. And someone told me that me approach to enter commands withion the more session was correct but I did it wrong. Because for some reason in my terminal session the whole motd-like text was printed at once without using more's intended *paging capabilities*. So another hint was to resize the terminal window before starting the SSH connection. 
Damn, what a nightmare... For sure I was on the right track with my previous steps but I missed one significant thing:
```more``` only uses it's paging capabilities if the text it should display is longer than one screen/terminal page. And that wasn't the case because all this motd-like output wasn't part of what ```more``` has displayed but was displayed by the SSH server's banner functionality. We recall the code of ``/usr/bin/showtext``` which is set as login shell for the user bandit26 within ```/etc/passwd```:

```
bandit25@bandit:~$ cat /usr/bin/showtext
#!/bin/sh

export TERM=linux

more ~/text.txt
exit 0
```

There we can see in cold print that ```more``` only displays the file ```~/text.txt``` which obviously only contains the following part:

```
  _                     _ _ _   ___   __
 | |                   | (_) | |__ \ / /
 | |__   __ _ _ __   __| |_| |_   ) / /_
 | '_ \ / _` | '_ \ / _` | | __| / / '_ \
 | |_) | (_| | | | | (_| | | |_ / /| (_) |
 |_.__/ \__,_|_| |_|\__,_|_|\__|____\___/
```

And this for sure isn't enough text in order to let ```more``` do any paging. To put it in a nutshell, I shrinked the terminal window to a minimum of three lines (or whatever is smaller than the *bandit26* logo) and executed the already well known SSH command line once again:

```
+----------------------------------------------------------------+
| x - +                                                          |
+----------------------------------------------------------------+
|bandit25@bandit:~$ ssh -i bandit26.sshkey bandit26@localhost    |
|                                                                |
|                                                                |
+----------------------------------------------------------------+
```

This time I made ```more``` to display each individual page separately indicated by ```---More---(33%)```:

```
+----------------------------------------------------------------+
| x - +                                                          |
+----------------------------------------------------------------+
|  _                     _ _ _   ___   __                        |
| | |                   | (_) | |__ \ / /                        |
|--More--(33%)                                                   |
+----------------------------------------------------------------+
```
Damn, that's what the OTW admin told me when I asked for a hint...

```
[13:45:43]  <martin>	as hint i'd say - think when pager is triggered when you do cat, etc. in terminal
[13:45:53]  <martin>	and find a way to make it happen there
```
What the hell! ;-)

Then I resized the terminal window back to its original size and once again tried to execute commands from within ```more``` as described in the man page and mentioned before. But this wasn't successful again. All attempts to enter any combination of ```!<cmd>``` or ```:!<cmd>``` failed and didn't execute any command but just displayed the already known banner message again and again =(

From within the SSH/more session I pressed th ```?``` key in order to get some additional help and got this:

```
Most commands optionally preceded by integer argument k.  Defaults in brackets.
Star (*) indicates argument becomes new default.
-------------------------------------------------------------------------------
<space>                 Display next k lines of text [current screen size]
z                       Display next k lines of text [current screen size]*
<return>                Display next k lines of text [1]*
d or ctrl-D             Scroll k lines [current scroll size, initially 11]*
q or Q or <interrupt>   Exit from more
s                       Skip forward k lines of text [1]
f                       Skip forward k screenfuls of text [1]
b or ctrl-B             Skip backwards k screenfuls of text [1]
'                       Go to place where previous search started
=                       Display current line number
/<regular expression>   Search for kth occurrence of regular expression [1]
n                       Search for kth occurrence of last r.e [1]
!<cmd> or :!<cmd>       Execute <cmd> in a subshell
v                       Start up /usr/bin/vi at current line
ctrl-L                  Redraw screen
:n                      Go to kth next file [1]
:p                      Go to kth previous file [1]
:f                      Display current file name and line number
.                       Repeat previous command
-------------------------------------------------------------------------------
```
Except for the ```!<cmd> or :!<cmd>``` line mostly every other command was scroll and/or display related but didn't give me a chance to get the password which I'm looking for...
Rather accidentally than knowingly I pressed the ```v``` key and ended in a VI(M) session which gave me the possibility to modify the file ```~/text.txt``` which initially was displayed by ```more```. To be honest I didn't want to do this but when I triggered the usual ```:wq``` command in order to get out of VI(M) I realized that the ```more``` process for sure is able to read/write access files which are owned by ```bandit26```. So I pressed ```v``` once again in order to get back to VI(M). Then from within the VI(M) session I did a ```:split /etc/bandit_pass/bandit26``` and finally got the password for Bandit level 26:

```
5czgV9L3Xx8JPOyRbXh6lQbmIOWvPT6Z
```

This level was indead a very educational but even more hair-raising challenge. I'm proud to have completed it but I honestly have to admit that without the hints I would never have solved this level! :-D
