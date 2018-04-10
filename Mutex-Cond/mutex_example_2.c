/* Mutex_example_2.c - removing the mutex.
   James S. Plank
   April, 2017
 */

/* The only thing different from this and mutex_example_1.c, is that
   I have commented out the lock and unlock calls. */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/* Each thread is going to have private information and 
   shared information.  Here is the shared information. */

struct shared {
  int counter;            /* A shared counter. */
  pthread_mutex_t *lock;  /* A lock to protect the counter. */
  int usleeptime;         /* Microseconds that each thread will sleep after updating the counter. */
};

/* Here is the private information */

struct info {
  int id;                 /* The thread's id. */
  struct shared *s;       /* Pointer to the shared information. */
};

/* Here is the procedure that each thread calls.  
   In a nutshell, each thread locks the mutex, increments the
   counter, then sleeps.  It then tests to make sure that the
   counter hasn't been modified, and unlocks the mutex.  It
   repeats this loop indefinitely. */

void *share_counter(void *arg)
{
  struct info *info;    /* The thread's private info. */
  struct shared *s;     /* The thread's shared info. */
  int counter;          /* A copy of the counter, to test. */

  info = (struct info *) arg;
  s = info->s;

  while (1) {

    /* Lock the mutex, update the counter and print. */

    /* pthread_mutex_lock(s->lock);       */
    s->counter++;
    counter = s->counter;
    printf("Thread: %3d - Begin - Counter %3d.\n", info->id, s->counter);
    fflush(stdout);

    /* Sleep, and then print the counter again. */

    usleep(s->usleeptime);
    printf("Thread: %3d - End   - Counter %3d.\n", info->id, s->counter);
    fflush(stdout);

    /* Make sure the counter hasn't been modified, then unlock the mutex. */

    if (s->counter != counter) {
      printf("Thread %d - Problem -- counter was %d, but now it's %d\n",
             info->id, counter, s->counter);
      exit(1);
    }
    /* pthread_mutex_unlock(s->lock); */

  }

  return NULL;   /* Shut the compiler up. */
}

/* The main sets up the threads, and exits. */
  
int main(int argc, char **argv)
{
  int nthreads;
  int usleeptime;
  pthread_t *tids;
  struct shared S;
  struct info *infos;
  int i;

  if (argc != 3) {
    fprintf(stderr, "usage: mutex_example nthreads usleep_time\n");
    exit(1);
  }

  nthreads = atoi(argv[1]);
  usleeptime = atoi(argv[2]);

  tids = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  infos = (struct info *) malloc(sizeof(struct info) * nthreads);
  for (i = 0; i < nthreads; i++) {
    infos[i].id = i;
    infos[i].s = &S;
  }
  S.counter = 0;
  S.usleeptime = usleeptime;
  S.lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(S.lock, NULL);

  for (i = 0; i < nthreads; i++) {
    pthread_create(tids+i, NULL, share_counter, (void *) &infos[i]);
  }

  pthread_exit(NULL);
}
