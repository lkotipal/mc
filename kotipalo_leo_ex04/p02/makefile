CC=g++
CFLAGS=-std=c++20 -O2
SRC=sampler.hpp discrete_sampler.hpp
OBJS=

main: main.cpp $(SRC)
	$(CC) $(CFLAGS) -o sampler.exe main.cpp $(OBJS)

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.exe