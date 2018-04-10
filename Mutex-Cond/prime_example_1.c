/* Prime_example_1.c - multiple threads read longs from standard input and print out the primes.
   James S. Plank
   April, 2017.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/* Each thread will have its own private information, 
   and some shared information.  Here's the shared information. */

struct shared {
  int debug;          /* This is 0 or 1.  If 1, it will print more information. */
};

/* Here's the private information.  
   This includes a pointer to the shared information. */

struct info {
  int id;
  struct shared *s;
};

/* This is what each thread runs.  
   Each thread reads longs from standard input, and prints out the primes. */
   
void *find_primes(void *arg)
{
  struct info *info;
  struct shared *s;
  long prime_to_test, i;
  int prime;

  info = (struct info *) arg;
  s = info->s;

  while (1) {

    /* Read a number from standard input. */

    if (scanf("%ld", &prime_to_test) != 1) {
      if (s->debug) printf("Thread %d - Input_over - Exiting.\n", info->id);
      return NULL;
    }

    if (s->debug) {
      printf("Thread %d testing %ld\n", info->id, prime_to_test);
      fflush(stdout);
    }

    /* Determine if the number is prime. */

    prime = 1;
    for (i = 2; prime && i*i <= prime_to_test; i++) {
        if (prime_to_test % i == 0) prime = 0;
    }

    if (prime) {
      printf("Thread %d found prime %ld\n", info->id, prime_to_test);
    }
  }
}

  
int main(int argc, char **argv)
{
  int nthreads;
  pthread_t *tids;
  struct info *infos;
  struct shared S;
  int i;
  long l;

  if (argc != 3) {
    fprintf(stderr, "usage: prime_example nthreads debug(y|anything-else)\n");
    fprintf(stderr, "       put the numbers to test on standard input.\n");
    exit(1);
  }

  nthreads = atoi(argv[1]);
  if (strcmp(argv[2], "y") == 0) {
    S.debug = (strcmp(argv[2], "y") == 0);
  }

  tids = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  infos = (struct info *) malloc(sizeof(struct info) * nthreads);
  for (i = 0; i < nthreads; i++) {
    infos[i].id = i;
    infos[i].s = &S;
  }

  for (i = 0; i < nthreads; i++) {
    pthread_create(tids+i, NULL, find_primes, (void *) &infos[i]);
  }

  pthread_exit(NULL);
}
