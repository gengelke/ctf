Bandit Level 11 → Level 12
==========================

Level Goal
----------

The password for the next level is stored in the file data.txt, where all lowercase (a-z) and uppercase (A-Z) letters have been rotated by 13 positions

Commands you may need to solve this level
-----------------------------------------

grep, sort, uniq, strings, base64, tr, tar, gzip, bzip2, xxd

Helpful Reading Material
------------------------

[Rot13 on Wikipedia](http://en.wikipedia.org/wiki/Rot13)

Solution
========

The text gives us the hint that the content of file data.txt is encoded with the ROT13 algorithm. ROT13 is described in detail in the mentioned Wikipedia article.
Once again I strongly recommend to read and understand the article carefully because again you will have to deal with ROT13 encoded data in other CTF and/or wargame challenges relatively often.
Furthermore the article tells us how to decrypt the password:

```
bandit11@bandit:~$ cat data.txt | tr 'A-Za-z' 'N-ZA-Mn-za-m'
The password is 5Te8Y4drgCRfCx8ugdwuEX8KFC6k2EUu
```
