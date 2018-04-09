
EXECUTABLES = preempt1 preempt2 preempt3 \
              race2 race3 race1

CFLAGS = -I/home/plank/cs360/include
CSDIR = /home/plank/cs360
SOCKLIB = $(CSDIR)/objs/sockettome.o 
FIELDLIB = $(CSDIR)/objs/fields.o
RB = $(CSDIR)/objs/librb.a

CC = gcc

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


preempt1: preempt1.o
	$(CC) $(CFLAGS) -o preempt1 preempt1.o -lpthread

preempt2: preempt2.o
	$(CC) $(CFLAGS) -o preempt2 preempt2.o -lpthread

preempt3: preempt3.o
	$(CC) $(CFLAGS) -o preempt3 preempt3.o -lpthread

race1: race1.o
	$(CC) $(CFLAGS) -o race1 race1.o -lpthread

race2: race2.o
	$(CC) $(CFLAGS) -o race2 race2.o -lpthread

race3: race3.o
	$(CC) $(CFLAGS) -o race3 race3.o -lpthread

