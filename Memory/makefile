CC = gcc
# +mkmake+ -- Everything after this line is automatically generated

EXECUTABLES = segfault testaddr1 testaddr2 testaddr3 testaddr4 \
              testaddr3a breakstack3

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

CFLAGS = 

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

segfault: segfault.c
	$(CC) $(CFLAGS) -o segfault segfault.c

