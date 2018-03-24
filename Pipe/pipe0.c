/* pipe0.c
   Jim Plank
   CS360
   Pipe lecture */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int pipefd[2];
  int i;
  char s[1000];
  char *s2;

  if (pipe(pipefd) < 0) {
    perror("pipe");
    exit(1);
  }

  s2 = "Rex Morgan MD";

  write(pipefd[1], s2, strlen(s2));

  i = read(pipefd[0], s, 1000);
  s[i] = '\0';

  printf("Read %d bytes from the pipe: '%s'\n", i, s);

}
