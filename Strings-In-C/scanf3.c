#include <stdio.h>
#include <stdlib.h>

int main()
{
  char s[10];
  int i;
  
  if (scanf("%s", s) != 1) exit(0);

  for (i = 0; s[i] != '\0'; i++) {
    printf("Character: %d: %3d %c\n", i, s[i], s[i]);
  }
  exit(0);
}

