make: main.out
	./main.out input.txt output.txt

main.out: io.o memory.o main.o 
	g++ io.o memory.o main.o -o main.out
	rm *.o *.gch
	
main.o: main.cpp
	g++ -c main.cpp

memory.o: memory.hpp memory.cpp
	g++ -c memory.hpp memory.cpp 

io.o: io.hpp io.cpp
	g++ -c io.hpp io.cpp 

