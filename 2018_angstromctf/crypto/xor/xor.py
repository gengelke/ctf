# https://stackoverflow.com/questions/41819489/single-byte-xor-cipher-python

import binascii

encoded = binascii.unhexlify('fbf9eefce1f2f5eaffc5e3f5efc5efe9fffec5fbc5e9f9e8f3eaeee7')
for key in range(256):  # All combinations for a single byte: 2^8 = 256
    decoded = ''.join(chr(byte ^ key) for byte in encoded)
    if decoded.isprintable():
#        if decoded.find("actf"):
         print(key, decoded)
