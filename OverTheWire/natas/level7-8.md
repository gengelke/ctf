Natas Level 7 → Level 8
=======================

Username: natas8
URL:      http://natas8.natas.labs.overthewire.org


Solution
========

When we browse to the given URL with the credentials gained in level6-7, we once again get a web form where we are asked to enter a *secret*. The website's source code looks like this:

```
[...]
$encodedSecret = "3d3d516343746d4d6d6c315669563362";

function encodeSecret($secret) {
    return bin2hex(strrev(base64_encode($secret)));
}

if(array_key_exists("submit", $_POST)) {
    if(encodeSecret($_POST['secret']) == $encodedSecret) {
    print "Access granted. The password for natas9 is <censored>";
    } else {
    print "Wrong secret";
    }
}
?>

<form method=post>
Input secret: <input name=secret><br>
<input type=submit name=submit>
</form>

<div id="viewsource"><a href="index-source.html">View sourcecode</a></div>
</div>
</body>
</html>
```

Obviously the *secret* is included in the source code again. But this time it has been encoded. So in order to get the *secret* that we have to enter in the web form, we have to decode the string first. That's done by reversing the function ```encodeSecret($secret)``` which looks like this:

```
function encodeSecret($secret) {
    return bin2hex(strrev(base64_encode($secret)));
}
```

The code works like this: Anything that is entered to the web form and submitted to the webserver is then encoded using ```bin2hex(strrev(base64_encode($secret)))``` and finally compared to the encoded secret  ```3d3d516343746d4d6d6c315669563362``` which is hardcoded in the web site's source code. 

We have to implement some code which does the reversal for us. Such codee could look like this:

```
user@workstation ~ $ cat decodeSecret.php
<?
$encodedSecret = "3d3d516343746d4d6d6c315669563362";

function decodeSecret($encodedSecret) {
    return base64_decode(strrev(hex2bin($encodedSecret)));
}

print decodeSecret($encodedSecret)
?>
```

When we execute this code on our personal workstation we get the decoded *secret*:

```
user@workstation ~ $ php decodeSecret.php
oubWYf2kBq
```

If we now enter the string ```oubWYf2kBq``` into the web form and submit it, we get the next level's password: 

```
Access granted. The password for natas9 is W0mMhUcRRnG8dcghE4qvk3JA9lGt8nDl
```

Note to myself
==============
Instead of using a GUI web browser like Firefox one can use cURL instead:
```
curl --data "submit=submit&secret=oubWYf2kBq" http://natas8:DBfUBfqQG69KvJvJ1iAbMoIpwSNQ9bWe@natas8.natas.labs.overthewire.org/
```

Instead of writing the decodeSecret() function in PHP, in could have easily been done in Bash as well:
```
echo 3d3d516343746d4d6d6c315669563362 | xxd -p -r | rev | base64 -D
```
