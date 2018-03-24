CC = gcc
# +mkmake+ -- Everything after this line is automatically generated

EXECUTABLES = headsort pipe0 pipe1 pipe2 pipe3

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out output

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


headsort: headsort.c
	$(CC) $(CFLAGS) -o headsort headsort.c

pipe0: pipe0.c
	$(CC) $(CFLAGS) -o pipe0 pipe0.c

pipe1: pipe1.c
	$(CC) $(CFLAGS) -o pipe1 pipe1.c

pipe2: pipe2.c
	$(CC) $(CFLAGS) -o pipe2 pipe2.c

pipe3: pipe3.c
	$(CC) $(CFLAGS) -o pipe3 pipe3.c
