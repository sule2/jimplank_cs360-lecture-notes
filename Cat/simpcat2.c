/* simpcat2.c
   James S. Plank
   CS360
   September, 1996 */

/* This program copies standard input to standard output one character
   at a time using read()/write(). */

#include <unistd.h> 
                       
int main()                 
{                      
  char c;           
  int i;               
                       
  i = read(0, &c, 1);   
  while(i > 0) {       
    write(1, &c, 1);    
    i = read(0, &c, 1); 
  }                    
  return 0;
}                      

