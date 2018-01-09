#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int i[2];
  unsigned char *c;
  int *ip;

  i[0] = 0xabcdef12;
  i[1] = 0x3456789a;

  c = (char *) i;
  c++;
  ip = (int *) c;
  
  printf("I: 0x%x 0x%x\n", i[0], i[1]);
  printf("c: 0x%lx    ip: 0x%lx\n", (unsigned long) c, (unsigned long) ip);
  printf("c[0] = 0x%x   c[1] = 0x%x\n", c[0], c[1]);
  printf("c[2] = 0x%x   c[3] = 0x%x\n", c[2], c[3]);
  printf("0x%x\n", *ip);

  exit(0);
}

