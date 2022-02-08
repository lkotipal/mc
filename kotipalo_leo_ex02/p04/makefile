CC=g++
CFLAGS=-std=c++20 -O
SRC=../p01/rng.hpp ../p03/lcg.hpp ../p03/pm.hpp shuffler.hpp

main: main.cpp $(SRC)
	$(CC) $(CFLAGS) -o rng.exe main.cpp

clean:
	rm -f *.o *.exe