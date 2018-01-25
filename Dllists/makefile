CC = gcc

# When I do this at home, I use the following:
# INCLUDE = $(HOME)/include
# LIBDIR = $(HOME)/lib

INCLUDE = -I/home/plank/cs360/include
LIBDIR = /home/plank/cs360/objs
LIBS = $(LIBDIR)/libfdr.a
CFLAGS = -g $(INCLUDE)
ALL = dllreverse dlltail cos

all: $(ALL)

clean:
	rm -f *.o core $(ALL)

dllreverse: dllreverse.o
	$(CC) $(CFLAGS) -o dllreverse dllreverse.o $(LIBS)

cos: cos.o
	$(CC) $(CFLAGS) -o cos cos.o $(LIBS)

dlltail: dlltail.o
	$(CC) $(CFLAGS) -o dlltail dlltail.o $(LIBS)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


