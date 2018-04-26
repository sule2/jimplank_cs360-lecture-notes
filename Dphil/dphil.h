/* dphil.h
   James S. Plank
   April, 2016
   CS360 - Systems Programming

   Header file for dining philosophers.
   
   The structure of this lecture is like a lab.  In this case, there is a driver program,
   called dphil_driver.c, which sets up the threads and drives the simulation.  
   There is one thread per philosopher, and a thread to monitor hunger time.  

   The driver program calls initialize_v(), where you allocate and initialize a (void *)
   that you will use to implement your dining philosopher's protocol.
   You will do so in your i_am_hungry() and i_am_done_eating() procedures.

   The threads go through the cycle of: (Think-Eat).  Thinking and Eating are implementing
   by calling sleep() or usleep().

   When a philosopher stops thinking, he/she becomes hungry, and
   wants to eat.  He/she calls i_am_hungry().  This is a procedure that
   you will implement to allocate the philosopher's chopsticks, using
   whatever protocol you desire.  I_am_hungry() should not return until
   the philosopher has the chopsticks.

   When a philosopher stops eating, he/she will go back to thinking.  Before doing so,
   he/she calls i_am_done_eating().  This is another procedure that you will write.  This
   will de-allocate the chopsticks, and do whatever else is required by your protocol.

   When a philosopher picks up a chopstick inside i_am_hungry(), he/she needs to call
   pick_up_chopstick().  That is implemented in dphil_driver.c.  It will make the proper
   print statements, and it will also insure that the philosopher is in the "hungry" state,
   and will block until the chopstick is not really available.  

   When a philosopher puts a chopstick down inside i_am_done_eating(), he/she needs to
   call put_down_chopstick().  This is also implemented in dphil_driver.c.  It will make
   the proper print statements, do some double-checking, and will unblock any threads that
   are blocking on pick_up_chopstick().

   dphil_driver.c employs a global variable to maintain its state.  You are not allowed
   to access this -- any information that you need to implement your protocol, you need
   to put in your (void *).
 */

#include <stdlib.h>
#include <string.h>

/* Again, these are implemented inside dphil_driver.c.  You can't modify these. */

extern void pick_up_chopstick(int philosopher, int stick);
extern void put_down_chopstick(int philosopher, int stick);

/* You have to write these. */

extern void *initialize_v(int phil_count);
extern void i_am_hungry(void *v, int philosopher);
extern void i_am_done_eating(void *v, int philosopher);
