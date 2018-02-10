Bandit Level 10 → Level 11
==========================

Level Goal
----------

The password for the next level is stored in the file data.txt, which contains base64 encoded data

Commands you may need to solve this level
-----------------------------------------

grep, sort, uniq, strings, base64, tr, tar, gzip, bzip2, xxd

Helpful Reading Material
------------------------

[Base64 on Wikipedia](http://en.wikipedia.org/wiki/Base64)

Solution
========

As described in the text, the content of file "data.txt" is base64 encoded. If the text wouldn't have given us this hint, we could have recognized it on our own because the string inside of data.txt ends with "==".
The link to Wikipedia's article about base64 gives us an explaination why. 
Please read the article carefully because you will very often have to deal with base64 encoded stuff during CTFs and/or wargame challenges.

```
bandit10@bandit:~$ cat data.txt
VGhlIHBhc3N3b3JkIGlzIElGdWt3S0dzRlc4TU9xM0lSRnFyeEUxaHhUTkViVVBSCg==
```

Nevertheless, since the text already told us that the file is base64 encoded, we simply have to decode it in order to get the human-readable password:

```
bandit10@bandit:~$ base64 -d data.txt
The password is IFukwKGsFW8MOq3IRFqrxE1hxTNEbUPR
```
