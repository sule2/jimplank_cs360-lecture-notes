/* fs3b.c
   Jim Plank
   CS360
   Dup lecture */

#include <stdio.h>
#include <string.h>

int main()
{
  char s[1000];
  int i;
  FILE *f;

  f = fopen("file3", "w");
  fprintf(f, "This is file3\n");

  i = fork();
  fprintf(f, "fork() = %d.\n", i);
  fclose (f);
}

