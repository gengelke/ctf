Connect to the system using SSH and password ```guest```:
```
user@system: ~ > ssh fd@pwnable.kr -p2222
fd@pwnable.kr's password:
```
Then you will see the some information about the game itself:
```
 ____  __    __  ____    ____  ____   _        ___      __  _  ____
|    \|  |__|  ||    \  /    ||    \ | |      /  _]    |  |/ ]|    \
|  o  )  |  |  ||  _  ||  o  ||  o  )| |     /  [_     |  ' / |  D  )
|   _/|  |  |  ||  |  ||     ||     || |___ |    _]    |    \ |    /
|  |  |  `  '  ||  |  ||  _  ||  O  ||     ||   [_  __ |     \|    \
|  |   \      / |  |  ||  |  ||     ||     ||     ||  ||  .  ||  .  \
|__|    \_/\_/  |__|__||__|__||_____||_____||_____||__||__|\_||__|\_|

- Site admin : daehee87@gatech.edu
- IRC : irc.netgarage.org:6667 / #pwnable.kr
- Simply type "irssi" command to join IRC now
- files under /tmp can be erased anytime. make your directory under /tmp
- to use peda, issue `source /usr/share/peda/peda.py` in gdb terminal
You have mail.
Last login: Sun Jul 11 13:48:52 2021 from 118.71.10.71
fd@pwnable:~$
```
Since there's not much information regarding the current level, let's take a look into the user's home folder:
```
fd@pwnable:~$ ls
fd  fd.c  flag
fd@pwnable:~$ ls -al
total 40
drwxr-x---   5 root   fd   4096 Oct 26  2016 .
drwxr-xr-x 115 root   root 4096 Dec 22  2020 ..
d---------   2 root   root 4096 Jun 12  2014 .bash_history
-r-sr-x---   1 fd_pwn fd   7322 Jun 11  2014 fd
-rw-r--r--   1 root   root  418 Jun 11  2014 fd.c
-r--r-----   1 fd_pwn root   50 Jun 11  2014 flag
-rw-------   1 root   root  128 Oct 26  2016 .gdb_history
dr-xr-xr-x   2 root   root 4096 Dec 19  2016 .irssi
drwxr-xr-x   2 root   root 4096 Oct 23  2016 .pwntools-cache
```
There are obviously three interesting files. The first one is named ```flag``` but which we can not read from because we don't have appropriate permissions:
```
fd@pwnable:~$ cat flag
cat: flag: Permission denied
```
The second is named ```fd``` and is a binary. Followed by ```fd.c``` which seems to be the C source code of the previously mentioned ```fd```binary: 
```
fd@pwnable:~$ cat fd.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char buf[32];
int main(int argc, char* argv[], char* envp[]){
	if(argc<2){
		printf("pass argv[1] a number\n");
		return 0;
	}
	int fd = atoi( argv[1] ) - 0x1234;
	int len = 0;
	len = read(fd, buf, 32);
	if(!strcmp("LETMEWIN\n", buf)){
		printf("good job :)\n");
		system("/bin/cat flag");
		exit(0);
	}
	printf("learn about Linux file IO\n");
	return 0;

}
``` 
We can see, that the code expects an argument when the program is called (```argv[1]```). The argument is then converted from ascii to integer and subtracted by the hexadezimal value ```0x1234```.
The resulting value is then used as the file descriptor for the ```read()``` function in order to read 32 Bytes from the given file descriptor into buffer ```buf```.
The previously read content of ```buf``` is then compared with the string ```LETMEWIN\n```. If the comparison is true, the ```fd``` binary will print the contents of the file named ```flag```.
Otherwise it just says ```learn about Linux file IO```. So in order to solve this level, we have to find out what's the correct program argument we would have to give in order to get the flag.

Since there is no ```open()``` in the given source code, the value of ```fd``` can only be one of the default [Linux/Unix file descriptors](https://en.wikipedia.org/wiki/File_descriptor):
```
0	  Standard input	  STDIN_FILENO	  stdin
1	  Standard output	  STDOUT_FILENO	  stdout
2	  Standard error          STDERR_FILENO	  stderr
```
```stdout``` and ```stderr``` are used for the output of a program. Therefore it's more likely that we would have to use the file descriptor 0 (```stdin```) instead in order to read in the magic word ```LETMEWIN\n```.
So in order to set variable ```fd``` to value 0, we have to convert the hexadecimal value ```0x1234``` to decimal...
```
fd@pwnable:~$ python -c 'print(int("0x1234", 16))'
4660
```
...and then use the result as our programs's argument: 
```
fd@pwnable:~$ ./fd 4660
```
Now the program waits for our interactivy input. We simply have to type ```LETMEWIN``` followed by ```<RETURN>``` (this represents the newline escape character ```\n```)...
```
LETMEWIN
good job :)
mommy! I think I know what a file descriptor is!!
```
...and we just have solved our first level :-)
The flag which we looked for is ```mommy! I think I know what a file descriptor is!!``` and it can now be registered in order to continue with the next level.
