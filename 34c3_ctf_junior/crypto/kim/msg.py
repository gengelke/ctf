import hashlib
#from secret import SECRET
SECRET = ""
def mac(msg):
    return hashlib.sha1(SECRET + msg).hexdigest()

mac = mac('f=dont.gif')

print mac
