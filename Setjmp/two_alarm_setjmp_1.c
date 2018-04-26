#include <stdio.h>
#include <time.h>
#include <unistd.h>
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
  longjmp(Env, t1);
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
  j = 0;
  i = 0;

  if (setjmp(Env) == 8) {
    printf("Gave up\n");
    exit(0);
  };

  for (; j < 10000; j++) {
    for (; i < 1000000; i++) ;
    i = 0;
  }
  printf("Done: Time = %ld\n", time(0)-T0);
  return 0;
}
