all: tree
tree: main.o binary_tree.o queue.o
	gcc $(LDFLAGS) queue.o binary_tree.o main.o -g -o tree
main.o: binary_tree.o queue.o
	gcc $(LDFLAGS) -g -c main.c
binary_tree.o:queue.o queue.o
	gcc $(LDFLAGS) -g -c binary_tree.c
queue.o:
	gcc $(LDFLAGS) -g -c queue.c
clean:
	rm *.o tree tree.exe
