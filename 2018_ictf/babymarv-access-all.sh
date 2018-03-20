#!/bin/sh

for((i=1; i<254; i++)) ; do nc -w 1 172.31.129.$i 20001 && echo "172.31.129.$i"; echo "------"; done




