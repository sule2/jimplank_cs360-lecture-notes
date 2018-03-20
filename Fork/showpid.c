#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  printf("My pid = %d.  My parent's pid = %d\n", getpid(), getppid());
  return 0;
}
