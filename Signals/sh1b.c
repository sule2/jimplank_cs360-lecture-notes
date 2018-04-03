#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* This program makes it look like you have an nsf server issue
   when your program generates a segmentation violation. */

void sint_handler(int dummy)
{
  signal(SIGINT, sint_handler);
  while(1) ;
}

void segv_handler(int dummy)
{
  signal(SIGINT, sint_handler);
  fprintf(stderr, "nfs server not responding, still trying\n");
  while(1) ;
}

int main()
{

  char *s;

  signal(SIGSEGV, segv_handler);

  /* This should cause a segmentation violation: */

  s = (char *) 0;
  strcpy(s, "jim");
  return 0;
}
