/*
 * CS360: preempt3.c
 * Jim Plank
 */

#include <stdio.h>
#include <pthread.h>

void *infloop(void *x)
{
  double f;
  int i, j, *id;
  char c;
 
  id = (int *) x;

  if (*id == 0) {
    printf("Thread %d: stopping to read\n", *id);
    read(0, &c, 1);
    printf("Thread %d: Starting up again\n", *id);
  }
  for (i = 0; i >= 0; i++) {
    printf("thread %d.  i = %10d\n", *id, i);
    f = 1;
    for (j = 0; j < 90000; j++) {
      f = f*.99;
    }
  }
  return NULL;
}

int main()
{
  pthread_t t[2];
  int id[2], i;
  void *retval;

  for (i = 0; i < 2; i++) {
    id[i] = i;
    pthread_create(t+i, NULL, infloop, id+i);
  }
  for (i = 0; i < 2; i++) {
    pthread_join(t[i], &retval);
  }
}
