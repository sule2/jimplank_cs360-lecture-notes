#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "printqsim.h"


void *user_thread(void *v)
{
  Spq *s;
  int i;
  int sleeptime;
  int jobsize;
  Job *j;

  s = (Spq *) v;
  for (i = 0; i < s->nevents; i++) {
    sleeptime = random()%(s->arrtime*2) + 1;
    pthread_mutex_lock(s->stdiolock);
    printf("%4ld: user %2d/%03d: Sleeping for %2d seconds\n", 
          time(0)-s->starttime, s->id, i, sleeptime);
    fflush(stdout);
    pthread_mutex_unlock(s->stdiolock);
    sleep(sleeptime);
    j = (Job *) malloc(sizeof(Job));
    j->jobsize = (random()%s->maxpages) + 1;
    j->userid = s->id;
    j->jobid = i;
    pthread_mutex_lock(s->stdiolock);
    printf("%4ld: user %2d/%03d: Submitting a job with size %d\n", 
          time(0)-s->starttime, s->id, i, j->jobsize);
    fflush(stdout);
    pthread_mutex_unlock(s->stdiolock);
    submit_job(s, j);
  }

  pthread_mutex_lock(s->stdiolock);
  printf("%4ld: user %2d/%03d: Done\n", 
        time(0)-s->starttime, s->id, i);
  fflush(stdout);
  pthread_mutex_unlock(s->stdiolock);
  return NULL;
  
}

/* Assume 4 seconds a page */

void *printer_thread(void *v)
{
  Spq *s;
  int jobsize, userid, jobid;
  int i;
  Job *j;

  s = (Spq *) v;

  i = 0;
  while(1) {
    pthread_mutex_lock(s->stdiolock);
    printf("%4ld: prnt %2d/%03d: ready to print\n",
          time(0)-s->starttime, s->id, i);
    fflush(stdout);
    pthread_mutex_unlock(s->stdiolock);
    j = get_print_job(s);
    if (j == NULL) {
      pthread_mutex_lock(s->stdiolock);
      printf("%4ld: prnt %2d/%03d: Done\n",
            time(0)-s->starttime, s->id, i);
      fflush(stdout);
      pthread_mutex_unlock(s->stdiolock);
      pthread_exit(NULL);
    }
    pthread_mutex_lock(s->stdiolock);
    printf("%4ld: prnt %2d/%03d:",
          time(0)-s->starttime, s->id, i);
    printf(" Printing job %3d from user %2d size %3d\n", 
             j->jobid, j->userid, j->jobsize);
    fflush(stdout);
    pthread_mutex_unlock(s->stdiolock);
    sleep(4*j->jobsize);
    free(j);
    i++;
  }
}

main(int argc, char **argv)
{
  Spq spq, *s;
  pthread_t *user_tids;
  pthread_t *printer_tids;
  int i;

  if (argc != 7) {
    fprintf(stderr, 
            "usage: printqsim nusers nprinters arrtime maxpages bufsize nevents\n");
    exit(1);
  }

  spq.nusers = atoi(argv[1]);
  spq.nprinters = atoi(argv[2]);
  spq.arrtime = atoi(argv[3]);
  spq.maxpages = atoi(argv[4]);
  spq.bufsize = atoi(argv[5]);
  spq.nevents = atoi(argv[6]);
  spq.starttime = time(0);
  spq.stdiolock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(spq.stdiolock, NULL);
  srandom(spq.starttime);
  
  initialize_v(&spq);

  user_tids = (pthread_t *) malloc(sizeof(pthread_t)*spq.nusers);
  printer_tids = (pthread_t *) malloc(sizeof(pthread_t)*spq.nprinters);

  for (i = 0; i < spq.nusers; i++) {
    s = (Spq *) malloc(sizeof(Spq));
    memcpy(s, &spq, sizeof(Spq));
    s->id = i;
    pthread_create(user_tids+i, NULL, user_thread, (void *) s);
  }
  for (i = 0; i < spq.nprinters; i++) {
    s = (Spq *) malloc(sizeof(Spq));
    memcpy(s, &spq, sizeof(Spq));
    s->id = i;
    pthread_create(printer_tids+i, NULL, printer_thread, (void *) s);
  }
  pthread_exit(NULL);
}
  
