#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fields.h"
#include "dllist.h"

int main(int argc, char **argv)
{
  IS is;
  int n;
  Dllist l;
  Dllist tmp;

  if (argc != 2) {
    fprintf(stderr, "usage: dlltail n\n");
    exit(1);
  }
  n = atoi(argv[1]);
  if (n < 0) {
    fprintf(stderr, "usage: dlltail n  -- n must be >= 0\n");
    exit(1);
  }

  is = new_inputstruct(NULL);
  l = new_dllist();

  while (get_line(is) >= 0) {
    dll_append(l, new_jval_s(strdup(is->text1)));
    if (is->line > n) {
      tmp = dll_first(l);
      free(jval_s(dll_val(tmp)));
      dll_delete_node(tmp);
    }
  }

  dll_traverse(tmp, l) printf("%s", jval_s(tmp->val));
}
