Krypton Level 0 → Level 1
=========================

Level Info
----------
The password for level 2 is in the file ‘krypton2’. It is ‘encrypted’ using a simple rotation. It is also in non-standard ciphertext format. When using alpha characters for cipher text it is normal to group the letters into 5 letter clusters, regardless of word boundaries. This helps obfuscate any patterns. This file has kept the plain text word boundaries and carried them to the cipher text. Enjoy!

Solution
========

Again, this one's pretty easy. As the Level Info tells us, the password is in the file /krypton/krypton2 which is encrypted using ROT13.
In order to decrypt the file, we simply have to encrypt it using [ROT13](https://en.wikipedia.org/wiki/ROT13) once again:
```
krypton1@krypton:~$ cat /krypton/krypton1/krypton2 | tr 'A-Za-z' 'N-ZA-Mn-za-m'
LEVEL TWO PASSWORD ROTTEN
```

```
krypton1@krypton:~$ python -c 'print "YRIRY GJB CNFFJBEQ EBGGRA".decode(encoding="ROT13")'
LEVEL TWO PASSWORD ROTTEN
```
