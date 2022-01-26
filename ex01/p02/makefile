CC=g++
CFLAGS=-std=c++20 -O
OBJ=buffon.o

main: main.cpp $(OBJ)
	$(CC) $(CFLAGS) -o main main.cpp $(OBJ)

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.exe