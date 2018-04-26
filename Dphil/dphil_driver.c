/* dphil_driver.c
   James S. Plank
   April, 2016
   CS360 - Systems Programming

   This is the file that implements the driver for dining philosophers.  
   Please see dphil.h for an explanation of what this file does.
 */

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "dphil.h"

struct phil {
  int num;
  int maxthink;
  int maxeat;
  int sleep;    /* 'U' or 'S' */
  int print;    /* 'Y' or 'N' */

  pthread_mutex_t *lock;
  pthread_cond_t **stick_conds;
  int *stick_states;
  int *phil_states;

  long t0;
  double dt0;

  pthread_mutex_t *blocklock;
  double *blocktime;
  double *start_hungry;
  int accounting_interval;

  void *v;
};

struct phil P;
struct phil *PS;
char buf[100];

char *phil_time()
{
  struct timeval tv;
  double t;

  if (PS->sleep == 'S') {
    sprintf(buf, "%3ld", time(0)-PS->t0);
    return buf;
  } else {
    gettimeofday(&tv, NULL);
    t = tv.tv_usec;
    t /= 1000000.0;
    t += tv.tv_sec;
    sprintf(buf, "%7.3lf", (t-PS->dt0));
    return buf;
  }
}

void *accounting_thread(void *arg)
{
  double tblock;
  struct timeval tv;
  double t;
  int i;
  double *bt;

  bt = (double *) malloc(sizeof(double)*PS->num);

  while (1) {
    if (PS->sleep == 'S') {
      sleep(PS->accounting_interval);
    } else {
      usleep(PS->accounting_interval);
    }
    gettimeofday(&tv, NULL);
    t = tv.tv_usec;
    t /= 1000000.0;
    t += tv.tv_sec;
  
    tblock = 0;
  
    pthread_mutex_lock(PS->blocklock);
    for (i = 0; i < PS->num; i++) {
      bt[i] = PS->blocktime[i];
      if (PS->phil_states[i] == 'H') bt[i] += (t - PS->start_hungry[i]);
      tblock += bt[i];
    }
  
    printf("%s Total-Hungry %.3lf\n", phil_time(), tblock);
    printf("%s Individual-Hungry", phil_time());
    for (i = 0; i < PS->num; i++) printf(" %7.3lf", bt[i]);
    printf("\n");
    fflush(stdout);
    pthread_mutex_unlock(PS->blocklock);
  }

  return NULL;
}

void pick_up_chopstick(int id, int stick)
{
  if (PS->phil_states[id] != 'H') {
    printf("%s Error -- pick_up_chopstick(%d %d) called and philosopher's state is %c .\n", 
         phil_time(), id, stick, PS->phil_states[id]);
    exit(1);
  }
  pthread_mutex_lock(PS->lock);
  while (PS->stick_states[stick] != -1) {
    if (PS->print == 'Y') {
      pthread_mutex_lock(PS->blocklock);
      printf("%s Philosopher %d Blocking on Stick %d\n", phil_time(), id, stick);
      fflush(stdout);
      pthread_mutex_unlock(PS->blocklock);
    }
    pthread_cond_wait(PS->stick_conds[stick], PS->lock);
  }

  PS->stick_states[stick] = id;

  if (PS->print == 'Y') {
    pthread_mutex_lock(PS->blocklock);
    printf("%s Philosopher %d Picked Up Stick %d\n", phil_time(), id, stick);
    fflush(stdout);
    pthread_mutex_unlock(PS->blocklock);
  }

  pthread_mutex_unlock(PS->lock);
}

void put_down_chopstick(int id, int stick)
{
  if (PS->phil_states[id] != 'E') {
    printf("%s Error -- put_down_chopstick(%d %d) called and philosopher's state is %c .\n", 
         phil_time(), id, stick, PS->phil_states[id]);
    exit(1);
  }
  if (PS->stick_states[stick] != id) {
    printf("%s Error -- put_down_chopstick(%d %d) called and chopstick state is %d .\n", 
         phil_time(), id, stick, PS->stick_states[stick]);
    exit(1);
  }
  pthread_mutex_lock(PS->lock);
  PS->stick_states[stick] = -1;
  if (PS->print == 'Y') {
    pthread_mutex_lock(PS->blocklock);
    printf("%s Philosopher %d Put Down Stick %d\n", phil_time(), id, stick);
    fflush(stdout);
    pthread_mutex_unlock(PS->blocklock);
  }
  pthread_cond_signal(PS->stick_conds[stick]);
  pthread_mutex_unlock(PS->lock);
}

