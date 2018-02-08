/* ls2.c
   Jim Plank
   CS360 -- Spring, 1994

   This is a program which lists files and their sizes to standard output.
   The files are specified on the command line arguments.  It uses stat to
   see if the files exist, and to determine the files' sizes.
*/

  
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char **argv)
{
  int i;
  struct stat buf;
  int exists;

  for (i = 1; i < argc; i++) {
    exists = stat(argv[i], &buf);
    if (exists < 0) {
      fprintf(stderr, "%s not found\n", argv[i]);
    } else {
      printf("%10ld %s\n", buf.st_size, argv[i]);
    }
  }
}
     

