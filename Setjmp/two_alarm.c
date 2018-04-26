#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

int i, j;
long T0;
jmp_buf Env;

void alarm_handler(int dummy)
{
  long t1;

  alarm(1);
  signal(SIGALRM, alarm_handler);
  t1 = time(0) - T0;
  printf("%ld second%s %s passed: j = %d.  i = %d\n", t1,
     (t1 == 1) ? "" : "s", 
     (t1 == 1) ? "has" : "have", j, i);
  while(1);
}

int main()
{
  signal(SIGALRM, alarm_handler);
  alarm(1);

  if (setjmp(Env) != 0) {
    printf("Gave up:  j = %d, i = %d\n", j, i);
    exit(1);
  }

  T0 = time(0);

  for (j = 0; j < 10000; j++) {
    for (i = 0; i < 1000000; i++);
  }
  return 0;
}
