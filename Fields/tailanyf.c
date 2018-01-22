#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"

int main(int argc, char **argv)
{
  char line[1000];
  char **lastn;
  int nlines, i, n;
  IS is;

  /* Error check the input */

  if (argc != 2) {
    fprintf(stderr, "usage: tailany1 n\n");
    exit(1);
  }
  n = atoi(argv[1]);
  if (n <= 0) exit(0);

  /* Allocate the array */

  lastn = (char **) malloc(sizeof(char *)*n);
 
  /* Allocate the IS */

  is = new_inputstruct(NULL);
  if (is == NULL) { perror("stdin"); exit(1); }

  /* Read the input */

  nlines = 0;
  while (get_line(is) >= 0) {
    if (nlines >= n) free(lastn[nlines%n]);
    lastn[nlines%n] = strdup(is->text1);
    nlines++;
  }

  /* Print the last n lines */

  if (nlines <= n) {
    for (i = 0; i < nlines; i++) printf("%s", lastn[i]);
  } else {
    for (i = nlines-n; i < nlines; i++) {
      printf("%s", lastn[i%n]);
    }
  }
}

