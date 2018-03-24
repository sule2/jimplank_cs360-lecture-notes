/* forkwait3a.c
   Jim Plank
   CS360 -- Exec/Wait lecture
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  int i, j, status;
  char *s;

  i = fork();

  if (i > 0) {
    j = wait(&status);
    printf("Parent: Child done.\n");
    printf("  Return value: %d\n", j);
    printf("  Status:       %d\n", status);
    printf("  WIFSTOPPED:   %d\n", WIFSTOPPED(status));
    printf("  WIFSIGNALED:  %d\n", WIFSIGNALED(status));
    printf("  WIFEXITED:    %d\n", WIFEXITED(status));
    printf("  WEXITSTATUS:  %d\n", WEXITSTATUS(status));
    printf("  WTERMSIG:     %d\n", WTERMSIG(status));
    printf("  WSTOPSIG:     %d\n", WSTOPSIG(status));
  } else {
    printf("Child (%d) generating a seg fault\n", getpid());
    s = NULL;
    *s = 'a';
  }
  return 0;
}
