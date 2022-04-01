CC=g++
CFLAGS=-std=c++17 -O2 -D_USE_MATH_DEFINES
SRC=point.hpp kinetic_mc.hpp

main: main.cpp $(SRC)
	$(CC) $(CFLAGS) -o kmc.exe main.cpp

clean:
	rm -f *.o *.exe