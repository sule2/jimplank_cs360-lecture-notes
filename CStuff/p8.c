#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char s[4];
  int i;
  char *s2;

  strcpy(s, "Jim");
  i = (int) s;
  printf("i = %d (0x%x)\n", i, i);
  printf("s = %ld (0x%lx)\n", (long unsigned int) s, (long unsigned int) s);

  i++;
  s2 = (char *) i;
  printf("s = 0x%lx.  s2 = 0x%lx, i = 0x%x\n", 
           (long unsigned int) s, 
           (long unsigned int) s2, i);
  printf("s[0] = %c, s[1] = %c, *s2 = %c\n", s[0], s[1], *s2);
  exit(0);
}
