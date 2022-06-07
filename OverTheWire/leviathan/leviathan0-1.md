Leviathan Level 0 → Level 1
===========================

Level Goal
----------

There is no information for this level, intentionally.


Solution
========

There's no hint text or anything else for this level. So let's look around what we can find in the home directory:

```
leviathan0@leviathan:~$ ls -al
total 24
drwxr-xr-x  3 root       root       4096 Aug 26  2019 .
drwxr-xr-x 10 root       root       4096 Aug 26  2019 ..
drwxr-x---  2 leviathan1 leviathan0 4096 Aug 26  2019 .backup
-rw-r--r--  1 root       root        220 May 15  2017 .bash_logout
-rw-r--r--  1 root       root       3526 May 15  2017 .bashrc
-rw-r--r--  1 root       root        675 May 15  2017 .profile
```

The sub directory **.backup** looks promising because it's owned by next level's user **leviathan1**. So let's jump into this directory and see what't inside:

```
leviathan0@leviathan:~$ cd .backup/
leviathan0@leviathan:~/.backup$ ls -al
total 140
drwxr-x--- 2 leviathan1 leviathan0   4096 Aug 26  2019 .
drwxr-xr-x 3 root       root         4096 Aug 26  2019 ..
-rw-r----- 1 leviathan1 leviathan0 133259 Aug 26  2019 bookmarks.html
```

Since we are looking for the password of levianth1, let's check if it's inside of this pretty long text file:
 
```
leviathan0@leviathan:~/.backup$ grep "password" bookmarks.html
<DT><A HREF="http://leviathan.labs.overthewire.org/passwordus.html | This will be fixed later, the password for leviathan1 is rioGegei8m" ADD_DATE="1155384634" LAST_CHARSET="ISO-8859-1" ID="rdf:#$2wIU71">password to leviathan1</A>
```

That was easy :-)
