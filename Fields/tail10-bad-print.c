#include <stdio.h>
#include <stdlib.h>
#include "fields.h"

int main(int argc, char **argv) 
{
  IS is;
  int i, n;
  char *lines[10];
  
  /* Read the lines of standard input, and only keep the last ten. */

  is = new_inputstruct(NULL);
  n = 0;
  while (get_line(is) >= 0) {
    lines[n%10] = is->text1;        /* This is the bad line -- it doesn't copy the string. */
    printf("I have set lines[%d] to 0x%lx, which is currently %s",
           n%10, (unsigned long) (lines[n%10]), lines[n%10]);
    n++;
  }

  /* Print the last 10 lines, or fewer if there are fewer lines. 
     Remember that is->text1 has a newline at the end. */

  i = (n >= 10) ? (n-10) : 0;
  for ( ; i < n; i++) printf("%s", lines[i%10]);

  exit(0);
}
