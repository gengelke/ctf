Natas Level 2 → Level 3
=======================

Username: natas3
URL:      http://natas3.natas.labs.overthewire.org


Solution
========

Browse to the URL with username ```natas3``` and the password you gained in level1-2. You'll get the following messages:

```
There is nothing on this page 
```

So once again we right-click on the web page and select "View Page Source":

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
<script>var wechallinfo = { "level": "natas3", "pass": "sJIJNW6ucpu6HPZ1ZAchaDtwd7oGrD14" };</script></head>
<body>
<h1>natas3</h1>
<div id="content">
There is nothing on this page
<!-- No more information leaks!! Not even Google will find it this time... -->
</div>
</body></html>
```

Too bad. It becomes harder now. There's really nothing obvious left in the source code which could help us to gain the next level's password.
There's only a one line saying this:

```
<!-- No more information leaks!! Not even Google will find it this time... -->
```

I wonder if this is a hint how to solve this level. In previous level 1-2 we experienced that there might be files in a directory that are not named on the web page itself but are accessible if we put them into the browser's URL. Unfortunately this time there's neither a sign that there's a file available nor do we know how to list the content of the current directory/path. But having the sentence "Not even Google will find it this time..." in mind, there's maybe a [robots.txt](https://support.google.com/webmasters/answer/6062608?hl=en) file available:

> A [robots.txt](https://support.google.com/webmasters/answer/6062608?hl=en) file is a file at the root of your site that indicates those parts of your site you don’t want accessed by search engine crawlers.

So let's try this by browsing to URL ```http://natas3.natas.labs.overthewire.org/robots.txt```. That's what we get:

```
User-agent: *
Disallow: /s3cr3t/
```

Or in other words: The file robots.txt tells us that there's a subdirectory named ```/s3cr3t/``` which the site's owner does want to get accessed by search engine crawlers. If we browse to the URL ```http://natas3.natas.labs.overthewire.org/s3cr3t/``` anyhow we get a directory listing with a file named ```users.txt``` once again:

```
Index of /s3cr3t
[ICO]	Name	Last modified	Size	Description
[PARENTDIR]	Parent Directory	 	- 	 
[TXT]	users.txt	2016-12-20 05:15 	40 	 
Apache/2.4.10 (Debian) Server at natas3.natas.labs.overthewire.org Port 80
```

So when we click on the link of ```users.txt``` we get the next level's password:

```
natas4:Z9tkRkWmpt9Qr7XrR5jWRkgOU901swEZ
```
