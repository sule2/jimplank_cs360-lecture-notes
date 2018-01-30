/* c1.c
   James S. Plank
   September, 1996 
   Last Revision: Thu Jan 27 08:43:49 EST 2011
 */

/* This program opens and closes the file "in1.txt" in 
   a variety of ways.  Make sure you understand 
   this program, especially the return values of the
   open calls. */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
  int fd1, fd2;

  /* First open in1.txt twice for reading.  Print out the file descriptors. */

  fd1 = open("in1.txt", O_RDONLY);
  if (fd1 < 0) { perror("c1"); exit(1); }

  fd2 = open("in1.txt", O_RDONLY);
  if (fd2 < 0) { perror("c1"); exit(1); }

  printf("Opened the file in1.txt twice:  Fd's are %d and %d.\n", fd1, fd2);

  /* Close the file descriptors. */

  if (close(fd1) < 0) { perror("c1"); exit(1); }
  if (close(fd2) < 0) { perror("c1"); exit(1); }

  printf("Closed both fd's.\n");

  /* Open in1.txt again, to see that it will reuse the first file descriptor. */

  fd2 = open("in1.txt", O_RDONLY);
  if (fd2 < 0) { perror("c1"); exit(1); }
  
  printf("Reopened in1.txt into fd2: %d.\n", fd2);

  /* Close the file descriptor twice.  The second causes an error, which usually
     goes unnoticed, because programmers rarely look at the return value of close(). */

  if (close(fd2) < 0) { perror("c1"); exit(1); }

  printf("Closed fd2.  Now, calling close(fd2) again.\n");
  printf("This should cause an error.\n\n");

  if (close(fd2) < 0) { perror("c1"); exit(1); }
  return 0;
}
