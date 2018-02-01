/* simpcat1a.c 
   Jame S. Plank
   CS360
   September, 1996 */

/* This program copies standard input to standard output one character
   at a time using getchar()/putchar(). */

#include <stdio.h>
#include <fcntl.h>
                       
int main()                 
{                      
  int c;              
                       
  c = getchar();       
  while(c != EOF) {    
    putchar(c);        
    c = getchar();     
  }                    
  return 0;
}                      

