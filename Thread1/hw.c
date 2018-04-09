#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* This is the procedure called by the thread.  I'm ignoring the argument
   (which is specified to be NULL in the pthread_create() calls. */

void *printme()
{
  printf("Hello world\n");
  return NULL;
}

int main()
{
  pthread_t tcb;
  void *status;

  /* Create one thread, which prints Hello World. */

  if (pthread_create(&tcb, NULL, printme, NULL) != 0) {
    perror("pthread_create");
    exit(1);
  }
  
  /* Wait for that thread to exit, and then exit. */

  if (pthread_join(tcb, &status) != 0) { 
    perror("pthread_join"); 
    exit(1); 
  }

  return 0;
}
