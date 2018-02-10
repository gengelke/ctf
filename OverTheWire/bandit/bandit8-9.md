Bandit Level 8 → Level 9
========================

Level Goal
----------

The password for the next level is stored in the file data.txt and is the only line of text that occurs only once

Commands you may need to solve this level
-----------------------------------------

grep, sort, uniq, strings, base64, tr, tar, gzip, bzip2, xxd

Helpful Reading Material
------------------------

[The unix commandline: pipes and redirects](http://www.westwind.com/reference/os-x/commandline/pipes.html)


Solution
========
```
bandit8@bandit:~$ cat data.txt | sort
[...]
xBzuRR0vEg07m0j5DUywU8VgPKA0faZI
xBzuRR0vEg07m0j5DUywU8VgPKA0faZI
xBzuRR0vEg07m0j5DUywU8VgPKA0faZI
xBzuRR0vEg07m0j5DUywU8VgPKA0faZI
xBzuRR0vEg07m0j5DUywU8VgPKA0faZI
xBzuRR0vEg07m0j5DUywU8VgPKA0faZI
xBzuRR0vEg07m0j5DUywU8VgPKA0faZI
xBzuRR0vEg07m0j5DUywU8VgPKA0faZI
xBzuRR0vEg07m0j5DUywU8VgPKA0faZI
xBzuRR0vEg07m0j5DUywU8VgPKA0faZI
xg4dS7lEFqXKmT4CWuoRtNAPIu556bmS
xg4dS7lEFqXKmT4CWuoRtNAPIu556bmS
xg4dS7lEFqXKmT4CWuoRtNAPIu556bmS
xg4dS7lEFqXKmT4CWuoRtNAPIu556bmS
xg4dS7lEFqXKmT4CWuoRtNAPIu556bmS
xg4dS7lEFqXKmT4CWuoRtNAPIu556bmS
xg4dS7lEFqXKmT4CWuoRtNAPIu556bmS
xg4dS7lEFqXKmT4CWuoRtNAPIu556bmS
xg4dS7lEFqXKmT4CWuoRtNAPIu556bmS
xg4dS7lEFqXKmT4CWuoRtNAPIu556bmS
yLFRVdVJ2AA8PGGcLaRXDaN49qlV4tPd
yLFRVdVJ2AA8PGGcLaRXDaN49qlV4tPd
yLFRVdVJ2AA8PGGcLaRXDaN49qlV4tPd
yLFRVdVJ2AA8PGGcLaRXDaN49qlV4tPd
yLFRVdVJ2AA8PGGcLaRXDaN49qlV4tPd
yLFRVdVJ2AA8PGGcLaRXDaN49qlV4tPd
yLFRVdVJ2AA8PGGcLaRXDaN49qlV4tPd
yLFRVdVJ2AA8PGGcLaRXDaN49qlV4tPd
yLFRVdVJ2AA8PGGcLaRXDaN49qlV4tPd
yLFRVdVJ2AA8PGGcLaRXDaN49qlV4tPd
```

```
TkgZWX6C1tqbn8tcdWg59CgeCj6G6GdM
TkgZWX6C1tqbn8tcdWg59CgeCj6G6GdM
TkgZWX6C1tqbn8tcdWg59CgeCj6G6GdM
TkgZWX6C1tqbn8tcdWg59CgeCj6G6GdM
UHCeBxlhQZUh266IDMQWYinseYUWQlQN
UHCeBxlhQZUh266IDMQWYinseYUWQlQN
UHCeBxlhQZUh266IDMQWYinseYUWQlQN
UHCeBxlhQZUh266IDMQWYinseYUWQlQN
UHCeBxlhQZUh266IDMQWYinseYUWQlQN
UHCeBxlhQZUh266IDMQWYinseYUWQlQN
UHCeBxlhQZUh266IDMQWYinseYUWQlQN
UHCeBxlhQZUh266IDMQWYinseYUWQlQN
UHCeBxlhQZUh266IDMQWYinseYUWQlQN
UHCeBxlhQZUh266IDMQWYinseYUWQlQN
UsvVyFSfZZWbi6wgC7dAFyFuR6jQQUhR    <====
UtFrSsji99J6qGOE9l12hnOrc8Xjj69g
UtFrSsji99J6qGOE9l12hnOrc8Xjj69g
UtFrSsji99J6qGOE9l12hnOrc8Xjj69g
UtFrSsji99J6qGOE9l12hnOrc8Xjj69g
UtFrSsji99J6qGOE9l12hnOrc8Xjj69g
UtFrSsji99J6qGOE9l12hnOrc8Xjj69g
UtFrSsji99J6qGOE9l12hnOrc8Xjj69g
UtFrSsji99J6qGOE9l12hnOrc8Xjj69g
UtFrSsji99J6qGOE9l12hnOrc8Xjj69g
UtFrSsji99J6qGOE9l12hnOrc8Xjj69g
VczmfEroPT25d76xyUxr26uXe1XO2xj5
VczmfEroPT25d76xyUxr26uXe1XO2xj5
VczmfEroPT25d76xyUxr26uXe1XO2xj5
VczmfEroPT25d76xyUxr26uXe1XO2xj5
```

UsvVyFSfZZWbi6wgC7dAFyFuR6jQQUhR



```
#!/bin/bash

sorted=`cat data.txt | sort`
previous_line=''

while read -r line; do
#  echo "... $line ..."
if [ "$previous_line" == "$line" ]; then
 echo "double"
fi
 previous_line=$line
  grep -o '$line' <<< $sorted #| wc -l
done <<< "$sorted"
```
