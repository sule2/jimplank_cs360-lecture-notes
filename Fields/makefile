# If you want to use this on your own machine, change CLASSDIR and/or INCLUDE and LIBS so
# that they point to the correct directories/library.

CLASSDIR = /home/plank/cs360
INCLUDE = -I$(CLASSDIR)/include
LIBS = $(CLASSDIR)/objs/libfdr.a
CC = gcc

EX = printwords goodword badword tailanyf pipetest
all: $(EX) 
clean: 
	rm -f $(EX) *.o

pipetest: pipetest.o $(LIBS)
	$(CC) $(INCLUDE) -o pipetest pipetest.o $(LIBS)
printwords: printwords.o $(LIBS)
	$(CC) $(INCLUDE) -o printwords printwords.o $(LIBS)
goodword: goodword.o $(LIBS)
	$(CC) $(INCLUDE) -o goodword goodword.o $(LIBS)
badword: badword.o $(LIBS)
	$(CC) $(INCLUDE) -o badword badword.o $(LIBS)
tailanyf: tailanyf.o $(LIBS)
	$(CC) $(INCLUDE) -o tailanyf tailanyf.o $(LIBS)


.SUFFIXES: .c .o

.c.o: 
	$(CC) $(INCLUDE) -g  -c  $*.c

