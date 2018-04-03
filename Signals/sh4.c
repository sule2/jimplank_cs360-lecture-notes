#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Put a while loop into the alarm handler, to see if it
   can catch SIGALRM while it's in the alarm handler. */

int i, j;

void cntl_bs_handler(int dummy)
{
  printf("SIGQUIT generated: j = %d.  i = %d\n", j, i);
  signal(SIGQUIT, cntl_bs_handler);
}

void alarm_handler(int dummy)
{
  printf("One second has passed: j = %d.  i = %d\n", j, i);
  signal(SIGALRM, alarm_handler);
  alarm(1);
  while(1);
}

int main()
{

  signal(SIGALRM, alarm_handler);
  signal(SIGQUIT, cntl_bs_handler);
  alarm(1);

  for (j = 0; j < 2000; j++) {
    for (i = 0; i < 1000000; i++);
  }
  return 0;
}

