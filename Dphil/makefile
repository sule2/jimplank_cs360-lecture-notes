
EXECUTABLES = dphil_0_compiles \
          dphil_1_right_left \
          dphil_1a_right_left \
          dphil_2_even_odd \
          dphil_3_hold_and_wait \
          dphil_4_global_list \
          dphil_5_take_a_number \
          dphil_6_hybrid \
          phil_step

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) -c $*.c

dphil_driver.o: dphil.h

dphil_0_compiles:         dphil.h
dphil_1_right_left:       dphil.h
dphil_1a_right_left:      dphil.h
dphil_2_even_odd:         dphil.h
dphil_3_hold_and_wait:    dphil.h
dphil_4_global_list:      dphil.h
dphil_5_take_a_number:    dphil.h
dphil_6_hybrid:           dphil.h

phil_step: phil_step.cpp
	g++ -o phil_step phil_step.cpp

dphil_0_compiles: dphil_0_compiles.o dphil_driver.o
	$(CC) -o dphil_0_compiles dphil_0_compiles.o dphil_driver.o -lpthread

dphil_1_right_left: dphil_1_right_left.o dphil_driver.o
	$(CC) -o dphil_1_right_left dphil_1_right_left.o dphil_driver.o -lpthread

dphil_1a_right_left: dphil_1a_right_left.o dphil_driver.o
	$(CC) -o dphil_1a_right_left dphil_1a_right_left.o dphil_driver.o -lpthread

dphil_2_even_odd: dphil_2_even_odd.o dphil_driver.o
	$(CC) -o dphil_2_even_odd dphil_2_even_odd.o dphil_driver.o -lpthread

dphil_3_hold_and_wait: dphil_3_hold_and_wait.o dphil_driver.o
	$(CC) -o dphil_3_hold_and_wait dphil_3_hold_and_wait.o dphil_driver.o -lpthread

dphil_4_global_list: dphil_4_global_list.o dphil_driver.o
	$(CC) -o dphil_4_global_list dphil_4_global_list.o dphil_driver.o -lpthread

dphil_5_take_a_number: dphil_5_take_a_number.o dphil_driver.o
	$(CC) -o dphil_5_take_a_number dphil_5_take_a_number.o dphil_driver.o -lpthread

dphil_6_hybrid: dphil_6_hybrid.o dphil_driver.o
	$(CC) -o dphil_6_hybrid dphil_6_hybrid.o dphil_driver.o -lpthread

