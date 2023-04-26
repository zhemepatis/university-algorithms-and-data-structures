make: main.out
	./main.out duota.txt

main.out: main.o
	g++ main.o -o main.out
	rm *.o
	
main.o: main.cpp
	g++ -c main.cpp