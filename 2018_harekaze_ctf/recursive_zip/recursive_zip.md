Description
Do you know unzip?

    flag.zip

(Warmup, 40 points)

user@0075b85222f3 /data/flag $ cat recu.sh
#!/bin/bash

while [ ! -e "flag.txt" ]
do
    unzip -o flag.zip
done

user@0075b85222f3 /data/flag $ cat flag.txt
HarekazeCTF{(\lambda f. (\lambda x. f (x x)) (\lambda x . f (x x))) zip}


