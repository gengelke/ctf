50 Points

LOL LMAO

gengelke@genmac ~ $ hexdump lol
0000000 20 09 09 20 20 09 20 09 20 09 09 09 20 09 09 20
0000010 20 09 09 20 09 09 20 20 20 09 09 09 09 20 09 20
0000020 20 09 09 09 09 20 09 09 20 09 09 20 09 20 20 09
0000030 20 09 20 09 09 09 09 09 20 09 09 20 20 09 20 20
0000040 20 09 09 20 09 09 09 09 20 09 09 20 09 09 09 20
0000050 20 09 09 09 20 09 20 20 20 09 20 09 09 09 09 09
0000060 20 09 09 20 09 09 20 20 20 09 09 20 09 20 20 09
0000070 20 09 09 20 09 20 09 09 20 09 09 20 20 09 20 09
0000080 20 09 20 09 09 09 09 09 20 09 09 09 20 09 09 09
0000090 20 09 09 09 20 09 09 09 20 09 09 20 20 09 20 09
00000a0 20 09 09 09 09 09 20 09 20 09 09 20 20 20 09 09
00000b0 20 09 09 09 20 09 20 20 20 09 09 20 20 09 09 20
00000c0

meine annahme, dass der hexdump morse-code ist, war fast richtig. es ist binary. denn fuer morse kam das muster nicht hin. also habe ich mir zum probieren ein kleines python gebastelt. ich habe einfach mal eine variante ausprobiert indem ich angenommen habe, dass jedes 0x09 (tab) eine 1 ist und jedes 0x20 (space) eine 0. und den daraus ergebenden "binary string" habe ich dann umgewandelt:

```root@ff4cbcc93a30 /data # cat lol.py
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
print binascii.unhexlify('%x' % n)```

geholfen hat http://www.asciitable.com/ und die approved answer aus https://stackoverflow.com/questions/7396849/convert-binary-to-ascii-and-vice-versa
