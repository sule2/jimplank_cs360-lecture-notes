/* Uses red-black trees to sort standard input lexicographically,
   ignoring upper and lower case.  It does this by creating a new
   comparison function ucomp, which duplicates strcmp()'s functionality
   but ignores case.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "jrb.h"
#include "fields.h"

int ucomp(Jval k1, Jval k2)
{
  char *s1, *s2, c1, c2;

  s1 = k1.s;
  s2 = k2.s;
  

  while(1) {
    if (*s1 == '\0') {
      if (*s2 == '\0') return 0; else return -1;
    } else if (*s2 == '\0') {
      return 1;
    } else {
      c1 = tolower(*s1);
      c2 = tolower(*s2);
      if (c1 < c2) return -1;
      if (c1 > c2) return 1;
    }
    s1++;
    s2++;
  }
}

int main()
{
  JRB b;
  JRB bn;
  IS is;

  is = new_inputstruct(NULL);
  b = make_jrb();

  while (get_line(is) >= 0) {
    (void) jrb_insert_gen(b, new_jval_s(strdup(is->text1)), 
                               new_jval_v(NULL), ucomp);
  }

  jrb_traverse(bn, b) {
    printf("%s", jval_s(bn->key));
  }
  exit(0);
}
