#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **envp)
{
  char *newargv[3];
  int i;

  newargv[0] = "cat";
  newargv[1] = "exec1.c";
  newargv[2] = NULL;

  i = execve("cat", newargv, envp);
  perror("exec1: execve failed");
  exit(1);
}
