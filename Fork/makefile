CC = gcc
# +mkmake+ -- Everything after this line is automatically generated

EXECUTABLES = showpid simpfork simpfork2 simpfork3 simpfork4 forkbomb1 forkbomb2

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


showpid: showpid.c
	$(CC) $(CFLAGS) -o showpid showpid.c

simpfork: simpfork.c
	$(CC) $(CFLAGS) -o simpfork simpfork.c

simpfork2: simpfork2.c
	$(CC) $(CFLAGS) -o simpfork2 simpfork2.c

simpfork3: simpfork3.c
	$(CC) $(CFLAGS) -o simpfork3 simpfork3.c

simpfork4: simpfork4.c
	$(CC) $(CFLAGS) -o simpfork4 simpfork4.c

forkbomb1: forkbomb1.c
	$(CC) $(CFLAGS) -o forkbomb1 forkbomb1.c

forkbomb2: forkbomb2.c
	$(CC) $(CFLAGS) -o forkbomb2 forkbomb2.c
