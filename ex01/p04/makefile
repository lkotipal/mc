CC=g++
CFLAGS=-std=c++20 -O
SRC=../p03/rng.hpp ../p03/lcg.hpp ../p03/pm.hpp ../p03/mt.hpp

main: main.cpp buffon.o $(SRC)
	$(CC) -o rng.exe main.cpp buffon.o $(CFLAGS)

%.o: %.cpp %.hpp ../p03/rng.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o *.exe