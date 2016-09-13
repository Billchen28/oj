all: tree
tree: main.o
	gcc $(LDFLAGS) main.o -g -o tree
main.o:
	gcc $(LDFLAGS) -g -c main.c
clean:
	rm *.o tree tree.exe
