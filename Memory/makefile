CC = gcc
# +mkmake+ -- Everything after this line is automatically generated

EXECUTABLES = segfault look_at_memory mess_with_memory break_the_stack break_the_heap

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

CFLAGS = 

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

segfault: segfault.c
	$(CC) $(CFLAGS) -o segfault segfault.c

look_at_memory: look_at_memory.c
	$(CC) $(CFLAGS) -o look_at_memory look_at_memory.c

mess_with_memory: mess_with_memory.c
	$(CC) $(CFLAGS) -o mess_with_memory mess_with_memory.c

break_the_stack: break_the_stack.c
	$(CC) $(CFLAGS) -o break_the_stack break_the_stack.c

break_the_heap: break_the_heap.c
	$(CC) $(CFLAGS) -o break_the_heap break_the_heap.c

