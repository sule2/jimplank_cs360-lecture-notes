# +mkmake+ -- Everything after this line is automatically generated

EXECUTABLES = quiz ptr1 sptr cptr dptr

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


ptr1: ptr1.o
	$(CC) $(CFLAGS) -o ptr1 ptr1.o

sptr: sptr.o
	$(CC) $(CFLAGS) -o sptr sptr.o

dptr: dptr.o
	$(CC) $(CFLAGS) -o dptr dptr.o

cptr: cptr.o
	$(CC) $(CFLAGS) -o cptr cptr.o

quiz: quiz.o
	$(CC) $(CFLAGS) -o quiz quiz.o

