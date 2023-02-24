main.out: test.o queue.o
	gcc test.o queue.o -o main.out

test.o: queue.c queue.h
	gcc -c test.c queue.c

queue.o: queue.c queue.h
	gcc -c queue.c 