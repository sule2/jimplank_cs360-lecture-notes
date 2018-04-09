#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* This is the same as print4.c, except that we call pthread_exit()
   in the main thread before making the pthread_join() calls. */

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

  for (i = 0; i < 4; i++) {
    ids[i] = i;
    if (pthread_create(tids+i, NULL, printme, ids+i) != 0) {
      perror("pthread_create");
      exit(0);
    }
  }

  pthread_exit(NULL);  /* Here's the new call. */

  for (i = 0; i < 4; i++) {
    printf("Trying to join with thread %d\n", i);
    if (pthread_join(tids[i], &retval) != 0) { perror("join"); exit(1); }
    printf("Joined with thread %d\n", i);
  }
  return 0;
}
