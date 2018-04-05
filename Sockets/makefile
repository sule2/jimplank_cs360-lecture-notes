CC = gcc
CFLAGS = -g 
SOCKLIB = sockettome.o


EXECUTABLES = client1 serve1 serve2 alternate minitalk1 minitalk2 minitalk3

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .c
.c.c:
	$(CC) $(CFLAGS) -c $*.c


client1: client1.c sockettome.o
	$(CC) $(CFLAGS) -o client1 client1.c $(SOCKLIB)

serve2: serve2.c sockettome.o
	$(CC) $(CFLAGS) -o serve2 serve2.c $(SOCKLIB)

serve1: serve1.c sockettome.o
	$(CC) $(CFLAGS) -o serve1 serve1.c $(SOCKLIB)

alternate: alternate.c sockettome.o
	$(CC) $(CFLAGS) -o alternate alternate.c $(SOCKLIB)

minitalk1: minitalk1.c sockettome.o
	$(CC) $(CFLAGS) -o minitalk1 minitalk1.c $(SOCKLIB)

minitalk2: minitalk2.c sockettome.o
	$(CC) $(CFLAGS) -o minitalk2 minitalk2.c $(SOCKLIB)

minitalk3: minitalk3.c sockettome.o
	$(CC) $(CFLAGS) -o minitalk3 minitalk3.c $(SOCKLIB)

