b1 = bytearray("fbf9eefce1f2f5eaffc5e3f5efc5efe9fffec5fbc5e9f9e8f3eaeee7")
b2 = bytearray("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
b2 = bytearray("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")

b = bytearray(len(b1))

for i in range(len(b1)):
  b[i] = b1[i] ^ b2[i]

print b
#bytearray(b'GWB\x00TAG')
