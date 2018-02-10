Natas Level 4 → Level 5
=======================

Username: natas5
URL:      http://natas5.natas.labs.overthewire.org


Solution
========

This one's pretty similar to the previous level. When we browse to ```http://natas5.natas.labs.overthewire.org``` and login with username ```natas5``` and the password that we gained in level3-4
we get the following message:

```
Access disallowed. You are not logged in
```

Even after we have entered the correct credentials we don't get access to the web site. And we even can't enter our credentials once again because when we reload the page it doesn't ask for our credentials but directly claims that we are not allowed to access this page.
Sounds like our login has been saved but something went wrong. Most likely this is done through a mechanism named [```Cookies```](https://en.wikipedia.org/wiki/HTTP_cookie).
Let's have a look into the data that have been sent around when we loaded the web page, look for an appropriate Cookie entry and try to modify it in order to get access to this web site.

In Firefox, right-click on the web page, click on "Inspect Element" and select "Storage" => "Cookies" => "http://http://natas5.natas.labs.overthewire.org/".
On the right side of the window you see a line that starts with "loggedin". Initially it's "Value" is "0". Double-click on this field and change it's value to "1".
Finally reload the web site and you'll get next level's password"

```
Access granted. The password for natas6 is aGoY4q2Dc6MgDq4oL4YtoKtyAg9PeHa1
```

Note to myself
--------------

Instead of using a GUI web browser like Firefox one can use cURL instead:

```
curl -isu natas5:iX6IOfmpN7AYOQGPwtn3fXpbaJVJcHfq http://natas5.natas.labs.overthewire.org
```
```
curl -I http://natas5:iX6IOfmpN7AYOQGPwtn3fXpbaJVJcHfq@natas5.natas.labs.overthewire.org/
```
```
curl --cookie loggedin=1 http://natas5:iX6IOfmpN7AYOQGPwtn3fXpbaJVJcHfq@natas5.natas.labs.overthewire.org/

```
