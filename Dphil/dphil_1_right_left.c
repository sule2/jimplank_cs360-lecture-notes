/* dphil_1_right_left.c
   James S. Plank
   April, 2016
   CS360 - Systems Programming

   Solution #1: Each philosopher grabs his/her right chopstick, and then the left one.
 */

#include <stdio.h>
#include <pthread.h>
#include "dphil.h"

/* The only information we need is the number of philosophers.
   This is because we have to calculate the chopstick numbers from
   the philosopher id. */

typedef struct {
  int num;
} MyPhil;

/* Store the number of philosophers in the (void *). */

void *initialize_v(int phil_count) 
{
  MyPhil *p;

  p = (MyPhil *) malloc(sizeof(MyPhil));
  p->num = phil_count;

  return p; 
}

/* These are straightforward, simply picking up and putting down
   chopsticks, first right, then left. */

void i_am_hungry(void *v, int philosopher) 
{
  MyPhil *p;

  p = (MyPhil *) v;

  pick_up_chopstick(philosopher, philosopher);
  pick_up_chopstick(philosopher, (philosopher+1)%p->num);
}

void i_am_done_eating(void *v, int philosopher) 
{
  MyPhil *p;

  p = (MyPhil *) v;

  put_down_chopstick(philosopher, philosopher);
  put_down_chopstick(philosopher, (philosopher+1)%p->num);
}
