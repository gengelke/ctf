100 Points

https://goo.gl/bcaJFt

nc 35.200.197.38 8000
Go get flag

$ strings ./miscertify
[...]
Enter filename:
Enter command:
.dat
flag.flag
Hello User, Enter name:
Choose your option
	1.Create file
	2.Read file
	3.Sign file
	>>>
/bin/sh
NULL
signature
[...]

$ strace ./miscertify
execve("./miscertify", ["./miscertify"], 0x7fff2a2f4610 /* 20 vars */) = 0
brk(NULL)                               = 0x1e3c000
brk(0x1e3d200)                          = 0x1e3d200
arch_prctl(ARCH_SET_FS, 0x1e3c8c0)      = 0
uname({sysname="Linux", nodename="kali", ...}) = 0
readlink("/proc/self/exe", "/home/user/Downloads/miscertify", 4096) = 31
brk(0x1e5e200)                          = 0x1e5e200
brk(0x1e5f000)                          = 0x1e5f000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "flag.flag", O_RDONLY) = -1 ENOENT (No such file or directory)    <=================== !!!!
fstat(1, {st_mode=S_IFCHR|0600, st_rdev=makedev(136, 2), ...}) = 0
write(1, "Hello User, Enter name:\t", 24Hello User, Enter name:	) = 24
fstat(0, {st_mode=S_IFCHR|0600, st_rdev=makedev(136, 2), ...}) = 0
read(0,

$ nc 35.205.196.143 8000

Choose your option
    1.Create file
    2.Read file
    3.Sign file
    >>>2
Enter filename:    flag.flag
evlz{intended_mistake}ctf                       <===================== !!!
Choose your option
    1.Create file
    2.Read file
    3.Sign file

http://manoharvanga.com/hackme/
