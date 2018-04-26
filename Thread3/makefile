CFLAGS = -I/home/plank/cs360/include
CSDIR = /home/plank/cs360
SOCKLIB = $(CSDIR)/objs/sockettome.o 
LIBS = $(CSDIR)/objs/libfdr.a  $(SOCKLIB)

CC = gcc 

# +mkmake+ -- Everything after this line is automatically generated

EXECUTABLES = inputgen ssnserver ssnserver1 inclient ssnserver2 \
              ssnserver3 ssnserver4 ssnserver5 

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


inputgen: inputgen.o 
	$(CC) $(CFLAGS) -o inputgen inputgen.o $(LIBS)

inclient: inclient.o 
	$(CC) $(CFLAGS) -o inclient inclient.o $(LIBS) -lpthread

ssnserver: ssnserver.o
	$(CC) $(CFLAGS) -o ssnserver ssnserver.o $(LIBS)

ssnserver1: ssnserver1.o
	$(CC) $(CFLAGS) -o ssnserver1 ssnserver1.o $(LIBS) -lpthread

ssnserver2: ssnserver2.o
	$(CC) $(CFLAGS) -o ssnserver2 ssnserver2.o $(LIBS) -lpthread

ssnserver3: ssnserver3.o
	$(CC) $(CFLAGS) -o ssnserver3 ssnserver3.o $(LIBS) -lpthread

ssnserver4: ssnserver4.o
	$(CC) $(CFLAGS) -o ssnserver4 ssnserver4.o $(LIBS) -lpthread

ssnserver5: ssnserver5.o
	$(CC) $(CFLAGS) -o ssnserver5 ssnserver5.o $(LIBS) -lpthread
