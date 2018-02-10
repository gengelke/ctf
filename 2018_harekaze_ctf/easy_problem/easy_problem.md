Description
Do you know ROT13? Can you decode this text? UnerxnmrPGS{Uryyb, jbeyq!}

(WarmUp, 30 points)

http://www.rot13.com/

user@0075b85222f3 /data $ cat ./rot.py
import codecs
print codecs.encode('UnerxnmrPGS{Uryyb, jbeyq!}', 'rot_13')

'UnerxnmrPGS{Uryyb, jbeyq!}'.encode('rot13')

HarekazeCTF{Hello, world!}
