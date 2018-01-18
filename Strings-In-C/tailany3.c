#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  char line[1000];
  char **lastn;
  int nlines, i, n;

  /* Error check the input */

  if (argc != 2) {
    fprintf(stderr, "usage: tailany3 n\n");
    exit(1);
  }
  n = atoi(argv[1]);
  if (n <= 0) exit(0);

  /* Allocate the array */

  lastn = (char **) malloc(sizeof(char *)*n);
 
  /* Read the input */

  nlines = 0;
  while (fgets(line, 1000, stdin) != NULL) {
    if (nlines >= n) free(lastn[nlines%n]);
    lastn[nlines%n] = strdup(line);
    nlines++;
  }

  /* Print the last n lines */

  if (nlines <= n) {
    for (i = 0; i < nlines; i++) puts(lastn[i]);
  } else {
    for (i = nlines-n; i < nlines; i++) {
      puts(lastn[i%n]);
    }
  }
  return 0;
}

