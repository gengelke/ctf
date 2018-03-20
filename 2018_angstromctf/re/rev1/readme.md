re, 60

One of the commmon categories in CTFs is Reverse Engineering, which involves using a dissassembler and other tools to figure out how an executable file works. For your first real reversing challenge, here is an ELF file. Head over to /problems/rev1/ on the shell server to try it out, and once you have the input right, get the flag!


team332540@shell:/problems/run_me$ cd /problems/rev1
```
strings rev1_32
[...]
[^_]
Welcome to your first Reverse Engineering challenge!
What is the password to this file? Enter password here:
s3cret_pa55word
Sorry, the password isn't %s. Try again!
Correct! You read my mind, have a flag:
/bin/cat flag
;*2$"(
GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609
crtstuff.c
[...]
```
team332540@shell:/problems/rev1$ ./rev1_32
Welcome to your first Reverse Engineering challenge!
What is the password to this file? Enter password here: s3cret_pa55word
Correct! You read my mind, have a flag:
actf{r3v_is_just_gettin_started!}
