CC=g++
CFLAGS=-std=c++20 -O2
OBJS=vdc.o

main: main.cpp vdc.o
	$(CC) $(CFLAGS) -o vdc.exe main.cpp $(OBJS)

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.exe