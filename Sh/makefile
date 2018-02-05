CC = gcc

EXECUTABLES = badbadcode dont_admit_i_taught_you_this

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

badbadcode: badbadcode.o
	$(CC) $(CFLAGS) -o badbadcode badbadcode.o

dont_admit_i_taught_you_this: dont_admit_i_taught_you_this.o
	$(CC) $(CFLAGS) -o dont_admit_i_taught_you_this dont_admit_i_taught_you_this.o

