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

/* Here is new structure: */

typedef struct {
  int num;
  pthread_mutex_t *lock;                 /* This is so that you can look at the chopsticks. */
  pthread_cond_t **blocked_philosophers; /* Block if either chopstick is not available. */
  int *stick_states;                     /* This is how you monitor the chopsticks. */
} MyPhil;                                /* 'U' means taken.  'D' means available. */

void *initialize_v(int phil_count) 
{
  MyPhil *p;
  int i;

  p = (MyPhil *) malloc(sizeof(MyPhil));
  p->num = phil_count;
  p->lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(p->lock, NULL);
  p->blocked_philosophers = (pthread_cond_t **) malloc(sizeof(pthread_cond_t *)*p->num);
  p->stick_states = (int *) malloc(sizeof(int)*p->num);
  for (i = 0; i < p->num; i++) {
    p->blocked_philosophers[i] = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
    pthread_cond_init(p->blocked_philosophers[i], NULL);
    p->stick_states[i] = 'D';
  }
  return p; 
}

void i_am_hungry(void *v, int philosopher) 
{
  MyPhil *p;
  int stick1, stick2;

  p = (MyPhil *) v;
  stick1 = philosopher;
  stick2 = (philosopher+1)%p->num;

  pthread_mutex_lock(p->lock);

  while(p->stick_states[stick1] == 'U' || 
        p->stick_states[stick2] == 'U') {
    pthread_cond_wait(p->blocked_philosophers[philosopher], p->lock);
  }

  pick_up_chopstick(philosopher, stick1);
  pick_up_chopstick(philosopher, stick2);
  p->stick_states[stick1] = 'U';
  p->stick_states[stick2] = 'U';

  pthread_mutex_unlock(p->lock);
  
}

void i_am_done_eating(void *v, int philosopher) 
{
  MyPhil *p;
  int stick1, stick2;

  p = (MyPhil *) v;
  stick1 = philosopher;
  stick2 = (philosopher+1)%p->num;

  pthread_mutex_lock(p->lock);

  p->stick_states[stick1] = 'D';
  p->stick_states[stick2] = 'D';
  put_down_chopstick(philosopher, stick1);
  put_down_chopstick(philosopher, stick2);
  pthread_cond_signal(p->blocked_philosophers[(philosopher+1)%p->num]);
  pthread_cond_signal(p->blocked_philosophers[(philosopher+p->num-1)%p->num]);

  pthread_mutex_unlock(p->lock);
}
