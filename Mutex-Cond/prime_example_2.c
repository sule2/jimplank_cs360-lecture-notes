/* prime_example_2.c - read numbers into a dllist without any locks. 
   James S. Plank
   April, 2017
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "dllist.h"

/* Each thread will have its own private information, 
   and some shared information.  Here's the shared information. 
   There's a dllist to hold the numbers to test. */

struct shared {
  int nthreads;
  int debug;          /* This is 0 or 1.  If 1, it will print more information. */
  Dllist numbers;
};

/* Here's the private information.  
   This includes a pointer to the shared information. */

struct info {
  int id;
  struct shared *S;
};

/* This procedure reads the numbers from standard input to the dllist,
   1000 numbers at a time. */

int read_numbers(Dllist l)
{
  int i;
  long n;

  for (i = 0; i < 1000; i++) {
    if (scanf("%ld", &n) != 1) {
      return (i == 0) ? 0 : 1;
    }
    dll_append(l, new_jval_l(n));
  }
  return 1;
}

/* Find_primes now calls read_numbers() when the dllist is
   empty.  Each thread pulls numbers off the dllist to check. */

void *find_primes(void *arg)
{
  struct info *info;
  struct shared *s;
  long prime_to_test, i;
  int prime;

  info = (struct info *) arg;
  s = info->S;

  while (1) {

    if (dll_empty(s->numbers)) {
      if (s->debug) {
        printf("Thread %d calling read_numbers.\n", info->id);
        fflush(stdout);
      }
      if (read_numbers(s->numbers) == 0) {
        if (s->debug) {
          printf("Thread %d exiting.\n", info->id);
          fflush(stdout);
        }
        return NULL;
      }
    }

    prime_to_test = s->numbers->flink->val.l;
    dll_delete_node(s->numbers->flink);

    if (s->debug) {
      printf("Thread %d testing %ld\n", info->id, prime_to_test);
      fflush(stdout);
    }

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
  pthread_t *tids;
  struct info *infos;
  struct shared S;
  int i;
  long l;

  if (argc != 3) {
    fprintf(stderr, "usage: mutex_example nthreads debug(y|anything-else)\n");
    fprintf(stderr, "       put the numbers to test on standard input.\n");
    exit(1);
  }

  S.nthreads = atoi(argv[1]);
  S.debug = (strcmp(argv[2], "y") == 0);
  S.numbers = new_dllist();
  
  tids = (pthread_t *) malloc(sizeof(pthread_t) * S.nthreads);
  infos = (struct info *) malloc(sizeof(struct info) * S.nthreads);

  for (i = 0; i < S.nthreads; i++) {
    infos[i].id = i;
    infos[i].S = &S;
  }

  for (i = 0; i < S.nthreads; i++) {
    pthread_create(tids+i, NULL, find_primes, (void *) &infos[i]);
  }

  pthread_exit(NULL);
}