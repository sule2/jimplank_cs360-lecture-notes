/* CS360 Example Programs for the Random System Call Lecture
 *
 * James S. Plank
 * University of Tennessee
 * February, 2010
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main()
{
  int fd;
  char s[11];
  int i;

  printf("Opening f1.txt and putting \"Fun Fun\" into s.\n");
  strcpy(s, "Fun Fun\n");
  fd = open("f1.txt", O_RDONLY);
  sleep(1);

  printf("Removing f1.txt\n");
  remove("f1.txt");
  sleep(1);

  printf("Listing f1.txt, and reading 10 bytes from the open file descriptor.\n");
  system("ls -l f1.txt");
  i = read(fd, s, 10);
  s[i] = '\0';
  printf("Read returned %d: %d %s\n", i, fd, s);
  return 0;
}
