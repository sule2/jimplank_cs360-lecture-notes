/* dphil_2_even_odd.c
   James S. Plank
   April, 2016
   CS360 - Systems Programming

   Even and Odd philosophers get their chopsticks in a different order.
 */

#include <stdio.h>
#include <pthread.h>
#include "dphil.h"

typedef struct {
  int num;
} MyPhil;

void *initialize_v(int phil_count) 
{
  MyPhil *p;

  p = (MyPhil *) malloc(sizeof(MyPhil));
  p->num = phil_count;

  return p; 
}

/* Even philosophers go right-left, and odd philosophers go left-right. */

void i_am_hungry(void *v, int philosopher) 
{
  MyPhil *p;

  p = (MyPhil *) v;

  if (philosopher % 2 == 0) {
    pick_up_chopstick(philosopher, philosopher);
    pick_up_chopstick(philosopher, (philosopher+1)%p->num);
  } else {
    pick_up_chopstick(philosopher, (philosopher+1)%p->num);
    pick_up_chopstick(philosopher, philosopher);
  }
}
void i_am_done_eating(void *v, int philosopher) 
{
  MyPhil *p;

  p = (MyPhil *) v;

  put_down_chopstick(philosopher, philosopher);
  put_down_chopstick(philosopher, (philosopher+1)%p->num);
}
