CC = gcc
CFLAGS = 

EXECUTABLES = sh1 sh1a sh1b sh2 sh3 sh3a sh3b sh3c sh4 sh5 sigpipe_1 sigpipe_2 \
              sort_compare instaclose call_exec

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


sigpipe_1: sigpipe_1.c
	$(CC) $(CFLAGS) -o sigpipe_1 sigpipe_1.c

sigpipe_2: sigpipe_2.c
	$(CC) $(CFLAGS) -o sigpipe_2 sigpipe_2.c

sh1: sh1.c
	$(CC) $(CFLAGS) -o sh1 sh1.c

sh1a: sh1a.c
	$(CC) $(CFLAGS) -o sh1a sh1a.c

sh1b: sh1b.c
	$(CC) $(CFLAGS) -o sh1b sh1b.c

sh2: sh2.c
	$(CC) $(CFLAGS) -o sh2 sh2.c

sh3: sh3.c
	$(CC) $(CFLAGS) -o sh3 sh3.c

sh3a: sh3a.c
	$(CC) $(CFLAGS) -o sh3a sh3a.c

sh3b: sh3b.c
	$(CC) $(CFLAGS) -o sh3b sh3b.c

sh3c: sh3c.c
	$(CC) $(CFLAGS) -o sh3c sh3c.c

sh4: sh4.c
	$(CC) $(CFLAGS) -o sh4 sh4.c

sh5: sh5.c
	$(CC) $(CFLAGS) -o sh5 sh5.c

sort_compare: sort_compare.c
	$(CC) $(CFLAGS) -o sort_compare sort_compare.c

call_exec: call_exec.c
	$(CC) $(CFLAGS) -o call_exec call_exec.c

instaclose: instaclose.c
	$(CC) $(CFLAGS) -o instaclose instaclose.c
