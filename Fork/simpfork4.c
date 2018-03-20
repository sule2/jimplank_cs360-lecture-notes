#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int i;
  int seekp;
  int fd;
  char *s1;
  char s2[1000];

  /* Open a file for writing, and then call fork(). */

  fd = open("tmpfile.txt", O_WRONLY | O_TRUNC | O_CREAT, 0666);

  s1 = "Before forking\n";
  write(fd, s1, strlen(s1));

  i = fork();

  /* Delay the parent by a second, so that the child runs first. */

  if (i > 0) {
    sleep(1);  
    s1 = "Parent";
  } else {
    s1 = "Child";
  }

  /* Print the file's seek pointer. 
     Do a write, and print the seek pointer again. */

  seekp = lseek(fd, 0, SEEK_CUR);
  printf("%s: After forking, before writing: Seek pointer = %d\n", s1, seekp);

  sprintf(s2, "%s: After forking.\n", s1);
  write(fd, s2, strlen(s2));

  seekp = lseek(fd, 0, SEEK_CUR);
  printf("%s: After forking, after  writing: Seek pointer = %d\n", s1, seekp);

  return 0;
}
