
CC = gcc 

# +mkmake+ -- Everything after this line is automatically generated

EXECUTABLES = ps1 ps2 ps3 ps4 ps5

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

printqsim.o: printqsim.h

ps1.o: printqsim.h printqsim.o
ps1: ps1.o 
	$(CC) $(CFLAGS) -o ps1 printqsim.o ps1.o -lpthread

ps2.o: printqsim.h printqsim.o
ps2: ps2.o 
	$(CC) $(CFLAGS) -o ps2 printqsim.o ps2.o -lpthread

ps3.o: printqsim.h printqsim.o
ps3: ps3.o 
	$(CC) $(CFLAGS) -o ps3 printqsim.o ps3.o -lpthread

ps4.o: printqsim.h printqsim.o
ps4: ps4.o 
	$(CC) $(CFLAGS) -o ps4 printqsim.o ps4.o -lpthread

ps5.o: printqsim.h printqsim.o
ps5: ps5.o 
	$(CC) $(CFLAGS) -o ps5 printqsim.o ps5.o -lpthread
