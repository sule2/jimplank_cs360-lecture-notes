# If you want to use this on your own machine, change CLASSDIR and/or INCLUDE and LIBS so
# that they point to the correct directories/library.

CLASSDIR = /home/plank/cs360
INCLUDE = -I$(CLASSDIR)/include
CFLAGS = -g $(INCLUDE)
LIBS = $(CLASSDIR)/objs/libfdr.a

EXECUTABLES = jval_ex jval_ex2 badavg goodavg
CC = gcc

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


jval_ex: jval_ex.o
	$(CC) $(CFLAGS) -o jval_ex jval_ex.o $(LIBS)

jval_ex2: jval_ex2.o
	$(CC) $(CFLAGS) -o jval_ex2 jval_ex2.o $(LIBS)

badavg: badavg.o
	$(CC) $(CFLAGS) -o badavg badavg.o $(LIBS)

goodavg: goodavg.o
	$(CC) $(CFLAGS) -o goodavg goodavg.o

