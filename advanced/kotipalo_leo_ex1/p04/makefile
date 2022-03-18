CC=g++
CFLAGS=-std=c++20 -O2
SRC=point.hpp self_avoiding_walker.hpp

main: main.cpp $(SRC)
	$(CC) $(CFLAGS) -o walker.exe main.cpp

clean:
	rm -f *.o *.exe