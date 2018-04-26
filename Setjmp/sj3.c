#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>


int a(char *s, jmp_buf env)
{
  int i;

  i = setjmp(env);
  printf("Setjmp returned -- i = %d, 0x%lx\n", i, (unsigned long) s);
  
  printf("s = %s\n", s);
  return i;
}

int b(char *s, jmp_buf env)
{
  printf("In B: Calling longjmp(env, i)\n");

  longjmp(env, 3);
}



int main(int argc, char **argv)
{
  jmp_buf env;

  if (a("Jim", env) != 0) exit(0);
  b(NULL, env);
}
