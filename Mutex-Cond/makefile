INCLUDE = /home/plank/cs360/include
LIBFDR = /home/plank/cs360/objs/libfdr.a
LPTHREAD = -lpthread

ALL = mutex_example_1 \
      mutex_example_2 \
      mutex_example_3 \
      prime_example_1 \
      prime_example_2 \
      prime_example_3 \
      prime_example_4 \
      prime_example_5 \
      prime_example_6

all: $(ALL)

clean:
	rm -f $(ALL)

mutex_example_1: mutex_example_1.c
	gcc -o mutex_example_1 mutex_example_1.c $(LPTHREAD)

mutex_example_2: mutex_example_2.c
	gcc -o mutex_example_2 mutex_example_2.c $(LPTHREAD)

mutex_example_3: mutex_example_3.c
	gcc -o mutex_example_3 mutex_example_3.c $(LPTHREAD)

prime_example_1: prime_example_1.c
	gcc -o prime_example_1 prime_example_1.c $(LPTHREAD)

prime_example_2: prime_example_2.c 
	gcc -o prime_example_2 -I$(INCLUDE) prime_example_2.c $(LIBFDR) $(LPTHREAD)

prime_example_3: prime_example_3.c 
	gcc -o prime_example_3 -I$(INCLUDE) prime_example_3.c $(LIBFDR) $(LPTHREAD)

prime_example_4: prime_example_4.c 
	gcc -o prime_example_4 -I$(INCLUDE) prime_example_4.c $(LIBFDR) $(LPTHREAD)

prime_example_5: prime_example_5.c 
	gcc -o prime_example_5 -I$(INCLUDE) prime_example_5.c $(LIBFDR) $(LPTHREAD)

prime_example_6: prime_example_6.c 
	gcc -o prime_example_6 -I$(INCLUDE) prime_example_6.c $(LIBFDR) $(LPTHREAD)

