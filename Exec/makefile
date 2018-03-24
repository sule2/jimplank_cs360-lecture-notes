CC = gcc
# +mkmake+ -- Everything after this line is automatically generated

EXECUTABLES = exec1 exec2 execcat1 execcat2 execcat3 execcat4 forkwait0 forkwait1 forkwait2 forkwait3 forkwait4 forkwait5 multichild

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


exec1: exec1.c
	$(CC) $(CFLAGS) -o exec1 exec1.c

exec2: exec2.c
	$(CC) $(CFLAGS) -o exec2 exec2.c

execcat1: execcat1.c
	$(CC) $(CFLAGS) -o execcat1 execcat1.c

execcat2: execcat2.c
	$(CC) $(CFLAGS) -o execcat2 execcat2.c

execcat3: execcat3.c
	$(CC) $(CFLAGS) -o execcat3 execcat3.c

multichild: multichild.c
	$(CC) $(CFLAGS) -o multichild multichild.c

execcat4: execcat4.c
	$(CC) $(CFLAGS) -o execcat4 execcat4.c

forkwait0: forkwait0.c
	$(CC) $(CFLAGS) -o forkwait0 forkwait0.c

forkwait1: forkwait1.c
	$(CC) $(CFLAGS) -o forkwait1 forkwait1.c

forkwait2: forkwait2.c
	$(CC) $(CFLAGS) -o forkwait2 forkwait2.c

forkwait3: forkwait3.c
	$(CC) $(CFLAGS) -o forkwait3 forkwait3.c

forkwait5: forkwait5.c
	$(CC) $(CFLAGS) -o forkwait5 forkwait5.c

forkwait4: forkwait4.c
	$(CC) $(CFLAGS) -o forkwait4 forkwait4.c
