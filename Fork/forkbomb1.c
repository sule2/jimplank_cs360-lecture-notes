#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int i;
  int fv;

  for (i = 0; i < 10; i++) {
    fv = fork();
    printf("Process: %8d -- i = %d\n", getpid(), i);
    if (fv == 0) exit(0);
  }
  return 0;
} 
