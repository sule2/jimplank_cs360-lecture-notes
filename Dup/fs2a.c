/* fs2a.c
   Jim Plank
   CS360
   Dup lecture */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
  int fd1, fd2;

  fd1 = open("file2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  fd2 = dup(fd1);

  printf("Before writing Jim:   lseek(fd1, 0, 1): %d.  lseek(fd2, 0, 1): %d\n", 
          (int) lseek(fd1, 0, 1), (int) lseek(fd2, 0, 1));

  write(fd1, "Jim\n", strlen("Jim\n"));

  printf("Before writing Plank: lseek(fd1, 0, 1): %d.  lseek(fd2, 0, 1): %d\n",
          (int) lseek(fd1, 0, 1), (int) lseek(fd2, 0, 1));

  write(fd2, "Plank\n", strlen("Plank\n"));

  printf("After writing Plank:  lseek(fd1, 0, 1): %d.  lseek(fd2, 0, 1): %d\n",
          (int) lseek(fd1, 0, 1), (int) lseek(fd2, 0, 1));

  close(fd1);
  close(fd2);
  return 0;
}
