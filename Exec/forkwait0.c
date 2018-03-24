#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  int rv, stat_loc;
  
  stat_loc = 0xabcdef;

  rv = wait(&stat_loc);
  printf("RV: %d.   Stat_loc = 0x%x\n", rv, (unsigned int) stat_loc);
  return 0;
}
