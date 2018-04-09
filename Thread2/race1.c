/* CS360: race1.c, James Plank.  April, 2016. */

/* This program forks off two threads which share an integer,    
   on which there is a race condition. */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* This is information shared by the two threads. */

typedef struct {
  int i;
  int die;
} Shared_Info;

/* This is information which will be unique to each thread (SI is shared) */

typedef struct {
  int id;
  Shared_Info *SI;
} Info;

/* Here's the thread code -- pretty simple. */

void *thread(void *x)
{
  Info *I;
 
  I = (Info *) x;

  while (!I->SI->die) I->SI->i = I->id;
  return NULL;
}

/* The main code sets up the shared and unique info, then forks off two threads.
   It then sleeps for two seconds and prints out the shared variable, si.i.
   Finally, it calls pthread_join() to wait for the two threads to die, and
   prints out the shared variable again. */

int main(int argc, char **argv)
{
  pthread_t tids[2];
  Shared_Info si;
  Info I[2];
  void *retval;

  /* Set up the data to send to the threads. */

  I[0].id = 0;
  I[0].SI = &si;

  I[1].id = 1;
  I[1].SI = &si;

  si.die = 0;
  
  /* Create the two threads and sleep */

  if (pthread_create(tids, NULL, thread, I) != 0) { perror("pthread_create"); exit(1); }
  if (pthread_create(tids+1, NULL, thread, I+1) != 0) { perror("pthread_create"); exit(1); }
  sleep(2);

  /* Tell the threads to die, then print the shared info. */

  si.die = 1;
  printf("%d\n", si.i);

  /* Wait for the threads to die and print out the shared info again. */

  if (pthread_join(tids[0], &retval) != 0) { perror("pthread_join"); exit(1); }
  if (pthread_join(tids[1], &retval) != 0) { perror("pthread_join"); exit(1); }
  printf("%d\n", si.i);

  return 0;
}
