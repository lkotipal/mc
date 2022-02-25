CC=gfortran
CFLAGS=-O2
OBJS=mt19937-64.o sand_pile.o

target: $(OBJS)
	$(CC) -o sand_pile.exe $(OBJS) $(CFLAGS)

mt19937-64.o: mt19937-64.f95
	$(CC) -c mt19937-64.f95 $(CFLAGS)

sand_pile.o: sand_pile.f90
	$(CC) -c sand_pile.f90 $(CFLAGS)

clean:
	rm -f *.o *.exe