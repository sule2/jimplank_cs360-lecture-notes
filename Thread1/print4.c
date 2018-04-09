/*
 * CS360:
 * James S. Plank
 * print4.c -- forks off four threads that print their ids
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Printme's argument is a (void *), which we know is actually an 
   (int *), pointing to the integer id of the thread, which is set
    up in main(). */

void *printme(void *ip)
{
  int *i;

  i = (int *) ip;
  printf("Hi.  I'm thread %d\n", *i);
  return NULL;
}

int main()
{
  int i, ids[4];
  pthread_t tids[4];
  void *retval;

  /* Fork off four "printme" threads, setting the argument to
     be a pointer to the thread's integer id. */

  for (i = 0; i < 4; i++) {
    ids[i] = i;
    if (pthread_create(tids+i, NULL, printme, ids+i) != 0) {
      perror("pthread_create");
      exit(0);
    }
  }

  /* Join with the four threads. */

  for (i = 0; i < 4; i++) {
    printf("Trying to join with thread %d\n", i);
    if (pthread_join(tids[i], &retval) != 0) { perror("join"); exit(1); }
    printf("Joined with thread %d\n", i);
  }
  return 0;
}
