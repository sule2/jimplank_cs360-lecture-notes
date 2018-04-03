#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/* i and j are global variables so that the signal handler
   can read them. */
int i, j;

/* Different handlers for SIGINT and SIGQUIT. */

void cntl_c_handler(int dummy)
{
  printf("You just typed cntl-c.  j is %d and i is %d\n", j, i);
  signal(SIGINT, cntl_c_handler);
}

void cntl_bs_handler(int dummy)
{
  printf("You just typed cntl-\\.  j is %d and i is %d\n", j, i);
  signal(SIGQUIT, cntl_bs_handler);
}

int main()
{

  signal(SIGINT, cntl_c_handler);
  signal(SIGQUIT, cntl_bs_handler);

  for (j = 0; j < 2000; j++) {
    for (i = 0; i < 1000000; i++);
  }
  return 0;
}


