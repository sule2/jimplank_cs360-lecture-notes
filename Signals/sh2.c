#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int i, j;

void alarm_handler(int dummy)
{
  printf("Three seconds just passed: j = %d.  i = %d\n", j, i);
}

int main()
{

  signal(SIGALRM, alarm_handler);
  alarm(3);

  for (j = 0; j < 2000; j++) {
    for (i = 0; i < 1000000; i++);
  }
}

