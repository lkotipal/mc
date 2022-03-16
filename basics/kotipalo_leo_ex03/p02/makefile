CC=g++
CFLAGS=-std=c++20 -O2
SRC=sphere.hpp

main: main.cpp $(SRC)
	$(CC) $(CFLAGS) -o sphere.exe main.cpp

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.exe