/* execcat3.c
   Jim Plank
   CS360 -- Exec/Wait lecture
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  char *newargv[3];
  int i, j;

  newargv[0] = "cat";
  newargv[1] = "f1.txt";
  newargv[2] = NULL;

  for (j = 0; j < 4; j++) {
    printf("I am %d.  j = %d\n", getpid(), j);
    fflush(stdout);
    if (fork() == 0) {
      i = execv("cat", newargv);
    } else {
      wait(&i);
    }
  }
  return 0;
}
