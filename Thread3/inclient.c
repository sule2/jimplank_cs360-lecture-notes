#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sockettome.h"
#include "jrb.h"
#include "dllist.h"
#include "fields.h"
#include <pthread.h>

#define NFN 65

static char *fns[NFN] =
  { "Adam", "Andrei", "Anika", "Baine", "Bill", "Blanche", "Brad",
  "Buddy", "Carla", "Catherine", "Charlie", "Chemique", "Cindy",
  "Dave", "Dizzy", "Eden", "Elena", "Dontonio", "Ellen", "Emily",
  "Glenn", "Helen", "Jamal", "Jamie", "Jane", "Jay", "Jean", "Jeff",
  "Jennifer", "Jian", "Jim", "John", "Katie", "Kevin", "Kitty",
  "Kyra", "LaShonda", "Lazar", "Leonard", "Mark", "Mary", "Miles",
  "Mingo", "Misty", "Molly", "Pat", "Peg", "Peyton", "Phil",
  "Priest", "Raynoch", "Rob", "Semeka", "Sergei", "Shira", "Suzy",
  "Sviatoslav", "Tamika", "Terry", "Thor", "Tom", "Wallace", "Wanda",
  "Wendy", "Xavier" };


void *connection_reader(void *fdp)
{
  char buf[2000];
  int j;
  int fd;
  FILE *fin;

  fd = * (int *) fdp;
  fin = fdopen(fd, "r");

  while(fgets(buf, 2000, fin) != NULL) {
    fputs(buf, stdout);
  }
  fclose(fin);
  return NULL;
}


int main(int argc, char **argv)
{
  int fd;

  int nevents;
  int seed;
  int NLN;
  int i;
  char **lns;
  IS is;
  JRB t, tmp;
  char *s, nam[100];
  int r;
  FILE *fout;
  pthread_t tid;
  Dllist dl, dtmp;

 
  if (argc != 6) {
    fprintf(stderr, "usage: inclient1 host port nevents seed lnfile\n");
    exit(1);
  }

  fd = request_connection(argv[1], atoi(argv[2]));
  pthread_create(&tid, NULL, connection_reader, &fd);

  nevents = atoi(argv[3]);
  seed = atoi(argv[4]);

  srand48(seed);
  
  is = new_inputstruct(argv[5]);
  if (is == NULL) { perror(argv[5]); exit(1); }
  dl = new_dllist();
  NLN = 0;
  while (get_line(is) == 1) {
    dll_append(dl, new_jval_s((char *) strdup(is->fields[0])));
    NLN++;
  }
  lns = (char **) malloc(sizeof(char *)*NLN);
  for (i = 0; i < NLN; i++) {
    dtmp = dll_first(dl);
    lns[i] = dtmp->val.s;
    dll_delete_node(dtmp);
  }
  free_dllist(dl);

  t = make_jrb();

  fout = fdopen(fd, "w");

  for (i = 0; i < nevents; i++) {
    if (i < 50 || lrand48()%11 < 5) {
      strcpy(nam, fns[lrand48()%NFN]);
      strcat(nam, " ");
      strcat(nam, lns[lrand48()%NLN]); 
      s = (char *) strdup(nam);
      r = lrand48();
      jrb_insert_int(t, r, new_jval_s(s));
      fprintf(fout, "ADD %s %ld %03ld-%02ld-%04ld\n", s, lrand48()%100,
                 lrand48()%1000, lrand48()%100, lrand48()%10000);
      fflush(fout);
    } else if (lrand48()%6 == 0 && i < nevents - 1) {
      fprintf(fout, "PRINT\n");
      fflush(fout);
    } else {
      if (!jrb_empty(t)) {
        tmp = jrb_first(t);
        s = (char *) tmp->val.s;
        jrb_delete_node(tmp);
        fprintf(fout, "DELETE %s\n", s);
        fflush(fout);
        free(s);
      }
    }
  }
  fprintf(fout, "PRINT\n");
  fprintf(fout, "DONE\n");
  fflush(fout);
  pthread_exit(NULL);
}
