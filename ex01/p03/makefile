CC=g++
CFLAGS=-std=c++20 -O
OBJ=lcg.o pm.o mt.o

main: main.cpp $(OBJ)
	$(CC) $(CFLAGS) -o main main.cpp $(OBJ)

%.o: %.cpp %.hpp rng.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.exe