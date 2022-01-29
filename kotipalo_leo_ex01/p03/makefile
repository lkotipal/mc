CC=g++
CFLAGS=-std=c++20 -O
SRC=rng.hpp lcg.hpp pm.hpp mt.hpp

main: main.cpp $(SRC)
	$(CC) $(CFLAGS) -o rng.exe main.cpp

clean:
	rm -f *.o *.exe