#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <setjmp.h>

int main()
{
  jmp_buf env;
  int i;

  i = setjmp(env);
  if (i == 10) exit(0);

  printf("i = %d\n", i);

  longjmp(env, i+1);
  printf("Does this line get printed?\n");

  return 0;
}

