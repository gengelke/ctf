Bandit Level 20 → Level 21
==========================

Level Goal
----------

There is a setuid binary in the homedirectory that does the following: it makes a connection to localhost on the port you specify as a commandline argument. It then reads a line of text from the connection and compares it to the password in the previous level (bandit20). If the password is correct, it will transmit the password for the next level (bandit21).

NOTE: [Changes to the infrastructure](http://overthewire.org/help/sshinfra.html) made this level more difficult. You will need to figure out a way to launch multiple commands in the same Docker instance.

NOTE 2: Try connecting to your own network daemon to see if it works as you think

Commands you may need to solve this level
-----------------------------------------

ssh, nc, cat, bash, screen, tmux


Solution
========

This challenge is a little bit tricky and requires some more detailed knowledge of a couple of tools and techniques. Firstly I was a little bit stuck without any idea how to solve this. I looked for open ports on localhost in order to find out which port I would have to connect to using the mentioned setuid binary ```suconnect```:

```
bandit20@bandit:~$ nmap localhost

Starting Nmap 6.40 ( http://nmap.org ) at 2017-10-27 05:56 UTC
Nmap scan report for localhost (127.0.0.1)
Host is up (0.00052s latency).
Other addresses for localhost (not scanned): 127.0.0.1
Not shown: 997 closed ports
PORT      STATE SERVICE
22/tcp    open  ssh
113/tcp   open  ident
30000/tcp open  unknown
```

So I tried all three open ports:

```
bandit20@bandit:~$ ./suconnect 22
Read: SSH-2.0-OpenSSH_6.6.1p1 Ubuntu-2ubuntu2.8
ERROR: This doesn't match the current password!
bandit20@bandit:~$
bandit20@bandit:~$ ./suconnect 113

qqq
^C
bandit20@bandit:~$ ./suconnect 30000
qqq
^C
```

But obviously none of these were able to let me enter the current level's password. So I didn't know how to proceed.
After I slept over it and read the text(s) once again, I realized that the solution is described pretty detailed.

More precisely the text references to a document which [describes the infrastructure](http://overthewire.org/help/sshinfra.html)) of OverTheWire challenges. Here we can read that for each SSH connection a new Docker container gets started. Therefore everything gets lost when one disconnects or connects with another SSH session. Furthermore the text tells us to consider to use the following commands: ```ssh, nc, cat, bash, screen, tmux```. 
Furthermore I simply executed the binary without any arguments and got this:

```
bandit20@bandit:~$ ./suconnect
Usage: ./suconnect <portnumber>
This program will connect to the given port on localhost using TCP. If it receives the correct password from the other side, the next password is transmitted back.
```

So with these information in mind, reading the text "Level Goal" once again brought me to the idea to use netcat (nc) in order to set up a listening server which simply provides the current level's password whenever another process connects to it. This would make sence because ```suconnect``` is not able to read the required current level's password from stdin. Then I could use ```suconnect``` in order to connect to my small server's port and see what happens. 

But wait... Since we only have one SSH connection open due to the Docker stuff limitations described before, we first have to find a way to execute several commands in parallel. Since I was already familiar with tmux/screen I picked it to open two terminal windows within the same SSH connection:

```
bandit20@bandit:~$ tmux
```

Inside of tmux I pressed the key combination ```Ctrl+b "``` in order to split the screen into two panes. In the newly created pane I started a nectcat server listening on port 12345 using the command line ```echo "GbKksEFF4yrVs6il55v6gwY5aVje5f0j" | nc -l 12345```. Then I switched to the other open tmux pane by pressing the key combination ```Ctr+b o``` and executed ```suconnect 12345``` inside of it in order to connect to my previously opened netcat server port.

The result is that we get the information about a matching password in the upper tmux pane:

```
bandit20@bandit:~$ ./suconnect 12345
Read: GbKksEFF4yrVs6il55v6gwY5aVje5f0j
Password matches, sending next password
bandit20@bandit:~$
```

While we get the next level's password in the lower tmux pane:

```
bandit20@bandit:~$ echo "GbKksEFF4yrVs6il55v6gwY5aVje5f0j" | nc -l 12345
gE269g2h3mw3pwgrj0Ha9Uoqen1c9DGr
bandit20@bandit:~$
```

Phew! This was tricky ;-)
