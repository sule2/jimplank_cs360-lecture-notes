/* prime_4_input_thread.c - adding a thread whose job is to read input.
   James S. Plank
   Fri Apr 12 12:40:15 EDT 2019
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
  int workers_alive;               /* Boolean for whether there are still worker threads. */
  int input_over;                  /* Boolean for whether there is no more input. */
  Dllist primes;                   /* List of primes found by the worker threads. */
  Dllist primes_to_test;           /* List of primes to test. */
  pthread_mutex_t *output_mutex;   /* Mutex for the list of primes. */
  pthread_cond_t  *output_cond;    /* Condition variable to wake up the output thread. */
  pthread_mutex_t *input_mutex;    /* Mutex for the list of primes. */
  pthread_cond_t *input_cond;      /* Condition variable for the input thread to wait. */
  pthread_cond_t *worker_cond;     /* Condition variable for the workers to wait. */
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
    
    /* Get a number from the primes_to_test list.  If it's empty, signal the
       input thread, and wait to be unblocked. */

    pthread_mutex_lock(s->input_mutex);
    while (!s->input_over && dll_empty(s->primes_to_test)) {
      if (s->debug) printf("Thread %d - waking up the reader thread and blocking.\n", info->id);
      pthread_cond_signal(s->input_cond);
      pthread_cond_wait(s->worker_cond, s->input_mutex);
    }
    pthread_cond_signal(s->worker_cond);   /* See the lecture notes for why I do this. */

    if (!dll_empty(s->primes_to_test)) {  /* Grab a prime to test from the list. */
      prime_to_test = s->primes_to_test->flink->val.l;
      dll_delete_node(s->primes_to_test->flink);
    } else {                              /* Otherwise, the input is done - so return */
      pthread_mutex_unlock(s->input_mutex);
      if (s->debug) printf("Thread %d - exiting.\n", info->id);
      return NULL;
    }

    pthread_mutex_unlock(s->input_mutex);
 
    /* All of the rest of the code is the same. */

    /* Determine if the number is prime.  Print if debugging. */

    if (s->debug) {
      printf("Thread %d testing %ld\n", info->id, prime_to_test);
      fflush(stdout);
    }
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

  /* Change the loop to exit when the list is empty and there are no more workers. */

  pthread_mutex_lock(s->output_mutex);
  while (!dll_empty(s->primes) || s->workers_alive) {
    while (!dll_empty(s->primes)) {
      printf("Prime %5d: %20ld\n", counter, s->primes->flink->val.l);
      counter++;
      dll_delete_node(s->primes->flink);
    }                                           /* When the list is empty, wait. */
    pthread_cond_wait(s->output_cond, s->output_mutex);
  }
  pthread_mutex_unlock(s->output_mutex);
  return NULL;
}
  
/* Here's the code for the input thread.  When the primes_to_test list is empty, it
   reads eight primes from standard input and puts them onto the list.  It also
   signals the worker_cond once for each number.  If there are multiple workers waiting,
   they will wake each other up. */
   
void *input_thread(void *arg)
{
  struct shared *s;                /* Shared Information. */
  int i;
  long l;

  s = (struct shared *) arg;

  pthread_mutex_lock(s->input_mutex);

  while (1) {
    /* If the list is empty, then put ten items on it (if there are ten items to
       put on it).  Then signal the worker_cond to wake up a blocking worker.
       That worker will unblock the others if necessary. */

    if (dll_empty(s->primes_to_test)) {
      for (i = 0; i < 10; i++) {

        /* Read an integer and put it on the list. */
        if (scanf("%ld", &l) == 1) {
          dll_append(s->primes_to_test, new_jval_l(l));
          if (s->debug) printf("Reader thread put %ld onto primes_to_test.\n", l);

        /* If we're at EOF, then flag that input is over, signal the worker thread and exit. */
        } else {
          s->input_over = 1;
          pthread_cond_signal(s->worker_cond);
          if (s->debug) printf("Reader thread is done.\n");
          pthread_mutex_unlock(s->input_mutex);
          return NULL;
        }
      }
      pthread_cond_signal(s->worker_cond);

    /* If the list isn't empty, simply block and wait for a worker thread to signal you
       that the list is empty. */

    } else {
      if (s->debug) printf("Reader thread is blocking until primes_to_test is empty.\n");
      pthread_cond_wait(s->input_cond, s->input_mutex);
    }
  }
 
  /* Keep the compiler quiet. */
  return NULL;
}
  
  
int main(int argc, char **argv)
{
  int nthreads;            /* The number of threads. */
  pthread_t *tids;         /* The thread id's of the worker threads. */
  pthread_t output_tid;    /* The thread id of the output thread. */
  pthread_t input_tid;     /* The thread id of the input thread. */
  struct shared S;         /* The information that is shared among all threads. */
  struct info *infos;      /* The private information for each thread. */
  void *rv;
  int i;

  /* Error check */

  if (argc != 3) {
    fprintf(stderr, "usage: prime_4_input_thread nthreads debug(y|anything-else)\n");
    fprintf(stderr, "       put the numbers to test on standard input.\n");
    exit(1);
  }

  /* Set up the shared and private information. */

  nthreads = atoi(argv[1]);

  S.debug = (strcmp(argv[2], "y") == 0);
  S.workers_alive = 1;
  S.input_over = 0;
  S.primes = new_dllist();
  S.primes_to_test = new_dllist();

  S.output_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  S.input_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  S.output_cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
  S.input_cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
  S.worker_cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));

  pthread_mutex_init(S.output_mutex, NULL);
  pthread_mutex_init(S.input_mutex, NULL);
  pthread_cond_init(S.output_cond, NULL);
  pthread_cond_init(S.input_cond, NULL);
  pthread_cond_init(S.worker_cond, NULL);
  
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
  }

  /* Create the output thread, passing it the shared info. */

  if (pthread_create(&output_tid, NULL, output_thread, (void *) &S) != 0) {
    perror("pthread_create");
    exit(1);
  }
  pthread_detach(output_tid);

  /* Create the input thread, passing it the shared info. */

  if (pthread_create(&input_tid, NULL, input_thread, (void *) &S) != 0) {
    perror("pthread_create");
    exit(1);
  }
  pthread_detach(input_tid);

  /* Wait for the worker threads to exit, and then signal the output thread to exit. */

  for (i = 0; i < nthreads; i++) pthread_join(tids[i], &rv);
  pthread_mutex_lock(S.output_mutex);
  S.workers_alive = 0;
  pthread_cond_signal(S.output_cond);
  pthread_mutex_unlock(S.output_mutex);

  pthread_exit(NULL);
}
