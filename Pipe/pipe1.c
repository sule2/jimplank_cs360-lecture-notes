/* pipe1.c
   Jim Plank
   CS360
   Pipe lecture */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* This program shows how two processes can communicate via pipes.
   A child process is forked off.  The parent reads input from standard
   input, and sends it to the child, which prints it to standard output with 
   its line number.

   If you type CNTL-D to this, and then do a ps x, you'll see that there's
   still a pipe process running.  Kill it manually with kill.  Why does
   this happen?
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

  /* The parent reads lines of input from 
     standard input, and writes them 
     to the pipe. */

  if (pid > 0) {
    while(fgets(s, 1000, stdin) != NULL) {
      write(pipefd[1], s, strlen(s));
    }

  /* The child reads single characters from
     the pipe, and when it sees a newline, it
     writes the line to standard output, 
     preceded by the line number. */

  } else {
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
  return 0;
} 
