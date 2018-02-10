Natas Level 3 → Level 4
=======================

Username: natas4
URL:      http://natas4.natas.labs.overthewire.org


Solution
========

Browse to the URL ```http://natas4.natas.labs.overthewire.org``` and login with username ```natas4``` and the password that you gained in level2-3.
You'll get the following message:

```
Access disallowed. You are visiting from "" while authorized users should come only from "http://natas5.natas.labs.overthewire.org/" 
```

Too bad. Even if we browse to ```http://natas5.natas.labs.overthewire.org``` first we don't get access to ```http://natas4.natas.labs.overthewire.org``` because we don't know natas5's password yet and therefore can't access the page.
As a consequence we get a similar message again saying this:

```
Access disallowed. You are visiting from "http://natas4.natas.labs.overthewire.org/index.php" while authorized users should come only from "http://natas5.natas.labs.overthewire.org/" 
```

Obviously we have to find a way how to make the browser think that we are comming right from the web page on URL ```http://natas5.natas.labs.overthewire.org```. This can be done with a Firefox plugin named [```RefControl```](https://addons.mozilla.org/en-US/firefox/addon/refcontrol/). After it has been installed and Firefox restarted, we configure the plugin in order to spoof the [HTTP referer header field](https://en.wikipedia.org/wiki/HTTP_referer) information sent by the web browser to the web server. Click on "RefControl Options" => "Add Site" => "Site: http://natas4.natas.labs.overthewire.org" => "Custom: http://natas5.natas.labs.overthewire.org/".

After RefControl has been successfully configured, reload the URL ```http://natas4.natas.labs.overthewire.org``` and you'll get the next level's password:

```
Access granted. The password for natas5 is iX6IOfmpN7AYOQGPwtn3fXpbaJVJcHfq
```

Note to myself
--------------

Instead of using a GUI web browser like Firefox one can use cURL instead:

```
curl --referer "http://natas5.natas.labs.overthewire.org/" http://natas4:Z9tkRkWmpt9Qr7XrR5jWRkgOU901swEZ@natas4.natas.labs.overthewire.org/
```
