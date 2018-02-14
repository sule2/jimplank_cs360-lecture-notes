#include <stdio.h>

int main()
{
  char s[9000000];

  printf("s = 0x%x\n", s);
  printf("%d\n", *s);
  return 0;
}
