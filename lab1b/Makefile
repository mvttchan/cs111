#NAME:	Matthew Chan
#EMAIL:	matthew_2185@yahoo.com
#ID:	805291212

default: clean
	gcc -g -Wall -Wextra lab1b-server.c -o lab1b-server -lz
	gcc -g -Wall -Wextra lab1b-client.c -o lab1b-client -lz
clean:
	rm -f lab1b *.o *.tar.gz lab1b-client lab1b-server

dist:	clean default
	tar -czvf lab1b-805291212.tar.gz lab1b-server.c lab1b-client.c Makefile README
