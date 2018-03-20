from pwn import *

r = remote('1.2.3.4', 3333)
r.send("Hello world!\n")
print "> " + r.recv()
print r.recvuntil("END\n")
#interactive mode
r.interactive()
