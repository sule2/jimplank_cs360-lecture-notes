/* pipe2.c
   Jim Plank
   CS360
   Pipe lecture */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*  This is the same as pipe1.c except that it makes sure that unused files
    are closed.  This will make sure that the child exits on CNTL-D.  Why?
*/



int main()
{
  int pipefd[2];
  int pid;
  int i, line;
  char s[1000];

  if (pipe(pipefd) < 0) {
    perror("pipe");
    exit(1);
  }

  pid = fork();

  if (pid > 0) {
    close(1);
    close(pipefd[0]);
    while(fgets(s, 1000, stdin) != NULL) {
      write(pipefd[1], s, strlen(s));
    }
    close(pipefd[1]);
  } else {
    close(0);
    close(pipefd[1]);
    i = 0;
    line = 1;
    while(read(pipefd[0], s+i, 1) == 1) {
      if (s[i] == '\n') {
        s[i] = '\0';
        printf("%6d  %s\n", line, s);
        line++;
        i = 0;
      } else {
        i++;
      }
    }
  }
} 
