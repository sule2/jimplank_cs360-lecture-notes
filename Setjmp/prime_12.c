#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include "dllist.h"

sigjmp_buf Env;
long time;

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
  int test1, largest_prime1;
  int test2, largest_prime2;
  Dllist l;

  test1 = 2; largest_prime1 = 2;
  test2 = 2; largest_prime2 = 2;
  l = new_dllist();
  
  time = 0;
  signal(SIGALRM, alarm_handler);
  alarm(1);

  time += sigsetjmp(Env, 1);
  if (time%2 == 0) {
    printf("%4ld   EP1: %10d  EP2: %10d\n", time/2, largest_prime1, largest_prime2);
    enumerate_primes1(&test1, &largest_prime1);
  } else {
    enumerate_primes2(&test2, &largest_prime2, l);
  }
  return 0;

}

