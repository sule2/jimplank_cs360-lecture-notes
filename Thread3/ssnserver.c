#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "jrb.h"

/* We are going to store these entries in a red-black tree, keyed on names. */

typedef struct {
  char *name;
  int age;
  char *ssn;
} Entry;

int main()
{
  JRB t, tmp;
  FILE *f;
  int age;
  char fn[300], ln[300], ssn[100], n[300];
  char command[300];
  char line[300];
  Entry *e;
  int done;

  t = make_jrb();

  /* Read four different events from standard input:

     ADD first-name last-name age social
     DELETE first-name last-name
     PRINT
     DONE
  */
     
  f = stdin;

  done = 0;
  while(!done && fgets(line, 300, f) != NULL) {
    if (sscanf(line, "%s", command) == 1) {
      if (sscanf(line, "ADD %s %s %d %s", fn, ln, &age, ssn) == 4) {
        e = (Entry *) malloc(sizeof(Entry));
        e->name = (char *) malloc(sizeof(char)*(strlen(ln)+strlen(fn)+3));
        strcpy(e->name, ln);
        strcat(e->name, ", ");
        strcat(e->name, fn);
        e->ssn = (char *) strdup(ssn);
        e->age = age;
        jrb_insert_str(t, e->name, new_jval_v(e));
      } else if (strcmp(command, "PRINT") == 0) {
        printf("__________________________________________________\n");
        jrb_traverse(tmp, t) {
          e = (Entry *) tmp->val.v;
          printf("%-30s -- %11s %4d\n", e->name, e->ssn, e->age);
        }
        printf("--------------------------------------------------\n");
      } else if (sscanf(line, "DELETE %s %s", fn, ln) == 2) {
        strcpy(n, ln);
        strcat(n, ", ");
        strcat(n, fn);
        tmp = jrb_find_str(t, n);
        if (tmp == NULL) {
          printf("Error: No %s %s\n", fn, ln);
        } else {
          jrb_delete_node(tmp);
        }
      } else if (strcmp(command, "DONE") == 0) {
        done = 1;
      } else {
        printf("Bad command: %s\n", command);
      }
    }
  }
  return 0;
}
