#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
  char *newargv[3];
  int i;

  newargv[0] = "cat";
  newargv[1] = "exec2.c";
  newargv[2] = NULL;

  i = execve("/bin/cat", newargv, envp);
  perror("exec2: execve failed");
  exit(1);
}
