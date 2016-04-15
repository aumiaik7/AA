CC=g++
CFLAGS=-c 


all: qsort

qsort: qsort1.o 
	$(CC) qsort1.o -o qsort1

qsort1.o: qsort1.cc
	$(CC) $(CFLAGS) qsort1.cc -g


clean:
	rm -rf *.o *~ qsort1
	 


