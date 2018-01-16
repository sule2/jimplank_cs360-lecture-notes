CC = gcc

EXECUTABLES = id1 id2 id3 id5 id5a id5b id6 p1 p2a

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .cpp 

.c:
	$(CC) $(CFLAGS) -o $* $*.c

.cpp:
	g++ -o $* $*.cpp

