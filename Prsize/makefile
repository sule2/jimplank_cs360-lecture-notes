CC = gcc

# When I'm at home, I uncomment these and comment the other CFLAGS/LIB defintions.
# CFLAGS  =       -g -I$(HOME)/include
# LIB = $(HOME)/lib/libfdr.a

CFLAGS  =       -g -I/home/plank/cs360/include
LIB = /home/plank/cs360/objs/libfdr.a


EXECUTABLES = prsize1 prsize2 prsize3 prsize3a prsize4 prsize5 prsize6 prsize7 prsize7a prsize8

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


prsize1: prsize1.o
	$(CC) $(CFLAGS) -o prsize1 prsize1.o

prsize2: prsize2.o
	$(CC) $(CFLAGS) -o prsize2 prsize2.o

prsize3: prsize3.o
	$(CC) $(CFLAGS) -o prsize3 prsize3.o

prsize3a: prsize3a.o
	$(CC) $(CFLAGS) -o prsize3a prsize3a.o

prsize4: prsize4.o
	$(CC) $(CFLAGS) -o prsize4 prsize4.o

prsize5: prsize5.o
	$(CC) $(CFLAGS) -o prsize5 prsize5.o

prsize6: prsize6.o
	$(CC) $(CFLAGS) -o prsize6 prsize6.o $(LIB)

prsize7: prsize7.o
	$(CC) $(CFLAGS) -o prsize7 prsize7.o $(LIB)

prsize7a: prsize7a.o
	$(CC) $(CFLAGS) -o prsize7a prsize7a.o $(LIB)

prsize8: prsize8.o
	$(CC) $(CFLAGS) -o prsize8 prsize8.o $(LIB)
