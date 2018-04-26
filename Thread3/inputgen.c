#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"
#include "fields.h"

/* This program is going to create random events for our ssnserver.
   It has 65 first names that it uses, and reads last names from a file.
  
   It then generates 50 ADD events, and then random ADD, DELETE and PRINT
   events in a 5/5/1 ratio.  As such, the tree should be roughly 50 elements
   when it exits.

   Note that it stores names in a red-black tree keyed on random numbers.
   That way, when it wants to generate a DELETE event, it finds a "random" 
   element to delete by choosing the first element on the tree, deleting it
   from the tree, and turning it into a DELETE event.
 */

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

int main(int argc, char **argv)
{
  int nevents;
  int seed;
  int NLN;
  int i;
  char **lns;
  IS is;
  JRB t, tmp;
  char *s, nam[100];
  int r;
  Dllist dl, dtmp;

 
  if (argc != 4) {
    fprintf(stderr, "usage: inputgen nevents seed lnfile\n");
    exit(1);
  }

  nevents = atoi(argv[1]);
  seed = atoi(argv[2]);

  srand48(seed);
  
  /* Read in the last names from the file given on the command line. */

  is = new_inputstruct(argv[3]);
  if (is == NULL) { perror(argv[3]); exit(1); }
  dl = new_dllist();
  NLN = 0;
  while (get_line(is) == 1) {
    dll_append(dl, new_jval_s(strdup(is->fields[0])));
    NLN++;
  }
  jettison_inputstruct(is);

  lns = (char **) malloc(sizeof(char *)*NLN);
  for (i = 0; i < NLN; i++) {
    dtmp = dll_first(dl);
    lns[i] = dtmp->val.s;
    dll_delete_node(dtmp);
  }
  free_dllist(dl);

  /* Now, generate the events as described above. */

  t = make_jrb();

  for (i = 0; i < nevents; i++) {
    if (i < 50 || lrand48()%11 < 5) {
      strcpy(nam, fns[lrand48()%NFN]);
      strcat(nam, " ");
      strcat(nam, lns[lrand48()%NLN]); 
      s = (char *) strdup(nam);
      r = lrand48();
      jrb_insert_int(t, r, new_jval_s(s));
      printf("ADD %s %ld %03ld-%02ld-%04ld\n", s, lrand48()%100,
                 lrand48()%1000, lrand48()%100, lrand48()%10000);
    } else if (lrand48()%6 == 0 && i != nevents -1) {
      printf("PRINT\n");
    } else {
      if (!jrb_empty(t)) {
        tmp = jrb_first(t);
        s = tmp->val.s;
        jrb_delete_node(tmp);
        printf("DELETE %s\n", s);
        free(s);
      }
    }
  }
  printf("PRINT\n");
  printf("DONE\n");
  return 0;
}
