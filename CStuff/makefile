CC = gcc

# +mkmake+ -- Everything after this line is automatically generated

EXECUTABLES = p1 p3 p4 p5 p8 p9 pa pc pd pe id1 id2 id3 id5 id5a id5b pm endian

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .cpp 

.c:
	$(CC) $(CFLAGS) -o $* $*.c

.cpp:
	g++ -o $* $*.cpp

