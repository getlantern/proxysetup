all: main

main: proxysetup.c
	gcc proxysetup.c -o proxysetup

clean:
	rm -f proxysetup *.o