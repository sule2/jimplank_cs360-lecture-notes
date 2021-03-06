#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "sockettome.h"
#include <pthread.h>

/* We now only lock the mutex while we are accessing the tree, which allows
   multiple clients to be serviced simultaneously. */

typedef struct {
  char *name;
  int age;
  char *ssn;
} Entry;

typedef struct {
  int fd;
  JRB t;
  pthread_mutex_t *lock;
} Thread_Info;

void *server_thread(void *arg)
{
  JRB tmp;
  Thread_Info *ti;
  FILE *fin, *fout;
  int age;
  char fn[300], ln[300], ssn[100], n[300];
  char command[300];
  char line[300];
  Entry *e;
  int done;

  ti = (Thread_Info *) arg;
  fin = fdopen(ti->fd, "r");
  fout = fdopen(ti->fd, "w");

  done = 0;
  while(!done && fgets(line, 300, fin) != NULL) {
    if (sscanf(line, "%s", command) == 1) {
      if (sscanf(line, "ADD %s %s %d %s", fn, ln, &age, ssn) == 4) {
        e = (Entry *) malloc(sizeof(Entry));
        e->name = (char *) malloc(sizeof(char)*(strlen(ln)+strlen(fn)+3));
        strcpy(e->name, ln);
        strcat(e->name, ", ");
        strcat(e->name, fn);
        e->ssn = (char *) strdup(ssn);
        e->age = age;
        pthread_mutex_lock(ti->lock);
        jrb_insert_str(ti->t, e->name, new_jval_v(e));
        pthread_mutex_unlock(ti->lock);

      } else if (strcmp(command, "PRINT") == 0) {
        pthread_mutex_lock(ti->lock);
        fprintf(fout, "__________________________________________________\n");
        jrb_traverse(tmp, ti->t) {
          e = (Entry *) tmp->val.v;
          fprintf(fout, "%-30s -- %11s %4d\n", e->name, e->ssn, e->age);
        }
        fprintf(fout, "--------------------------------------------------\n");
        pthread_mutex_unlock(ti->lock);
        fflush(fout);

      } else if (sscanf(line, "DELETE %s %s", fn, ln) == 2) {
        strcpy(n, ln);
        strcat(n, ", ");
        strcat(n, fn);
        pthread_mutex_lock(ti->lock);
        tmp = jrb_find_str(ti->t, n);
        if (tmp == NULL) {
          fprintf(fout, "Error: No %s %s\n", fn, ln);
          fflush(fout);
        } else {
          jrb_delete_node(tmp);
        }
        pthread_mutex_unlock(ti->lock);

      } else if (strcmp(command, "DONE") == 0) {
        done = 1;
      } else {
        fprintf(fout, "Bad command: %s\n", command);
        fflush(fout);
      }
    }
  }
  
  close(ti->fd);
  fclose(fin);
  fclose(fout);
  free(ti);
  return NULL;
}
    
int main(int argc, char **argv)
{
  pthread_t tid;
  int sock;
  int fd;
  Thread_Info *ti;
  JRB t;
  pthread_mutex_t lock;
  
  if (argc != 2) {
    fprintf(stderr, "usage: ssnserver2 port\n");
    exit(1);
  }
 
  /* Now, service multiple connections. */

  t = make_jrb();
  pthread_mutex_init(&lock, NULL);
  
  sock = serve_socket(atoi(argv[1]));

  while (1) {
    fd = accept_connection(sock);
    ti = (Thread_Info *) malloc(sizeof(Thread_Info));
    ti->fd = fd;
    ti->t = t;
    ti->lock = &lock;
    pthread_create(&tid, NULL, server_thread, ti);
  }
  pthread_exit(NULL);
}
