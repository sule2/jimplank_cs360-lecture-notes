#include <stdlib.h>
#include <stdio.h>
#include "printqsim.h"

typedef struct {
  int head;
  int num;
  Job **buffer;
  pthread_mutex_t *lock;
  pthread_cond_t *full;
  pthread_cond_t *empty;
} Mydata;

void initialize_v(Spq *s)
{
  Mydata *md;

  md = (Mydata *) malloc(sizeof(Mydata));
  md->buffer = (Job **) malloc(sizeof(Job *)*s->bufsize);
  md->head = 0;
  md->num = 0;
  md->lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(md->lock, NULL);
  md->full = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
  pthread_cond_init(md->full, NULL);
  md->empty = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
  pthread_cond_init(md->empty, NULL);
  s->v = (void *) md;
}

void submit_job(Spq *s, Job *j)
{
  Mydata *md;

  md = (Mydata *) s->v;
  pthread_mutex_lock(md->lock);
  while (1) {
    if (md->num == s->bufsize) {
      printf("Buffer is full.  Waiting.\n");
      pthread_cond_wait(md->full, md->lock);
    } else {
      md->buffer[(md->head+md->num)%s->bufsize] = j;
      md->num++;
      pthread_cond_signal(md->empty);
      pthread_mutex_unlock(md->lock);
      return;
    }
  }
}

Job *get_print_job(Spq *s)
{
  Mydata *md;
  Job *j;

  md = (Mydata *) s->v;
  pthread_mutex_lock(md->lock);
  while (1) {
    if (md->num == 0) {
      pthread_cond_wait(md->empty, md->lock);
    } else {
      j = md->buffer[md->head];
      md->head++;
      md->head %= s->bufsize;
      md->num--;
      pthread_cond_signal(md->full);
      pthread_mutex_unlock(md->lock);
      return j;
    }
  }
}

