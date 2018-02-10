lol.py
import binascii

str = "0b"
with open("lol", "rb") as f:
      ba = bytearray(f.read())
      for byte in ba:
          if (byte == 9):
              str += "1"
          elif (byte == 32):
              str += "0"
n = int(str, 2)
print binascii.unhexlify('%x' % n)
