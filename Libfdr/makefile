# Libraries for fields, doubly-linked lists and red-black trees.
# Copyright (C) 2018 James S. Plank

CFLAGS = -O3

all: libfdr.a

OBJS = dllist.o fields.o jval.o jrb.o

libfdr.a: $(OBJS)
	ar ru libfdr.a $(OBJS)
	ranlib libfdr.a 

clean:
	rm -f core *.o libfdr.a

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

