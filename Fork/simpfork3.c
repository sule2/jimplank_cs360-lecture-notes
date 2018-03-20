#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int K;

int main()
{
  int i;
  int j;

  j = 200;
  K = 300;

  printf("Before forking: j (Address 0x%lx) = %d.   K (Address 0x%lx) = %d\n", 
         (long unsigned int) &j, j, (long unsigned int) &K, K);

  i = fork();

  if (i > 0) {  /* Delay the parent */
    sleep(1);
    printf("Parent after:   j (Address 0x%lx) = %d.   K (Address 0x%lx) = %d\n", 
         (long unsigned int) &j, j, (long unsigned int) &K, K);

  } else {
    j++;
    K++;
    printf("Child after:    j (Address 0x%lx) = %d.   K (Address 0x%lx) = %d\n", 
         (long unsigned int) &j, j, (long unsigned int) &K, K);
  }
  return 0;
} 
