/* simpcat3.c
   James S. Plank
   CS360
   September, 1996 */

/* This program copies standard input to standard output one character
   at a time using fread()/fwrite(). */


#include <stdio.h>

int main()
{
  char c[1];
  int i;

  i = fread(c, 1, 1, stdin);
  while(i > 0) {    
    fwrite(c, 1, 1, stdout);
    i = fread(c, 1, 1, stdin);
  }
  return 0;
}

