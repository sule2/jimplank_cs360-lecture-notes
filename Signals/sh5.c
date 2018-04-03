#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int i, j;

void alarm_handler(int dummy)
{
  printf("One second has passed: j = %d.  i = %d\n", j, i);
  signal(SIGALRM, alarm_handler);
  alarm(1);

  for (; j < 2000; j++) {
    for (i = 0; i < 1000000; i++);
  }
}

int main()
{
  signal(SIGALRM, alarm_handler);
  alarm(1);

  for (j = 0; j < 2000; j++) {
    for (i = 0; i < 1000000; i++);
  }
  return 0;
}
