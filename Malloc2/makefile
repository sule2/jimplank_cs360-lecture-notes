CC = gcc

# +mkmake+ -- Everything after this line is automatically generated

EXECUTABLES = badfree

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


badfree: badfree.o
	$(CC) $(CFLAGS) -o badfree badfree.o
