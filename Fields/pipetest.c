/* pipetest.c counts the number of lines in all the .c files in the  
   current directory.  It does this by using pipe_inputstruct to get
   the standard output of 'cat *.c' into an inputstruct */

#include <stdio.h>
#include <stdlib.h>
#include "fields.h"

int main()
{
  IS is;
  int nlines;

  is = pipe_inputstruct("cat *.c");
  if (is == NULL) { perror("cat *.c"); exit(1); }

  nlines = 0;
  while (get_line(is) >= 0) nlines++;

  printf("# lines in *.c: %d\n", nlines);
}
