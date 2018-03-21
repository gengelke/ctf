def xor(data, key): 
    return bytearray(a^b for a, b in zip(*map(bytearray, [data, key]))) 

ciphertext = "fbf9eefce1f2f5eaffc5e3f5efc5efe9fffec5fbc5e9f9e8f3eaeee7"
key = "H"*len( ciphertext )

print xor(ciphertext,key)
