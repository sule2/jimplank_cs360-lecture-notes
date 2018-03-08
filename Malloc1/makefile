CC = gcc -m32

all_files: all

EXECUTABLES = fb2 fb2a fb3 fb3a fb4

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

fb2: fb2.o
	$(CC) $(CFLAGS) -o fb2 fb2.o

fb2a: fb2a.o
	$(CC) $(CFLAGS) -o fb2a fb2a.o

fb3: fb3.o
	$(CC) $(CFLAGS) -o fb3 fb3.o

fb3a: fb3a.o
	$(CC) $(CFLAGS) -o fb3a fb3a.o

fb4: fb4.o
	$(CC) $(CFLAGS) -o fb4 fb4.o
