CXX = g++
CXXFLAGS = -c

make: main.out
	./main.out input.txt output.txt

main.out: io.o memory.o main.o 
	${CXX} io.o memory.o main.o -o main.out
	
main.o: main.cpp
	${CXX} ${CXXFLAGS} main.cpp

memory.o: memory.hpp memory.cpp
	${CXX} ${CXXFLAGS} memory.cpp 

io.o: io.hpp io.cpp
	${CXX} ${CXXFLAGS} io.cpp 

