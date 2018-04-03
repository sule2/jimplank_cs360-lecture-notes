#include <stdio.h>
#include <stdlib.h>

int main()
{
  int i;
  char *s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";

  i = 0;
  while (1) {
    if (fputs(s, stdout) == EOF) {
      fprintf(stderr, "Died on iteration %d on fputs\n", i);
      exit(0);
    }
    if (fflush(stdout) != 0) {
      fprintf(stderr, "Died on iteration %d on fflush\n", i);
      exit(0);
    }
    fprintf(stderr, "Iteration %d done\n", i);
    i++;
  }
  return 0;
}
