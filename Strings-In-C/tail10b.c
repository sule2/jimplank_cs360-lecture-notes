#include <stdio.h>
#include <string.h>

int main()
{
  char line[1000];
  char last10[10][1000];
  int nlines, i;

  nlines = 0;
  while (fgets(line, 1000, stdin) != NULL) {
    strcpy(last10[nlines%10], line);
    nlines++;
  }

  if (nlines <= 10) {
    for (i = 0; i < nlines; i++) printf("%s",last10[i]);
  } else {
    for (i = nlines-10; i < nlines; i++) {
      printf("%s",last10[i%10]);
    }
  }
}
