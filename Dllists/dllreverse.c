#include <stdio.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"

int main()
{
  IS is;
  Dllist l;
  Dllist tmp;

  is = new_inputstruct(NULL);
  l = new_dllist();

  while (get_line(is) >= 0) {
    dll_append(l, new_jval_s(strdup(is->text1)));
  }

  dll_rtraverse(tmp, l) printf("%s", jval_s(tmp->val));
}