void *philosopher(void *arg)
{
  int id;
  int thinktime, eattime;
  struct timeval tv;
  double t;

  id = *((int *) arg);
  while (1) {
    thinktime = random() % PS->maxthink + 1;
    if (PS->print == 'Y') {
      pthread_mutex_lock(PS->blocklock);
      printf("%s Philosopher %d Thinking (%d)\n", phil_time(), id, thinktime);
      fflush(stdout);
      pthread_mutex_unlock(PS->blocklock);
    }

    if (PS->sleep == 'U') usleep(thinktime); else sleep(thinktime);
 
    if (PS->print == 'Y') {
      pthread_mutex_lock(PS->blocklock);
      printf("%s Philosopher %d Hungry\n", phil_time(), id);
      fflush(stdout);
      pthread_mutex_unlock(PS->blocklock);
    }

    pthread_mutex_lock(PS->blocklock);
    PS->phil_states[id] = 'H';
    gettimeofday(&tv, NULL);
    t = tv.tv_usec;
    t /= 1000000.0;
    t += tv.tv_sec;
    PS->start_hungry[id] = t;
    pthread_mutex_unlock(PS->blocklock);
    
    i_am_hungry(PS->v, id);

    if (PS->phil_states[id] != 'H') {
      printf("%s Philosopher %d Error -- state should be H, but it's %c\n", 
           phil_time(), id, PS->phil_states[id]);
      exit(1);
    }
    if (PS->stick_states[id] != id) {
      printf("%s Philosopher %d Error -- stick %d state should be %d, but it is %d.\n", 
           phil_time(), id, id, id, PS->stick_states[id]);
      exit(1);
    }
      
    if (PS->stick_states[(id+1)%PS->num] != id) {
      printf("%s Philosopher %d Error -- stick %d state should be %d, but it is %d.\n", 
           phil_time(), id, (id+1)%PS->num, id, PS->stick_states[id]);
      exit(1);
    }

    pthread_mutex_lock(PS->blocklock);
    PS->phil_states[id] = 'E';
    gettimeofday(&tv, NULL);
    t = tv.tv_usec;
    t /= 1000000.0;
    t += tv.tv_sec;
    PS->blocktime[id] += (t - PS->start_hungry[id]);
    pthread_mutex_unlock(PS->blocklock);
      
    eattime = random() % PS->maxeat + 1;
    if (PS->print == 'Y') {
      pthread_mutex_lock(PS->blocklock);
      printf("%s Philosopher %d Eating (%d)\n", phil_time(), id, eattime);
      fflush(stdout);
      pthread_mutex_unlock(PS->blocklock);
    }

    if (PS->sleep == 'U') usleep(eattime); else sleep(eattime);

    i_am_done_eating(PS->v, id);

    if (PS->phil_states[id] != 'E') {
      printf("%s Philosopher %d Error -- state should be E, but it's %c\n", 
           phil_time(), id, PS->phil_states[id]);
      exit(1);
    }
    if (PS->stick_states[id] == id) {
      printf("%s Philosopher %d Error -- stick %d state should not be %d, but it is.\n", 
           phil_time(), id, id, id);
      exit(1);
    }
      
    if (PS->stick_states[(id+1)%PS->num] == id) {
      printf("%s Philosopher %d Error -- stick %d state should not be %d, but it is.\n", 
           phil_time(), id, (id+1)%PS->num, id);
      exit(1);
    }
  }
}
void usage(char *s)
{
  fprintf(stderr, "usage: dphil num-philosophers max-think max-eat accounting-interval seed(-1=time(0)) sleep(u|s) print(y|n)\n");
  if (strlen(s) > 0) fprintf(stderr, "%s\n", s);
  exit(1);
}

int main(int argc, char **argv)
{
  if (argc != 8) usage("");
  int *ids;
  pthread_t *tids, atid;
  int i;
  long seed;
  struct timeval tv;
  
  PS = &P;
  PS->num = atoi(argv[1]);
  PS->maxthink = atoi(argv[2]);
  PS->maxeat = atoi(argv[3]);
  PS->accounting_interval = atoi(argv[4]);
  sscanf(argv[5], "%ld", &seed);
  if (seed == -1) seed = time(0);
  PS->sleep = (argv[6][0] == 'u') ? 'U' : 'S';
  PS->print = (argv[7][0] == 'y') ? 'Y' : 'N';

  if (PS->num <= 0 || PS->maxthink <= 0 || PS->maxeat <= 0) {
    usage("num-philosophers, max-think and max-eat all have to be greater than zero");
  }

  ids = (int *) malloc(sizeof(int) * PS->num);
  tids = (pthread_t *) malloc(sizeof(pthread_t) * PS->num);
  PS->lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * PS->num);
  PS->stick_states = (int *) malloc(sizeof(int) * PS->num);
  PS->phil_states = (int *) malloc(sizeof(int) * PS->num);
  PS->stick_conds = (pthread_cond_t **) malloc(sizeof(pthread_cond_t *) * PS->num);
  PS->blocklock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * PS->num);
  PS->blocktime = (double *) malloc(sizeof(double)*PS->num);
  PS->start_hungry = (double *) malloc(sizeof(double)*PS->num);

  pthread_mutex_init(PS->lock, NULL);
  pthread_mutex_init(PS->blocklock, NULL);

  for (i = 0; i < PS->num; i++) {
    ids[i] = i;
    PS->stick_states[i] = -1;
    PS->phil_states[i] = 'T';
    PS->stick_conds[i] = (pthread_cond_t *) malloc(sizeof(pthread_cond_t) * PS->num);
    pthread_cond_init(PS->stick_conds[i], NULL);
    PS->blocktime[i] = 0;
    PS->start_hungry[i] = 0;
  }
  
  if (PS->print == 'Y') printf("#-Philosophers: %d\n", PS->num);
  fflush(stdout);

  PS->t0 = time(0);
  gettimeofday(&tv, NULL);
  PS->dt0 = tv.tv_usec;
  PS->dt0 /= 1000000.0;
  PS->dt0 += tv.tv_sec;
  
  srandom(seed);

  if (PS->accounting_interval > 0) {
    pthread_create(&atid, NULL, accounting_thread, (void *) NULL);
  }

  PS->v = initialize_v(PS->num);
  for (i = 0; i < PS->num; i++) {
    pthread_create(tids+i, NULL, philosopher, (void *) (ids+i));
  }
  pthread_exit(NULL);
}
