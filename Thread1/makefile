
EXECUTABLES = print4 hw p4a p4b p4c p4d iloop th_telnet real_minitalk

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) -c $*.c


hw: hw.o
	$(CC) -o hw hw.o -lpthread

real_minitalk: real_minitalk.o sockettome.o
	$(CC) -o real_minitalk real_minitalk.o sockettome.o -lpthread

th_telnet: th_telnet.o sockettome.o
	$(CC) -o th_telnet th_telnet.o sockettome.o -lpthread

print4: print4.o
	$(CC) -o print4 print4.o -lpthread

p4a: p4a.o
	$(CC) -o p4a p4a.o -lpthread

p4b: p4b.o
	$(CC) -o p4b p4b.o -lpthread

p4c: p4c.o
	$(CC) -o p4c p4c.o -lpthread

p4d: p4d.o
	$(CC) -o p4d p4d.o -lpthread

iloop: iloop.o
	$(CC) -o iloop iloop.o -lpthread
