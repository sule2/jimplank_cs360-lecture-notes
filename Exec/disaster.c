/* disaster.c
   Jim Plank
   CS360 -- Exec/Wait lecture
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  char *newargv[3];
  int i, j;

  newargv[0] = "cat";
  newargv[1] = "f1.txt";
  newargv[2] = NULL;

  j = 0;
  while (j < 4) {
    if (fork() == 0) {
      execv("cat", newargv);
    } else {
      j++;
    }
  }
  return 0;
}
