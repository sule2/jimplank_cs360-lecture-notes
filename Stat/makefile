CC = gcc
CFLAGS  =       -g -I/home/plank/cs360/include
LIB  = /home/plank/cs360/objs/libfdr.a

EXECUTABLES = ls1 ls2 ls3 ls4 ls5 ls5a ls6 lec_soft

all: $(EXECUTABLES) 

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


ls1: ls1.o
	$(CC) $(CFLAGS) -o ls1 ls1.o 

ls2: ls2.o
	$(CC) $(CFLAGS) -o ls2 ls2.o 

ls3: ls3.o
	$(CC) $(CFLAGS) -o ls3 ls3.o 

ls4: ls4.o
	$(CC) $(CFLAGS) -o ls4 ls4.o $(LIB)

ls5: ls5.o
	$(CC) $(CFLAGS) -o ls5 ls5.o $(LIB)

ls5a: ls5a.o
	$(CC) $(CFLAGS) -o ls5a ls5a.o $(LIB)

ls6: ls6.o
	$(CC) $(CFLAGS) -o ls6 ls6.o $(LIB)

lec_soft: lecture.html
	ln -s lecture.html lec_soft
