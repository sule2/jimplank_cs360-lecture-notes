#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int i, j;
  char *s;

  for (i = 0; i < 1000; i++) {
    s = (char *) malloc(10);
    printf("0x%x\n", (unsigned int) s);
    for (j = 0; j < 10; j++) s[j] = 'a' + j % 26;
    free(s+8);
  }
}
