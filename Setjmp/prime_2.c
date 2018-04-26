#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include "dllist.h"

sigjmp_buf Env;

void alarm_handler(int dummy)
{
  alarm(1);
  signal(SIGALRM, alarm_handler);
  siglongjmp(Env, 1);
}
  
int is_prime(int p, Dllist l)
{
  Dllist tmp;
  int i;

  dll_traverse(tmp, l) {
    i = tmp->val.i;
    if (i*i > p) return 1;
    if (p % i == 0) return 0;
  }
  return 1;
}

void enumerate_primes2(int *current_test, int *largest_prime, Dllist l)
{

  while(1) {
    if (is_prime(*current_test, l)) {
      dll_append(l, new_jval_i(*current_test));
      *largest_prime = *current_test;
    }
    *current_test = *current_test + 1;
  }
}
    
int main()
{
  int test, largest_prime;
  int time;
  Dllist l;

  test = 2;
  largest_prime = 2;
  l = new_dllist();
  
  time = 0;
  signal(SIGALRM, alarm_handler);
  alarm(1);

  time += sigsetjmp(Env, 1);
  printf("%4d   Largest Prime: %10d\n", time, largest_prime);
  enumerate_primes2(&test, &largest_prime, l);
}
