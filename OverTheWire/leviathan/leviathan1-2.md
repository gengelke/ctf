Leviathan Level 1 → Level 2
===========================

Level Goal
----------

There is no information for this level, intentionally.

Solution
========

There's no hint text or anything else for this level. So let's look around what we can find in the home directory:

```
leviathan1@leviathan:~$ ls -al
total 28
drwxr-xr-x  2 root       root       4096 Aug 26  2019 .
drwxr-xr-x 10 root       root       4096 Aug 26  2019 ..
-rw-r--r--  1 root       root        220 May 15  2017 .bash_logout
-rw-r--r--  1 root       root       3526 May 15  2017 .bashrc
-r-sr-x---  1 leviathan2 leviathan1 7452 Aug 26  2019 check
-rw-r--r--  1 root       root        675 May 15  2017 .profile
```

There's a binary which belongs to the next level's user **leviathan2** so most likely we have to do something with it in order to get the password.
Let's find out what it does:

```
leviathan1@leviathan:~$ ./check
password: rioGegei8m
Wrong password, Good Bye ...
```

OK, so obviously we have to find a hidden password inside of the binary. Let's start with **strings** first:

```
leviathan1@leviathan:~$ strings ./check
/lib/ld-linux.so.2
libc.so.6
_IO_stdin_used
puts
setreuid
printf
getchar
system
geteuid
strcmp
__libc_start_main
__gmon_start__
GLIBC_2.0
PTRhp
QVh;
secrf
love
UWVS
t$,U
[^_]
password:
/bin/sh
Wrong password, Good Bye ...
;*2$"
GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516
crtstuff.c
__JCR_LIST__
deregister_tm_clones
__do_global_dtors_aux
completed.6587
__do_global_dtors_aux_fini_array_entry
frame_dummy
__frame_dummy_init_array_entry
check.c
__FRAME_END__
__JCR_END__
__init_array_end
_DYNAMIC
__init_array_start
__GNU_EH_FRAME_HDR
_GLOBAL_OFFSET_TABLE_
__libc_csu_fini
strcmp@@GLIBC_2.0
__x86.get_pc_thunk.bx
printf@@GLIBC_2.0
getchar@@GLIBC_2.0
_edata
geteuid@@GLIBC_2.0
__data_start
puts@@GLIBC_2.0
system@@GLIBC_2.0
__gmon_start__
__dso_handle
_IO_stdin_used
setreuid@@GLIBC_2.0
__libc_start_main@@GLIBC_2.0
__libc_csu_init
_fp_hw
__bss_start
main
__TMC_END__
.symtab
.strtab
.shstrtab
.interp
.note.ABI-tag
.note.gnu.build-id
.gnu.hash
.dynsym
.dynstr
.gnu.version
.gnu.version_r
.rel.dyn
.rel.plt
.init
.plt.got
.text
.fini
.rodata
.eh_frame_hdr
.eh_frame
.init_array
.fini_array
.jcr
.dynamic
.got.plt
.data
.bss
.comment
```

Nothing obvious which might look like a password string. So let's run the binary within **ltrace** in order to find out what it does under the hood:

```
leviathan1@leviathan:~$ ltrace ./check
__libc_start_main(0x804853b, 1, 0xffffd754, 0x8048610 <unfinished ...>
printf("password: ")                                                                                                             = 10
getchar(1, 0, 0x65766f6c, 0x646f6700password: bla
)                                                                                            = 98
getchar(1, 0, 0x65766f6c, 0x646f6700)                                                                                            = 108
getchar(1, 0, 0x65766f6c, 0x646f6700)                                                                                            = 97
strcmp("bla", "sex")                                                                                                             = -1
puts("Wrong password, Good Bye ..."Wrong password, Good Bye ...
)                                                                                             = 29
+++ exited (status 0) +++
```

BINGO! The code line **strcmp("bla", "sex")** is the solution:

```
leviathan1@leviathan:~$ ./check
password: sex
$ cat /etc/leviathan_pass/leviathan2
ougahZi8Ta
```
