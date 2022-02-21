CC=g++
CFLAGS=-std=c++20 -O2
SRC=distribution.hpp inversion_distribution.hpp sampling_distribution.hpp

main: main.cpp $(SRC)
	$(CC) $(CFLAGS) -o dis.exe main.cpp

clean:
	rm -f *.o *.exe