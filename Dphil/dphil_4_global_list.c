/* dphil_4_global_list.c
   James S. Plank
   April, 2016
   CS360 - Systems Programming

   Don't eat if anyone is hungrier than you.
 */

#include <stdio.h>
#include <pthread.h>
#include "dphil.h"

/* Now we keep a queue of philosophers who are hungry.  If the queue isn't empty,
   then whenever a philosopher is hungry, he/she has to go on the end of the 
   queue.  Only the philosopher on the head of the queue can eat.   

   We use a simple array to model the queue.  The queue's size is held in 
   wq_size.  The first philosopher is at wq_head.  When you insert a philosopher
   on the queue, then he/she goes into elelemtn (wq_head+wq_size)%num. */

typedef struct {
  int num;
  pthread_mutex_t *lock;
  pthread_cond_t **blocked_philosophers;
  int *stick_states;
  int *waiting_queue;
  int wq_head;
  int wq_size;
} MyPhil;

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
  p->waiting_queue = (int *) malloc(sizeof(int)*p->num);
  p->wq_head = 0;
  p->wq_size = 0;

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

  /* Put yourself on the queue */

  p->waiting_queue[(p->wq_head + p->wq_size)%p->num] = philosopher;
  p->wq_size++;

  /* You can't eat until you are on the head of the queue, and your
     chopsticks are available. */

  while (p->waiting_queue[p->wq_head] != philosopher ||
         p->stick_states[stick1] == 'U' ||
         p->stick_states[stick2] == 'U') {
    pthread_cond_wait(p->blocked_philosophers[philosopher], p->lock);
  }

  /* When you reach this part of the code, you can eat. */

  pick_up_chopstick(philosopher, philosopher);
  pick_up_chopstick(philosopher, (philosopher+1)%p->num);

  p->stick_states[stick1] = 'U';
  p->stick_states[stick2] = 'U';

  /* Remove yourself from the queue, and signal whoever is now on the
     head of the queue. */
  p->wq_head = (p->wq_head + 1) % p->num;
  p->wq_size--;
  if (p->wq_size > 0) {
    pthread_cond_signal(p->blocked_philosophers[p->waiting_queue[p->wq_head]]);
  }
  
  pthread_mutex_unlock(p->lock);
}

/* When you're done eating, signal the philosopher on the head of the queue. */

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
  if (p->wq_size > 0) {
    pthread_cond_signal(p->blocked_philosophers[p->waiting_queue[p->wq_head]]);
  }
  pthread_mutex_unlock(p->lock);
}
