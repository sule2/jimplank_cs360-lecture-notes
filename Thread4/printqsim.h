#include <pthread.h>

typedef struct {
  int nusers;
  int nprinters;
  int arrtime;
  int maxpages;
  int bufsize;
  int nevents;
  int id;
  int starttime;
  pthread_mutex_t *stdiolock;
  void *v;
} Spq;

typedef struct {
  int jobsize;
  int userid;
  int jobid;
} Job;

extern void initialize_v(Spq *);

extern void submit_job(Spq *, Job *); 

extern Job *get_print_job(Spq *);
