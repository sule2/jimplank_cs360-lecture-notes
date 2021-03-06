/* dphil_6_hybrid.c
   James S. Plank
   April, 2016
   CS360 - Systems Programming

   You can't eat if your neighbors are starving.
 */

#include <stdio.h>
#include <pthread.h>
#include "dphil.h"

typedef struct {
  int num;
  pthread_mutex_t *lock;
  pthread_cond_t **blocked_philosophers;
  int *phil_number;
  int counter;
} MyPhil;

#define HIGH_SENTINEL (0x7fffffff)
#define LOW_SENTINEL (-1)
#define THRESH (5)

void *initialize_v(int phil_count) 
{
  MyPhil *p;
  int i;

  p = (MyPhil *) malloc(sizeof(MyPhil));
  p->num = phil_count;
  p->counter = 0;
  p->lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(p->lock, NULL);
  p->blocked_philosophers = (pthread_cond_t **) malloc(sizeof(pthread_cond_t *)*p->num);
  p->phil_number = (int *) malloc(sizeof(int)*p->num);
  for (i = 0; i < p->num; i++) {
    p->blocked_philosophers[i] = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
    pthread_cond_init(p->blocked_philosophers[i], NULL);
    p->phil_number[i] = HIGH_SENTINEL;
  }
  return p; 
}

void i_am_hungry(void *v, int philosopher) 
{
  MyPhil *p;
  int leftp, rightp;

  p = (MyPhil *) v;
  leftp = (philosopher+p->num-1)%p->num;
  rightp = (philosopher+1)%p->num;

  pthread_mutex_lock(p->lock);

  p->phil_number[philosopher] = p->counter;
  p->counter++;

  while (p->phil_number[philosopher] - p->phil_number[leftp] > THRESH * p->num ||
         p->phil_number[philosopher] - p->phil_number[rightp] > THRESH * p->num) {
    pthread_cond_wait(p->blocked_philosophers[philosopher], p->lock);
  }

  pick_up_chopstick(philosopher, philosopher);
  pick_up_chopstick(philosopher, (philosopher+1)%p->num);

  p->phil_number[philosopher] = LOW_SENTINEL - THRESH * p->num;

  pthread_mutex_unlock(p->lock);
}

void i_am_done_eating(void *v, int philosopher) 
{
  MyPhil *p;
  int leftp, rightp;

  p = (MyPhil *) v;
  leftp = (philosopher+p->num-1)%p->num;
  rightp = (philosopher+1)%p->num;

  pthread_mutex_lock(p->lock);
  put_down_chopstick(philosopher, philosopher);
  put_down_chopstick(philosopher, (philosopher+1)%p->num);
  p->phil_number[philosopher] = HIGH_SENTINEL;
  
  pthread_cond_signal(p->blocked_philosophers[leftp]);
  pthread_cond_signal(p->blocked_philosophers[rightp]);
  pthread_mutex_unlock(p->lock);
}
