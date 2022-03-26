CC=g++
CFLAGS=-std=c++17 -O2 -D_USE_MATH_DEFINES
SRC=../p01/radiation_simulator.hpp ../p01/point.hpp ../p02/scattering_simulator.hpp better_scattering_simulator.hpp

main: main.cpp $(SRC)
	$(CC) $(CFLAGS) -o walker.exe main.cpp

clean:
	rm -f *.o *.exe