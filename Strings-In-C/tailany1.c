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
    fprintf(stderr, "usage: tailany1 n\n");
    exit(1);
  }
  n = atoi(argv[1]);
  if (n <= 0) exit(0);

  /* Allocate the array */

  lastn = (char **) malloc(sizeof(char *)*n);
  if (lastn == NULL) { perror("malloc"); exit(1); }

  for (i = 0; i < n; i++) {
    lastn[i] = (char *) malloc(sizeof(char)*1000);
    if (lastn[i] == NULL) { perror("malloc"); exit(1); }
  }
 
  /* Read the input */

  nlines = 0;
  while (fgets(line, 1000, stdin) != NULL) {
    strcpy(lastn[nlines%n], line);
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
  return 0;
}

