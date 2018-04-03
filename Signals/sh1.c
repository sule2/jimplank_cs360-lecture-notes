#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/* This is the signal handler that we are
   setting up for Control-C.  Instead of doing
   the default action, it will call this handler. */

void cntl_c_handler(int dummy)
{
  signal(SIGINT, cntl_c_handler);
  printf("You just typed cntl-c\n");
}

int main()
{
  int i, j;

  signal(SIGINT, cntl_c_handler);

  for (j = 0; j < 2000; j++) {
    for (i = 0; i < 1000000; i++);
  }
  return 0;
}

