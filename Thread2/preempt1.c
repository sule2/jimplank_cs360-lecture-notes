/*
 * CS360: preempt1.c
 * Jim Plank
 */

#include <stdio.h>
#include <pthread.h>



void *infloop(void *x)
{
  double f;
  int i, j, *id;
 
  id = (int *) x;

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
  int i[2];
  void *retval;

  i[0] = 0;
  i[1] = 1;
  pthread_create(t, NULL, infloop, i);
  pthread_create(t+1, NULL, infloop, i+1);
  pthread_join(t[0], &retval);
  pthread_join(t[1], &retval);
}
