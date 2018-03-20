#include <stdio.h>
#include <stdlib.h>

int main()
{
  printf("My pid = %d.  My parent's pid = %d\n", getpid(), getppid());
  return 0;
}
