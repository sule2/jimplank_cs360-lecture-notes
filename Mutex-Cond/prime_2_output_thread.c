/* prime_2_output_thread.c - adding an output thread to the prime example
   James S. Plank
   Fri Apr 12 11:10:25 EDT 2019
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "dllist.h"

/* Each thread will have its own private information, and some shared information.  
   Here's the shared information.   In addition to the debug flag, we have a 
   dllist, mutex and condition variable that allow the workers to communicate with
   the output thread. */

struct shared {
  int debug;                       /* This is 0 or 1.  If 1, it will print more information. */
  Dllist primes;                   /* List of primes found by the worker threads. */
  pthread_mutex_t *output_mutex;   /* Mutex for the list of primes. */
  pthread_cond_t  *output_cond;    /* Condition variable to wake up the output thread. */
};

/* The private information is the same.  This includes a pointer to the shared information. */

struct info {
  int id;
  struct shared *s;
};

/* Here is the code for the worker thread.  It differs from the previous code in that
   the workers append their primes to the shared dllist and then signal the output thread.  */
   
void *worker(void *arg)
{
  struct info *info;               /* Private Information. */
  struct shared *s;                /* Shared Information. */
  long prime_to_test;              /* The number to determine primality. */
  long i;
  int prime;                       /* Boolean -- is it prime? */

  /* Set the shared and private information from the argument. */

  info = (struct info *) arg;
  s = info->s;

  while (1) {

    /* Read a number from standard input.  Return if standard input is done. */

    if (scanf("%ld", &prime_to_test) != 1) {
      if (s->debug) printf("Thread %d - Input_over - Exiting.\n", info->id);
      return NULL;
    }

    if (s->debug) {
      printf("Thread %d testing %ld\n", info->id, prime_to_test);
      fflush(stdout);
    }

    /* Determine if the number is prime.  Print if debugging. */

    prime = (prime_to_test >= 2);
    for (i = 2; prime && i*i <= prime_to_test; i++) {
        if (prime_to_test % i == 0) prime = 0;
    }
    if (s->debug) {
      if (prime) {
        printf("Thread %d found prime %ld\n", info->id, prime_to_test);
      } else {
        printf("Thread %d found composite %ld.  Exited the loop when i = %ld\n", 
                info->id, prime_to_test, i-1);
      } 
    }

    /* If it's prime, then put it onto the list and signal the output thread. */

    if (prime) {
      pthread_mutex_lock(s->output_mutex);
      dll_append(s->primes, new_jval_l(prime_to_test));
      pthread_cond_signal(s->output_cond);
      pthread_mutex_unlock(s->output_mutex);
    }
  }
}

/* Here's the code for the output thread.  It takes as its argument the shared data.
   It monitors the dllist of primes, blocking when it is empty, and printing/clearing
   its contents when it is non-empty. */

void *output_thread(void *arg)
{
  struct shared *s;                /* Shared Information. */
  int counter;                     /* We'll keep track of the number of primes, too. */

  counter = 0;
  s = (struct shared *) arg;

  pthread_mutex_lock(s->output_mutex);
  while (1) {                                   /* Print the primes if there are any */
    while (!dll_empty(s->primes)) {
      printf("Prime %5d: %20ld\n", counter, s->primes->flink->val.l);
      counter++;
      dll_delete_node(s->primes->flink);
    }                                           /* When the list is empty, wait. */
    pthread_cond_wait(s->output_cond, s->output_mutex);
  }
  return NULL;
}
  
  
int main(int argc, char **argv)
{
  int nthreads;            /* The number of threads. */
  pthread_t *tids;         /* The thread id's of the worker threads. */
  pthread_t output_tid;    /* The thread id of the output thread. */
  struct shared S;         /* The information that is shared among all threads. */
  struct info *infos;      /* The private information for each thread. */
  int i;

  /* Error check */

  if (argc != 3) {
    fprintf(stderr, "usage: prime_2_output_thread nthreads debug(y|anything-else)\n");
    fprintf(stderr, "       put the numbers to test on standard input.\n");
    exit(1);
  }

  /* Set up the shared and private information. */

  nthreads = atoi(argv[1]);
  S.debug = (strcmp(argv[2], "y") == 0);
  S.primes = new_dllist();
  S.output_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  S.output_cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
  pthread_mutex_init(S.output_mutex, NULL);
  pthread_cond_init(S.output_cond, NULL);
  
  tids = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  infos = (struct info *) malloc(sizeof(struct info) * nthreads);
  for (i = 0; i < nthreads; i++) {
    infos[i].id = i;
    infos[i].s = &S;
  }

  /* Create the threads and detach them, since no one will join with them. */

  for (i = 0; i < nthreads; i++) {
    if (pthread_create(tids+i, NULL, worker, (void *) &infos[i]) != 0) {
      perror("pthread_create");
      exit(1);
    }
    pthread_detach(tids[i]);
  }

  /* Create the output thread, passing it the shared info. */

  if (pthread_create(&output_tid, NULL, output_thread, (void *) &S) != 0) {
    perror("pthread_create");
    exit(1);
  }
  pthread_detach(output_tid);

  /* Have the main thread exit, and let the worker threads run. */

  pthread_exit(NULL);
}
