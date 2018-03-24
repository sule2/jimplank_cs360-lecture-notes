/* pipe3.c
   Jim Plank
   CS360
   Pipe lecture */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* Try running pipe3, killing the child process by hand (using kill), and
   then typing something to stdin.  The parent will attept to write to
   the pipe, which has no readers, since the parent has closed pipefd[0],
   and the child is gone.  Thus, SIGPIPE will be generated.  This signal
   kills the process unless it is handled by a signal handler, as shown
   here -- of course, all the signal handler does is print out a line and
   then exit, but it is at least recognized.
*/


void sigpipe_handler(int dummy)
{
  fprintf(stderr, "%d: caught a SIGPIPE\n", getpid());
  exit(1);
}

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

  signal(SIGPIPE, sigpipe_handler);

  if (pid > 0) {
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
