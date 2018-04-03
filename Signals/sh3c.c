#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int i, j, seconds;

void alarm_handler(int dummy)
{
  seconds++;
  printf("%d second%s just passed: j = %4d.  i = %6d\n", seconds,
     (seconds == 1) ? " " : "s", j, i);
  signal(SIGALRM, alarm_handler);
  alarm(1);
}

int main()
{
  int k;
  seconds = 0;

  signal(SIGALRM, alarm_handler);
  alarm(1);

  for (j = 0; j < 2000; j++) {
    for (i = 0; i < 1000000; i++) k = 1-k;
  }
  printf("%d %d %d\n", j, i, k);
  return 0;
}

