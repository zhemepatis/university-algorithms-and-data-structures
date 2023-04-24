make: main.out
	./main.out input.txt output.txt 

main.out: stack.o queue.o io.o main.o
	gcc stack.o queue.o io.o main.o -o main.out
	rm *.o *.gch

main.o:
	gcc -c main.c

io.o:
	gcc -c io.c

stack.o:
	gcc -c stack.h stack.c

queue.o:
	gcc -c queue.h queue.c

del-o:
	rm *.o 

del-gch:
	rm *.gch

