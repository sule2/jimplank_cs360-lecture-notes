#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned long int UI;

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
  printf("Hi\n");
}

/* And of course i and buf will belong
   on the stack.  I will call malloc()
   to set buf equal to an address in 
   the heap. */

int main(int argc, char **argv)
{
  int i;
  char *buf;
  char *ptr;
  char c;
  void (*proc)();

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
  printf("\n");

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

  i = 0xabcd;

  while (1) {
    printf("\n");
    printf("Enter an address (with 0x), and R|W|X: ");
    fflush(stdout);
  
    /* From stdin, read a pointer value into ptr, and a character R, W, or X into c. */

    if (fgets(buf, 200, stdin) == NULL) {
      printf("Exiting\n");
      exit(0);
    }
  
    if (sscanf(buf, "0x%x %c", &ptr, &c) != 2 || strchr("RWX", c) == NULL) {
      printf("Bad format.\n");

    /* If c is 'R', read the character at the pointer. */

    } else if (c == 'R') {
      printf("Reading 0x%x\n", (UI) ptr);
      fflush(stdout);
      c = *ptr;
      printf("Read 0x%x\n", c); 
  
    /* If c is 'W', write the value 0x67 to the byte at the pointer, 
       and then print out A, i and buf. */

    } else if (c == 'W') {
      printf("Writing 0xff to 0x%x\n", ptr);
      *ptr = 0x67;
      printf("A is now 0x%x\n", A);
      printf("i is now 0x%x\n", i);
      printf("buf is now %s\n", buf);

    /* If c is 'X', then treat ptr as a procedure, and call it. */

    } else if (c == 'X') {
      memcpy(&proc, &ptr, sizeof(void *));
      proc();
    }
  }

  return 0;
}
