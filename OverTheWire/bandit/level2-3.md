Bandit Level 2 → Level 3
========================

Level Goal
----------

The password for the next level is stored in a file called spaces in this filename located in the home directory

Commands you may need to solve this level
-----------------------------------------

ls, cd, cat, file, du, find

Helpful Reading Material
------------------------

[Google Search for “spaces in filename”](https://www.google.com/search?q=spaces+in+filename)


Solution
========

Once again we use the already known tools in order to display the content of the file nmed "spaces in this filename". This time we have to deal with spaces in the filenname.
If we would just do a "cat spaces in this filename" we wouldn't be really successful because cat would interprete the spaces as the beginning of another command line option:

```
bandit2@bandit:~$ cat spaces in this filename
cat: spaces: No such file or directory
cat: in: No such file or directory
cat: this: No such file or directory
cat: filename: No such file or directory
```

So once again we have to find a way how to mask pecial charachters. Modern BASH-like shells automatically convert spaces in file names.
You just have to type the first beginning berfore the first space and then press the "TAB" key:

```
bandit2@bandit:~$ cat spaces<TAB>
bandit2@bandit:~$ cat spaces\ in\ this\ filename
UmHadQclWmgdLOKQ3YNgjWxGoRMb5luK
```

Another option to mask special characters like spaces would be to manually put a backslash ("\\") before each and every spave or any other special character in csse that your shell doesn't do it for you.
