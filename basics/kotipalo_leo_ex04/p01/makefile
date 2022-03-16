CC=g++
CFLAGS=-std=c++20 -O2
SRC=maxwell_boltzmann.hpp

all: test_delta test_points

test_delta: test_delta.cpp $(SRC)
	$(CC) $(CFLAGS) -o test_delta.exe test_delta.cpp

test_points: test_points.cpp $(SRC)
	$(CC) $(CFLAGS) -o test_points.exe test_points.cpp

clean:
	rm -f *.o *.exe