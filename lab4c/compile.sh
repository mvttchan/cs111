#!/bin/bash

#NAME: Matthew chan
#EMAIL: matthew_2185@yahoo.com
#ID: 805291212

if [ `hostname | grep -c lasr.cs.ucla.edu` -ge 1 ]
then
	gcc -o lab4c_tcp lab4c_tcp.c -g -Wall -Wextra -lmraa -lm
	gcc -o lab4c_tls lab4c_tls.c -g -Wall -Wextra -lmraa -lm -lssl -lcrypto
else
	gcc -o lab4c_tcp lab4c_tcp.c -g -Wall -Wextra -DDUMMY -lm
	gcc -o lab4c_tls lab4c_tls.c -g -Wall -Wextra -DDUMMY -lm -lssl -lcrypto
fi
