#Matthew Chan
#805291212
#matthew_2185@yahoo.com

default: 
	gcc -g -Wall -Wextra lab0.c -o lab0

check: default smoke_tests

clean: 
	rm -f lab0 lab0-805291212.tar.gz

dist: default
	tar -cvzf lab0-805291212.tar.gz lab0.c Makefile backtrace.png breakpoint.png README

smoke_tests: regular_test io_comparison fake_input segfault_test fake_argument

regular_test:
	echo "asdf" > input.txt; \
	-./lab0 --input input.txt --output output.txt; \
	if [$$? -ne 0]; then \
		echo "Case 1 failed: Fails normal functionality"; \
	else \
		echo "Case 1 passed"; \
	fi

io_comparison:
	cmp -s input.txt output.txt; \
	if [$$? -ne 0]; then \
		echo "Case 2 failed: Output does not match input"; \
	else \
		echo "Case 2 passed"; \
	fi
	rm -f input.txt output.txt

fake_input:
	./lab0 --input fakefile.txt; \
	if [$$? -ne 2]; then \
		echo "Case 3 failed: Does not catch fake input file"; \
	else \
		echo "Case 3 passed"; \
	fi

segfault_test:
	./lab0 --segfault --catch; \
	if [$$? -ne 4]; then \
		echo "Case 4 failed: Did not catch segmentation fault"; \
	else \
		echo "Case 4 passed"; \
	fi

fake_argument:
	./lab0 --lol; \
	if {$$? -ne 1]; then \
		echo "Case 5 failed: Did not detect invalid argument option"; \
	else \
		echo "Case 5 passed"; \
	fi
