/* forkwait3.c
   Jim Plank
   CS360 -- Exec/Wait lecture
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  int i, j, status;

  i = fork();

  if (i > 0) {
    sleep(1);
    printf("Kill the child with 'kill -9 %d'  or just 'kill %d'\n", i, i);
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
    printf("Child (%d) doing nothing until you kill it\n", getpid());
    while (1) ;
  }
  return 0;
}
