CC = gcc

EXECUTABLES = endian p3 p4 p5 p5a p8 p9 pa pc pd pe pm

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) p8-32 a.out

.SUFFIXES: .c .cpp 

.c:
	$(CC) $(CFLAGS) -o $* $*.c

.cpp:
	g++ -o $* $*.cpp

