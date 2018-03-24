#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  int i, j, status;

  i = fork();

  if (i > 0) {
    j = wait(&status);
    printf("Parent: Child done.\n");
    printf("  Return value: %d\n", j);
    printf("  Status:       %d\n", status);
    printf("  WIFSIGNALED:  %d\n", WIFSIGNALED(status));
    printf("  WIFEXITED:    %d\n", WIFEXITED(status));
    printf("  WEXITSTATUS:  %d\n", WEXITSTATUS(status));
    printf("  WTERMSIG:     %d\n", WTERMSIG(status));
  } else {
    printf("Child (%d) calling exit(1)\n", getpid());
    exit(1);
  }
  return 0;
}
