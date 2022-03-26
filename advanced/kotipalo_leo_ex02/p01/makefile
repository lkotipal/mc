CC=g++
CFLAGS=-std=c++17 -O2 -D_USE_MATH_DEFINES
SRC=radiation_simulator.hpp absorption_simulator.hpp point.hpp

main: main.cpp $(SRC)
	$(CC) $(CFLAGS) -o walker.exe main.cpp

clean:
	rm -f *.o *.exe