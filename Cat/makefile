
all: simpcat1a simpcat1 simpcat2 simpcat3 simpcat4 simpcat5 cat1 cat2 fullcat large.txt

CC = gcc
INCLUDE = .

simpcat1: simpcat1.o
	$(CC) -o simpcat1 -g simpcat1.o
	
simpcat1a: simpcat1a.o
	$(CC) -o simpcat1a -g simpcat1a.o
	
simpcat2: simpcat2.o
	$(CC) -o simpcat2 -g simpcat2.o
	
simpcat3: simpcat3.o
	$(CC) -o simpcat3 -g simpcat3.o

simpcat4: simpcat4.o
	$(CC) -o simpcat4 -g simpcat4.o

simpcat5: simpcat5.o
	$(CC) -o simpcat5 -g simpcat5.o

cat1: cat1.o
	$(CC) -o cat1 -g cat1.o
	
cat2: cat2.o
	$(CC) -o cat2 -g cat2.o
	
fullcat: fullcat.o
	$(CC) -o fullcat -g fullcat.o
	
large.txt:
	echo 25000000 | awk '{ for (i = 0; i < $$1/10; i++) print "123456789" }' > large.txt

.SUFFIXES: .c .o

.c.o: 
	$(CC) -g -c $*.c

clean:
	rm -f *.o simpcat1a simpcat1 simpcat2 simpcat3 simpcat4 simpcat5 \
                  cat1 cat2 fullcat core large.txt tmp1 tmp2 tmp3
