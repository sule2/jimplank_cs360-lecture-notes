/* Uses red-black trees to sort like sort -n -- i.e. it treats each
   line as an integer, and sorts it that way.  If the lines are not
   integers, or there are duplicate lines, anything goes.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

int main()
{
  JRB b;
  JRB bn;
  IS is;

  is = new_inputstruct(NULL);
  b = make_jrb();

  while (get_line(is) >= 0) {
    (void) jrb_insert_int(b, atoi(is->text1), new_jval_s(strdup(is->text1)));
  }

  jrb_traverse(bn, b) {
    printf("%s", jval_s(bn->val));
  }
  exit(0);
}
