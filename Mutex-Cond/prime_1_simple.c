/* Prime_1_simple.c - multiple threads read longs from standard input and print out the primes.
   James S. Plank
   April, 2017.
   And Thu Apr 11 16:37:03 EDT 2019
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/* Each thread will have its own private information, and some shared information.  
   Here's the shared information.   At this point, there's little to share, because
   the threads are simply reading from standard input and writing to standard output. */

struct shared {
  int debug;          /* This is 0 or 1.  If 1, it will print more information. */
};

/* Here's the private information.  This includes a pointer to the shared information. */

struct info {
  int id;
  struct shared *s;
};

/* This is what each thread runs.  
   Each thread reads longs from standard input, and prints out the primes on standard output. */
   
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

    /* Determine if the number is prime, and print out if so. */

    prime = (prime_to_test >= 2);
    for (i = 2; prime && i*i <= prime_to_test; i++) {
        if (prime_to_test % i == 0) prime = 0;
    }

    if (prime) {
      printf("Thread %d found prime %ld\n", info->id, prime_to_test);
    } else if (s->debug) {
      printf("Thread %d found composite %ld.  Exited the loop when i = %ld\n", 
              info->id, prime_to_test, i-1);
    } 
  }
}

  
int main(int argc, char **argv)
{
  int nthreads;            /* The number of threads. */
  pthread_t *tids;         /* The thread id's of the worker threads. */
  struct shared S;         /* The information that is shared among all threads. */
  struct info *infos;      /* The private information for each thread. */
  int i;

  /* Error check */

  if (argc != 3) {
    fprintf(stderr, "usage: prime_1_simple nthreads debug(y|anything-else)\n");
    fprintf(stderr, "       put the numbers to test on standard input.\n");
    exit(1);
  }

  /* Set up the shared and private information. */

  nthreads = atoi(argv[1]);
  S.debug = (strcmp(argv[2], "y") == 0);
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

  /* Have the main thread exit, and let the worker threads run. */

  pthread_exit(NULL);
}
