#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "sockettome.h"

/* This is like minitalk1, except a parent process forks the
   two children, and then cleans one up when the other dies. */

int main(int argc, char **argv)
{
  char *hn;
  int port, sock, fd;
  int pid1, pid2, p, dummy;

  if (argc != 4) {
    fprintf(stderr, "usage: minitalk hostname port s|c\n");
    exit(1);
  }

  hn = argv[1];
  port = atoi(argv[2]);
  if (port < 5000) {
    fprintf(stderr, "usage: minitalk hostname port s|c\n");
    fprintf(stderr, "       port must be > 5000\n");
    exit(1);
  }

  if (strcmp(argv[3], "s") == 0) {
    sock = serve_socket(port);
    fd = accept_connection(sock);
    close(sock);
  } else if (strcmp(argv[3], "c") == 0) {
    fd = request_connection(hn, port);
  } else {
    fprintf(stderr, "usage: minitalk hostname port s|c\n");
    fprintf(stderr, "       last argument must be `s' or `c'\n");
    exit(1);
  }

  printf("Connection made -- input goes to remote site\n");
  printf("                   output comes from remote site\n");

  pid1 = fork();

  /* The first child will have standard input come from the socket. */

  if (pid1 == 0) {
    dup2(fd, 0);

  /* Otherwise, fork again: */

  } else {
    pid2 = fork();

    /* The second child will have standard output go to the socket. */

    if (pid2 == 0) {
      dup2(fd, 1);

    /* The parent closes all extraneous file descriptors, and waits for
       one child to die.  When that happens, the parent kills the other child. */

    } else {
      close(fd);
      close(0);
      close(1);
      p = wait(&dummy);
      kill((p == pid1) ? pid2 : pid1, SIGKILL);
      exit(0);
    }
  }

  /* The children both close the socket fd (remember, they have each dup'd
     this to either zero or one, and then exec cat. */

  close(fd);
  execlp("cat", "cat", NULL);
  fprintf(stderr, "Exec failed.  Drag\n");
  return 0;
}
