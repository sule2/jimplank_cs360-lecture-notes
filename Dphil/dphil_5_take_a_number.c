/* dphil_3_hold_and_wait.c
   James S. Plank
   April, 2016
   CS360 - Systems Programming

   Only get the chopsticks if both are available.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "dphil.h"

#define EATING 0
#define THINKING 0x7fffffff

/* Here is new structure: */

typedef struct {
  int num;
  pthread_mutex_t *lock;                 /* This is so that you can look at the chopsticks. */
  pthread_cond_t **blocked_philosophers; /* Block if either chopstick is not available. */
  int *stick_states;                     /* This is how you monitor the chopsticks. */
  int *hunger;
  int counter;
} MyPhil;                                /* 'U' means taken.  'D' means available. */


void *initialize_v(int phil_count) 
{
  MyPhil *p;
  int i;

  p = (MyPhil *) malloc(sizeof(MyPhil));
  p->counter = 1;
  p->num = phil_count;
  p->lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(p->lock, NULL);
  p->blocked_philosophers = (pthread_cond_t **) malloc(sizeof(pthread_cond_t *)*p->num);
  p->stick_states = (int *) malloc(sizeof(int)*p->num);
  p->hunger = (int *) malloc(sizeof(int)*p->num);
  for (i = 0; i < p->num; i++) {
    p->blocked_philosophers[i] = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
    pthread_cond_init(p->blocked_philosophers[i], NULL);
    p->stick_states[i] = 'D';
    p->hunger[i] = THINKING;
  }
  return p; 
}

void i_am_hungry(void *v, int philosopher) 
{
  MyPhil *p;
  int stick1, stick2;
  int left, right;

  p = (MyPhil *) v;
  stick1 = philosopher;
  stick2 = (philosopher+1)%p->num;
  left = (philosopher+1)%p->num;
  right = (philosopher+p->num-1)%p->num;
  p->hunger[philosopher] = p->counter;
  p->counter++;

  /* While either chopstick is in use, block. */

  pthread_mutex_lock(p->lock);
  while (p->hunger[philosopher] > p->hunger[left] ||
         p->hunger[philosopher] > p->hunger[right]) {
    pthread_cond_wait(p->blocked_philosophers[philosopher], p->lock);
  }

  /* Now, both chopsticks are available.  
     We hold the lock to make sure that no other philosopher gets our chopsticks
     while we are picking up chopsticks. */

  pick_up_chopstick(philosopher, philosopher);
  pick_up_chopstick(philosopher, (philosopher+1)%p->num);

  p->stick_states[stick1] = 'U';
  p->stick_states[stick2] = 'U';
  p->hunger[philosopher] = EATING;
  pthread_mutex_unlock(p->lock);
}

void i_am_done_eating(void *v, int philosopher) 
{
  MyPhil *p;
  int stick1, stick2;
  int leftp, rightp;

  p = (MyPhil *) v;
  stick1 = philosopher;
  stick2 = (philosopher+1)%p->num;
  leftp = (philosopher+p->num-1)%p->num;
  rightp = stick2;

  pthread_mutex_lock(p->lock);
  put_down_chopstick(philosopher, philosopher);
  put_down_chopstick(philosopher, (philosopher+1)%p->num);
  p->stick_states[stick1] = 'D';
  p->stick_states[stick2] = 'D';

  /* After we put down out chopsticks, we need to signal adjacent philosophers. */

  p->hunger[philosopher] = THINKING;
  pthread_cond_signal(p->blocked_philosophers[leftp]);
  pthread_cond_signal(p->blocked_philosophers[rightp]);
  pthread_mutex_unlock(p->lock);
}
