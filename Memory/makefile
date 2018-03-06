CC = gcc
# +mkmake+ -- Everything after this line is automatically generated

EXECUTABLES = breakstack1 breakstack2 testaddr1 testaddr2 testaddr3 testaddr4 \
              testaddr3a breakstack3

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

CFLAGS = 

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


breakstack1: breakstack1.o
	$(CC) $(CFLAGS) -o breakstack1 breakstack1.o

breakstack2: breakstack2.o
	$(CC) $(CFLAGS) -o breakstack2 breakstack2.o

breakstack3: breakstack3.o
	$(CC) $(CFLAGS) -o breakstack3 breakstack3.o

testaddr1: testaddr1.o
	$(CC) $(CFLAGS) -o testaddr1 testaddr1.o

testaddr2: testaddr2.o
	$(CC) $(CFLAGS) -o testaddr2 testaddr2.o

testaddr3: testaddr3.o
	$(CC) $(CFLAGS) -o testaddr3 testaddr3.o

testaddr3a: testaddr3a.o
	$(CC) $(CFLAGS) -o testaddr3a testaddr3a.o

testaddr4: testaddr4.o
	$(CC) $(CFLAGS) -o testaddr4 testaddr4.o
