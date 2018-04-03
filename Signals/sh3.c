#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int i, j, seconds;

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

  seconds = 0;

  signal(SIGALRM, alarm_handler);
  alarm(1);

  for (j = 0; j < 2000; j++) {
    for (i = 0; i < 1000000; i++);
  }
  return 0;
}

