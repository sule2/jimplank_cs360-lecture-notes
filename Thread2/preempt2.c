/*
 * CS360: preempt2.c
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
  pthread_attr_t attr[2];
  int id[2], i;
  void *retval;

  for (i = 0; i < 2; i++) {
    id[i] = i;
    pthread_attr_init(attr+i);
    pthread_attr_setscope(attr+i, PTHREAD_SCOPE_SYSTEM);
    pthread_create(t+i, attr+i, infloop, id+i);
  }
  for (i = 0; i < 2; i++) {
    pthread_join(t[i], &retval);
  }
}
