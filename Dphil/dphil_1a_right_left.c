/* dphil_1a_left_right.c
   James S. Plank
   April, 2016
   CS360 - Systems Programming

   Adding a delay to dphil_1_left_right.c so that it's easier to have deadlock.
 */

#include <stdio.h>
#include <unistd.h>
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

void i_am_hungry(void *v, int philosopher) 
{
  MyPhil *p;

  p = (MyPhil *) v;

  pick_up_chopstick(philosopher, philosopher);
  sleep(3);
  pick_up_chopstick(philosopher, (philosopher+1)%p->num);
}
void i_am_done_eating(void *v, int philosopher) 
{
  MyPhil *p;

  p = (MyPhil *) v;

  put_down_chopstick(philosopher, philosopher);
  put_down_chopstick(philosopher, (philosopher+1)%p->num);
}
