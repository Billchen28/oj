all: kmp
kmp: main.o
	gcc $(LDFLAGS) main.o -g -o kmp
main.o:
	gcc $(LDFLAGS) -g -c main.c
clean:
	rm *.o kmp kmp.exe
