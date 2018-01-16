#include <stdio.h>
#include <stdlib.h>

int main()
{
  int *ia, *ip, iarray[10];
  int i;

  ia = malloc(sizeof(int) * 10);

  for (i = 0; i < 10; i++) ia[i] = 100+i;
  for (i = 0; i < 10; i++) iarray[i] = 200+i;

  printf("Printing ia using a pointer\n\n");
  for (ip = ia; ip != ia + 10; ip++) {
    printf("IP: 0x%lx   *ip: %d\n", (long unsigned int) ip, *ip);
  }

  printf("\n");
  printf("Printing iarray using a pointer\n\n");
  for (ip = iarray; ip != iarray + 10; ip++) {
    printf("IP: 0x%lx   *ip: %d\n", (long unsigned int) ip, *ip);
  }
  exit(0);
}
