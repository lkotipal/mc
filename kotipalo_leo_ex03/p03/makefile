CC=g++
CFLAGS=-std=c++20 -O2
OBJS=
SRC=poisson_integrator.hpp direct_sampler.hpp rejection_sampler.hpp partially_stratified_sampler.hpp

main: main.cpp $(OBJS) $(SRC)
	$(CC) $(CFLAGS) -o poisson.exe main.cpp $(OBJS)

%.o: %.cpp %.hpp $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.exe