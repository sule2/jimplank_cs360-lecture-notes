#include <stdio.h>

int main()
{
  char line[1000];
  char *last10[10];
  int nlines, i;

  nlines = 0;
  while (fgets(line, 1000, stdin) != NULL) {
    last10[nlines%10] = line;
    nlines++;
  }

  if (nlines <= 10) {
    for (i = 0; i < nlines; i++) printf("%s", last10[i]);
  } else {
    for (i = nlines-10; i < nlines; i++) {
      printf("0x%lx %s", (unsigned long) last10[i%10], last10[i%10]);
    }
  }
  printf("Line is 0x%lx\n", (unsigned long) line);
  return 0;
}
