CC = gcc
# +mkmake+ -- Everything after this line is automatically generated

EXECUTABLES = segfault look_at_memory

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

CFLAGS = 

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

segfault: segfault.c
	$(CC) $(CFLAGS) -o segfault segfault.c

look_at_memory: look_at_memory.c
	$(CC) $(CFLAGS) -o look_at_memory look_at_memory.c

