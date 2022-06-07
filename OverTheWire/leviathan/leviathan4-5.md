Leviathan Level 4 → Level 5
===========================

Level Goal
----------

There is no information for this level, intentionally.

Solution
========

There's no hint text or anything else for this level. So let's look around what we can find in the home directory:

```
leviathan4@leviathan:~$ ls -al
total 24
drwxr-xr-x  3 root root       4096 Aug 26  2019 .
drwxr-xr-x 10 root root       4096 Aug 26  2019 ..
-rw-r--r--  1 root root        220 May 15  2017 .bash_logout
-rw-r--r--  1 root root       3526 May 15  2017 .bashrc
-rw-r--r--  1 root root        675 May 15  2017 .profile
dr-xr-x---  2 root leviathan4 4096 Aug 26  2019 .trash

leviathan4@leviathan:~$ cd .trash/

leviathan4@leviathan:~/.trash$ ls -al
total 16
dr-xr-x--- 2 root       leviathan4 4096 Aug 26  2019 .
drwxr-xr-x 3 root       root       4096 Aug 26  2019 ..
-r-sr-x--- 1 leviathan5 leviathan4 7352 Aug 26  2019 bin
```

```
leviathan4@leviathan:~/.trash$ ./bin
01010100 01101001 01110100 01101000 00110100 01100011 01101111 01101011 01100101 01101001 00001010
```

So this time the binary file prints out a binary code. All we have to do is to convert the binary value to ASCII in order to get a human readable password.
Copy the following code into a new file named /tmp/n3lke/convert.py:

```
import sys
import binascii

for binary in sys.stdin:
    binary = binary.replace(' ', '')
    ascii  = binascii.unhexlify('%x' % int(binary, 2))
    print "\nBinary: " + binary + "ASCII:  " + ascii
```

And finally grab the password for the next level! :-)
```
leviathan4@leviathan:~/.trash$ ./bin | python /tmp/n3lke/convert.py

Binary: 0101010001101001011101000110100000110100011000110110111101101011011001010110100100001010
ASCII:  Tith4cokei
```
