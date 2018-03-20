from pwn import *

conn = remote('127.0.0.1', 20001)

print conn.recv()
data = conn.recv()
data += conn.recv()
print data
conn.send(data)
print conn.recv()
conn.close()
