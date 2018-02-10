Bandit Level 12 → Level 13
==========================

Level Goal
----------

The password for the next level is stored in the file data.txt, which is a hexdump of a file that has been repeatedly compressed. For this level it may be useful to create a directory under /tmp in which you can work using mkdir. For example: mkdir /tmp/myname123. Then copy the datafile using cp, and rename it using mv (read the manpages!)

Commands you may need to solve this level
-----------------------------------------

grep, sort, uniq, strings, base64, tr, tar, gzip, bzip2, xxd, mkdir, cp, mv

Helpful Reading Material
------------------------

[Hex dump on Wikipedia](http://en.wikipedia.org/wiki/Hex_dump)


Solution
========

First of all we have to change the hexdump back to the original binary file:

```
bandit12@bandit:~$ xxd -r data.txt data.bin
```

As decribed in the text, we get an archive file of type 'gzip':

```
bandit12@bandit:~$ file data.bin
data.bin: gzip compressed data, was "data2.bin", from Unix, last modified: Thu Sep 28 14:04:06 2017, max compression
```

So let's start the unpack orgy:

```
bandit12@bandit:~$ mv data.bin data.gz
bandit12@bandit:~$ gunzip data.gz
bandit12@bandit:~$ file data
data: bzip2 compressed data, block size = 900k
bandit12@bandit:~$ mv data data.bz
bandit12@bandit:~$ bunzip2 data.bz
bandit12@bandit:~$ file data
data: gzip compressed data, was "data4.bin", from Unix, last modified: Thu Sep 28 14:04:06 2017, max compression
bandit12@bandit:~$ mv data data.gz
bandit12@bandit:~$ gunzip data.gz
bandit12@bandit:~$ file data
data: POSIX tar archive (GNU)
bandit12@bandit:~$ mv data data.tar
bandit12@bandit:~$ tar -xvf data.tar
data5.bin
bandit12@bandit:~$ file data5.bin
data5.bin: POSIX tar archive (GNU)
bandit12@bandit:~$ mv data5.bin data5.tar
bandit12@bandit:~$ tar -xvf data.tar
data5.bin
bandit12@bandit:~$ file data5.bin
data5.bin: POSIX tar archive (GNU)
bandit12@bandit:~$ mv data5.bin data5.tar
bandit12@bandit:~$ tar -xvf data5.tar
data6.bin
bandit12@bandit:~$ file data6.bin
data6.bin: bzip2 compressed data, block size = 900k
bandit12@bandit:~$ mv data6.bin data6.bz
bandit12@bandit:~$ bunzip2 data6.bz
bandit12@bandit:~$ file data6
data6: POSIX tar archive (GNU)
bandit12@bandit:~$ mv data6 data6.tar
bandit12@bandit:~$ tar -xvf data6.tar
data8.bin
bandit12@bandit:~$ file data8.bin
data8.bin: gzip compressed data, was "data9.bin", from Unix, last modified: Thu Sep 28 14:04:06 2017, max compression
bandit12@bandit:~$ mv data8.bin data8.gz
bandit12@bandit:~$ gunzip data8.gz
bandit12@bandit:~$ file data8
data8: ASCII text
````

And finally we get the password:

```
bandit12@bandit:~$ cat data8
The password is 8ZjyCRiBWFYkneahHwxCv3wb2a1ORpYL
```
