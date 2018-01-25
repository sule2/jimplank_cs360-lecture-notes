# At home, I use the following:
# INCLUDE = -I$(HOME)/include
# LIBDIR = $(HOME)/lib

CLASSDIR = /home/plank/cs360
INCLUDE = -I$(CLASSDIR)/include
LIBDIR = $(CLASSDIR)/objs
CC = gcc
LIBS = $(LIBDIR)/libfdr.a
CFLAGS = -g $(INCLUDE)
ALL = strsort strrsort1 strrsort2 strisort nsort strusort \
      nsort2 nsort3 golf ni_sort1 ni_sort2 ni_sort3

all: $(ALL)

clean:
	rm -f *.o core $(ALL)

strsort: strsort.o 
	$(CC) $(CFLAGS) -o strsort strsort.o $(LIBS)

strrsort1: strrsort1.o 
	$(CC) $(CFLAGS) -o strrsort1 strrsort1.o $(LIBS)

strrsort2: strrsort2.o 
	$(CC) $(CFLAGS) -o strrsort2 strrsort2.o $(LIBS)

strusort: strusort.o 
	$(CC) $(CFLAGS) -o strusort strusort.o $(LIBS)

strisort: strisort.o 
	$(CC) $(CFLAGS) -o strisort strisort.o $(LIBS)

nsort: nsort.o 
	$(CC) $(CFLAGS) -o nsort nsort.o $(LIBS)

nsort2: nsort2.o 
	$(CC) $(CFLAGS) -o nsort2 nsort2.o $(LIBS)

nsort3: nsort3.o 
	$(CC) $(CFLAGS) -o nsort3 nsort3.o $(LIBS)

ni_sort1: ni_sort1.o 
	$(CC) $(CFLAGS) -o ni_sort1 ni_sort1.o $(LIBS)

ni_sort2: ni_sort2.o 
	$(CC) $(CFLAGS) -o ni_sort2 ni_sort2.o $(LIBS)

ni_sort3: ni_sort3.o 
	$(CC) $(CFLAGS) -o ni_sort3 ni_sort3.o $(LIBS)

golf: golf.o 
	$(CC) $(CFLAGS) -o golf golf.o $(LIBS)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


