#!/bin/bash

#NAME: Matthew chan
#EMAIL: matthew_2185@yahoo.com
#ID: 805291212

if [ `hostname | grep -c lasr.cs.ucla.edu` -ge 1 ]
then
	gcc -o lab4b lab4b.c -g -Wall -Wextra -lmraa -lm
else
	gcc -o lab4b lab4b.c -g -Wall -Wextra -DDUMMY -lm
fi
