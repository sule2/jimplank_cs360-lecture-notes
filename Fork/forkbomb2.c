#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int i;
  int fv;

  for (i = 0; i < 4; i++) {
    fv = fork();
    printf("Process: %8d -- i = %d\n", getpid(), i);
    fflush(stdout);
  }
} 
