# If you want to use this on your own machine, change CLASSDIR and/or INCLUDE and LIBS so
# that they point to the correct directories/library.

# CLASSDIR = $(HOME)
CLASSDIR = /home/plank/cs360
INCLUDE = -I$(CLASSDIR)/include
LIBS = $(CLASSDIR)/objs/libfdr.a
CC = gcc

EX = printwords tailanyf pipetest tail10-bad tail10-bad-print tail10-memory-leak tail10-good
all: $(EX) 
clean: 
	rm -f $(EX) *.o

pipetest: pipetest.o $(LIBS)
	$(CC) $(INCLUDE) -o pipetest pipetest.o $(LIBS)
printwords: printwords.o $(LIBS)
	$(CC) $(INCLUDE) -o printwords printwords.o $(LIBS)
tail10-good: tail10-good.o $(LIBS)
	$(CC) $(INCLUDE) -o tail10-good tail10-good.o $(LIBS)
tail10-bad: tail10-bad.o $(LIBS)
	$(CC) $(INCLUDE) -o tail10-bad tail10-bad.o $(LIBS)
tail10-bad-print: tail10-bad-print.o $(LIBS)
	$(CC) $(INCLUDE) -o tail10-bad-print tail10-bad-print.o $(LIBS)
tail10-memory-leak: tail10-memory-leak.o $(LIBS)
	$(CC) $(INCLUDE) -o tail10-memory-leak tail10-memory-leak.o $(LIBS)
goodword: goodword.o $(LIBS)
	$(CC) $(INCLUDE) -o goodword goodword.o $(LIBS)
badword: badword.o $(LIBS)
	$(CC) $(INCLUDE) -o badword badword.o $(LIBS)
tailanyf: tailanyf.o $(LIBS)
	$(CC) $(INCLUDE) -o tailanyf tailanyf.o $(LIBS)


.SUFFIXES: .c .o

.c.o: 
	$(CC) $(INCLUDE) -g  -c  $*.c

