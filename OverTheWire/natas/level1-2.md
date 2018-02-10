Natas Level 1 → Level 2
=======================

Username: natas2
URL:      http://natas2.natas.labs.overthewire.org


Solution
========

Browse to the URL and login with username ```natas2``` and the password which you gained in level0-1.
Then you'll get the following message:

```
There is nothing on this page 
```

And that's more or less true. Because when we look into the website's code there's not much obvious in it in order to get a password for the next level:

```
<html>
<head>
<!-- This stuff in the header has nothing to do with the level -->
<link rel="stylesheet" type="text/css" href="http://natas.labs.overthewire.org/css/level.css">
<link rel="stylesheet" href="http://natas.labs.overthewire.org/css/jquery-ui.css" />
<link rel="stylesheet" href="http://natas.labs.overthewire.org/css/wechall.css" />
<script src="http://natas.labs.overthewire.org/js/jquery-1.9.1.js"></script>
<script src="http://natas.labs.overthewire.org/js/jquery-ui.js"></script>
<script src=http://natas.labs.overthewire.org/js/wechall-data.js></script><script src="http://natas.labs.overthewire.org/js/wechall.js"></script>
<script>var wechallinfo = { "level": "natas2", "pass": "ZluruAthQk7Q2MqmDeTiUij2ZvWy2mBi" };</script></head>
<body>
<h1>natas2</h1>
<div id="content">
There is nothing on this page
<img src="files/pixel.png">
</div>
</body></html>
```
But wait... There's an ```<img>``` tag referencing a file named ```files/pixel.png```. So let's see if there's something in the same directory that may help us.
Just browse to URL ```http://natas2.natas.labs.overthewire.org/files/``` and you'll see this:

```
Index of /files
[ICO]	Name	Last modified	Size	Description
[PARENTDIR]	Parent Directory	 	- 	 
[IMG]	pixel.png	2016-12-15 16:07 	303 	 
[TXT]	users.txt	2016-12-20 05:15 	145 	 
Apache/2.4.10 (Debian) Server at natas2.natas.labs.overthewire.org Port 80
```
Then click on the link namen ```users.txt``` and you'll get a list of users including their passwords:

```
# username:password
alice:BYNdCesZqW
bob:jw2ueICLvT
charlie:G5vCxkVV3m
natas3:sJIJNW6ucpu6HPZ1ZAchaDtwd7oGrD14
eve:zo4mJWyNj2
mallory:9urtcpzBmH
```
