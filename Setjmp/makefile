CC = gcc
INC = -I$(HOME)/include
DLIST = $(HOME)/lib/$(ARCH)/libfdr.a 

CFLAGS = $(INC) 

# +mkmake+ -- Everything after this line is automatically generated
EXECUTABLES = prime_12 sh4 sj1 sj2 sj3 two_alarm two_alarm_setjmp_2 two_alarm_setjmp_1 prime_1 prime_2 prime_12_opt sh4_opt

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	 $(CC) $(CFLAGS) -c $*.c


prime_1: prime_1.o
	 $(CC) $(CFLAGS) -o prime_1 prime_1.o

prime_2: prime_2.o $(DLIST)
	 $(CC) $(CFLAGS) -o prime_2 prime_2.o $(DLIST)

prime_12: prime_12.o $(DLIST)
	 $(CC) $(CFLAGS) -o prime_12 prime_12.o $(DLIST)

prime_12_opt: prime_12.c $(DLIST)
	 $(CC) $(CFLAGS) -O -o prime_12_opt prime_12.c $(DLIST)

two_alarm_setjmp_2: two_alarm_setjmp_2.o
	 $(CC) $(CFLAGS) -o two_alarm_setjmp_2 two_alarm_setjmp_2.o

two_alarm_setjmp_1: two_alarm_setjmp_1.o
	 $(CC) $(CFLAGS) -o two_alarm_setjmp_1 two_alarm_setjmp_1.o

two_alarm: two_alarm.o
	 $(CC) $(CFLAGS) -o two_alarm two_alarm.o


sh4: sh4.o
	$(CC) $(CFLAGS) -o sh4 sh4.o

sh4_opt: sh4.c
	$(CC) $(CFLAGS) -O -o sh4_opt sh4.c

sj1: sj1.o
	$(CC) $(CFLAGS) -o sj1 sj1.o

sj2: sj2.o
	$(CC) $(CFLAGS) -o sj2 sj2.o

sj3: sj3.o
	$(CC) $(CFLAGS) -o sj3 sj3.o
