#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef UI (unsigned long int) 

/* These are special variables that
   denote the end of the memory segments
   for the code ("text"), initialized
   global variables ("data") and
   uninitialized global variables ("bss").
   */

extern end;
extern etext;
extern edata;

/* Here are four global variables.  A
   and B belong to the "data", and X and Y
   belong to the "bss".  */

int A = 4;
int X;
int B = 6;
int Y;

/* Proc_a and main should reside in the
   "text" segment. */

void proc_a()
{
}

/* And of course i and buf will belong
   on the stack.  I will call malloc()
   to set buf equal to an address in 
   the heap. */

int main(int argc, char **argv)
{
  int i;
  char *buf;

  buf = (char *) malloc(200);

  printf("Page size: %d\n", getpagesize());
  printf("\n");

  printf("&etext: 0x%lx\n", (UI) &etext);
  printf("&edata: 0x%lx\n", (UI) &edata);
  printf("&end:   0x%lx\n", (UI) &end);
  printf("\n");

  printf("Code Addresses:\n");
  printf("main:   0x%lx\n", (UI) main);
  printf("proc_a: 0x%lx\n", (UI) proc_a);

  printf("Global Variable Addresses:\n");
  printf("&A: 0x%lx\n", (UI) &A);
  printf("&B: 0x%lx\n", (UI) &B);
  printf("&X: 0x%lx\n", (UI) &X);
  printf("&Y: 0x%lx\n", (UI) &Y);
  printf("\n");

  printf("Heap Address:\n");
  printf("buf: 0x%lx\n", (UI) buf);
  printf("\n");

  printf("Stack Addresses:\n");
  printf("&i:    0x%lx\n", (UI) &i);
  printf("&buf:  0x%lx\n", (UI) &buf);
  printf("&argc: 0x%lx\n", (UI) &argc);
  printf("\n");

  /* Finally, print the addressses as recorded
     in the directory "/proc". */

  sprintf(buf, "cat /proc/%d/maps", getpid());
  system(buf);
  return 0;
}
