INCLUDE = /home/plank/cs360/include
LIBFDR = /home/plank/cs360/objs/libfdr.a

# INCLUDE = $(HOME)/include
# LIBFDR = $(HOME)/lib/libfdr.a

LPTHREAD = -lpthread

ALL = mutex_example_1 \
      mutex_example_2 \
      mutex_example_3 \
      prime_1_simple \
      prime_2_output_thread \
      prime_3_fix_end \
      prime_4_input_thread \

all: $(ALL)

clean:
	rm -f $(ALL)

mutex_example_1: mutex_example_1.c
	gcc -o mutex_example_1 mutex_example_1.c $(LPTHREAD)

mutex_example_2: mutex_example_2.c
	gcc -o mutex_example_2 mutex_example_2.c $(LPTHREAD)

mutex_example_3: mutex_example_3.c
	gcc -o mutex_example_3 mutex_example_3.c $(LPTHREAD)

prime_1_simple: prime_1_simple.c
	gcc -o prime_1_simple prime_1_simple.c $(LPTHREAD)

prime_2_output_thread: prime_2_output_thread.c 
	gcc -o prime_2_output_thread -I$(INCLUDE) prime_2_output_thread.c $(LIBFDR) $(LPTHREAD)

prime_3_fix_end: prime_3_fix_end.c 
	gcc -o prime_3_fix_end -I$(INCLUDE) prime_3_fix_end.c $(LIBFDR) $(LPTHREAD)

prime_4_input_thread: prime_4_input_thread.c 
	gcc -o prime_4_input_thread -I$(INCLUDE) prime_4_input_thread.c $(LIBFDR) $(LPTHREAD)

