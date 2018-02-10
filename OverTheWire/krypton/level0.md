Krypton Level 0
===============

Level Info
----------
Welcome to Krypton! The first level is easy. The following string encodes the password using Base64:

S1JZUFRPTklTR1JFQVQ=

Use this password to log in to krypton.labs.overthewire.org with username krypton1 using SSH on port 2222. You can find the files for other levels in /krypton/

Solution
========

This one's pretty easy. Everything we need to do is decode the Base64 encoded password mentioned in the Level Info.

```
d0n@netpest ~ $ echo "S1JZUFRPTklTR1JFQVQ=" | base64 -D
KRYPTONISGREATd0n@netpest ~ $ 
```
```
d0n@netpest ~ $ echo `echo "S1JZUFRPTklTR1JFQVQ=" | base64 -D`
KRYPTONISGREAT
```

Now we can log on to level 0 of Krypton:

```
d0n@netpest ~ $ ssh krypton1@krypton.labs.overthewire.org -p 2222
 _                     _
| | ___ __ _   _ _ __ | |_ ___  _ __
| |/ / '__| | | | '_ \| __/ _ \| '_ \
|   <| |  | |_| | |_) | || (_) | | | |
|_|\_\_|   \__, | .__/ \__\___/|_| |_|
           |___/|_|
a http://www.overthewire.org wargame.

krypton1@krypton.labs.overthewire.org's password:
X11 forwarding request failed on channel 0
Welcome to Ubuntu 14.04 LTS (GNU/Linux 4.4.0-92-generic x86_64)

 * Documentation:  https://help.ubuntu.com/

The programs included with the Ubuntu system are free software;
the exact distribution terms for each program are described in the
individual files in /usr/share/doc/*/copyright.

Ubuntu comes with ABSOLUTELY NO WARRANTY, to the extent permitted by
applicable law.

krypton1@krypton:~$
```
