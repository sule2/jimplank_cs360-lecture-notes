#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>

sigjmp_buf Env;
void alarm_handler(int dummy)
{
  alarm(1);
  signal(SIGALRM, alarm_handler);
  siglongjmp(Env, 1);
}
  
void enumerate_primes1(int *current_test, int *largest_prime)
{
  int i;

  while(1) {
    for(i = 2; i*i <= *current_test && *current_test % i != 0; i++) ;
    if (*current_test % i != 0) *largest_prime = *current_test;
    *current_test = *current_test + 1;
  }
}
    
int main()
{
  int test, largest_prime;
  int time;

  test = 2;
  largest_prime = 2;
  
  time = 0;
  signal(SIGALRM, alarm_handler);
  alarm(1);

  time += sigsetjmp(Env, 1);
  printf("%4d   Largest Prime: %10d\n", time, largest_prime);
  enumerate_primes1(&test, &largest_prime);
  return 0;
}

